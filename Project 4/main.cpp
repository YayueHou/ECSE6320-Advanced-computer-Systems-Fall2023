#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#ifdef __AVX2__
#include <immintrin.h>
#endif

using namespace std;

int get_num_threads_from_env() {
    const char* num_threads_str = getenv("NUM_THREADS");
    return num_threads_str ? stoi(num_threads_str) : 4;
}

const int NUM_THREADS = get_num_threads_from_env();

// Global variables
mutex mtx;

// Dictionary encoder
void encoder(const vector<string> &data, int start, int end, unordered_map<string, int> &dict) {
    for (int i = start; i < end; i++) {
        mtx.lock();
        if (dict.find(data[i]) == dict.end()) {
            dict[data[i]] = dict.size();
        }
        mtx.unlock();
    }
}

vector<int> encode(const vector<string> &data) {
    vector<int> encoded_data(data.size());
    unordered_map<string, int> dict;

    int data_size = data.size();
    int chunk_size = data_size / NUM_THREADS;
    vector<thread> threads;
    for (int i = 0; i < NUM_THREADS; i++) {
        int start = i * chunk_size;
        int end = (i + 1) * chunk_size;
        if (i == NUM_THREADS - 1) {
            end = data_size;
        }
        threads.push_back(thread(encoder, ref(data), start, end, ref(dict)));
    }

    for (auto &t : threads) {
        t.join();
    }

    for (size_t i = 0; i < data.size(); i++) {
        encoded_data[i] = dict[data[i]];
    }

    return encoded_data;
}

// Query functions
vector<int> search(const vector<string> &data, const string &value) {
    vector<int> indices;
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] == value) {
            indices.push_back(i);
        }
    }
    return indices;
}

#ifdef __AVX2__
vector<int> search_simd(const vector<string> &data, const string &value) {
    vector<int> indices;

    __m256i value_data = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(value.data()));
    for (size_t i = 0; i < data.size(); i++) {
        __m256i data_i = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(data[i].data()));
        __m256i cmp = _mm256_cmpeq_epi8(value_data, data_i);

        if (_mm256_movemask_epi8(cmp) == 0xFFFFFFFF) {
            indices.push_back(i);
        }
    }
    return indices;
}
#endif

vector<pair<string, int>> prefix_search(const vector<string> &data, const string &prefix) {
    vector<pair<string, int>> result;

    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].substr(0, prefix.size()) == prefix) {
            result.emplace_back(data[i], i);
        }
    }

    return result;
}


// Main function
int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <search_value> <prefix> <data_path>" << endl;
        return 1;
    }
    // Load data from file
    ifstream infile(argv[3]);
    vector<string> data;
    string line;
    while (getline(infile, line)) {
        data.push_back(line);
    }
    infile.close();

    // Encode the data
    auto start = chrono::high_resolution_clock::now();
    vector<int> encoded_data = encode(data);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> encoding_time = end - start;

    // Query operations
    string search_value = argv[1];
    string prefix = argv[2];

    // Single data item search speed performance
    start = chrono::high_resolution_clock::now();
    vector<int> search_result = search(data, search_value);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> search_time = end - start;

    #ifdef __AVX2__
    start = chrono::high_resolution_clock::now();
    vector<int> search_simd_result = search_simd(data, search_value);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> search_simd_time = end - start;
    #endif

    // Prefix scan speed performance
    start = chrono::high_resolution_clock::now();
    vector<pair<string, int>> prefix_result = prefix_search(data, prefix);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> prefix_time = end - start;

    // Print results
    cout << "Encoding time: " << encoding_time.count() << " seconds" << endl;
    cout << "Search time: " << search_time.count() << " seconds" << endl;
    #ifdef __AVX2__
    cout << "Search SIMD time: " << search_simd_time.count() << " seconds" << endl;
    #endif
    cout << "Prefix search time: " << prefix_time.count() << " seconds" << endl;

    return 0;
}