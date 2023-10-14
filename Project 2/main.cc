#include <iostream>
#include <fstream>
#include <chrono>
#include <immintrin.h>
#include <thread> // Include C++ threading support
#include <vector>


// Matrix structure
struct Matrix {
    int rows, cols;
    union {
        float * dataFloat;
        int16_t * dataFixed;
    };
    bool isFloat;
};

// Read matrix from txt file
Matrix readMatrix(const char * filename) {
    std::ifstream file(filename);
    Matrix m;
    file >> m.rows >> m.cols >> m.isFloat;
    if (m.isFloat) {
        // m.isFloat = true;
        m.dataFloat = new float[m.rows * m.cols];
        for (int i = 0; i < m.rows * m.cols; i++) {
            file >> m.dataFloat[i];
        }
    } else {
        // m.isFloat = false;
        m.dataFixed = new int16_t[m.rows * m.cols];
        for (int i = 0; i < m.rows * m.cols; i++) {
            file >> m.dataFixed[i];
        }
    }
    return m;
}

// Write matrix to txt file
void writeMatrix(const Matrix & m,
    const char * filename) {
    std::ofstream file(filename);
    file << m.rows << " " << m.cols << " " << m.isFloat << std::endl;
    if (m.isFloat) {
        for (int i = 0; i < m.rows; i++) {
            for (int j = 0; j < m.cols; j++) {
                file << m.dataFloat[i * m.cols + j] << " ";
            }
            file << std::endl;
        }
    } else {
        for (int i = 0; i < m.rows; i++) {
            for (int j = 0; j < m.cols; j++) {
                file << m.dataFixed[i * m.cols + j] << " ";
            }
            file << std::endl;
        }
    }
}

Matrix mulMatrixIntrin(const Matrix & a,
    const Matrix & b) {
    Matrix c;
    c.rows = a.rows;
    c.cols = b.cols;
    c.isFloat = a.isFloat || b.isFloat;
    if (c.isFloat) {
        c.dataFloat = new float[c.rows * c.cols];
        for (int i = 0; i < c.rows; i++) {
            for (int j = 0; j < c.cols; j++) {
                __m256 sum = _mm256_setzero_ps();
                for (int k = 0; k < a.cols; k += 8) {
                    __m256 aData = _mm256_loadu_ps(a.dataFloat + i * a.cols + k);
                    __m256 bData = _mm256_loadu_ps(b.dataFloat + k * b.cols + j);
                    // sum = _mm256_fmadd_ps(aData, bData, sum);
                    sum = _mm256_add_ps(sum, _mm256_mul_ps(aData, bData));
                }
                c.dataFloat[i * c.cols + j] = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
            }
        }
    } else {
        c.dataFixed = new int16_t[c.rows * c.cols];
        for (int i = 0; i < c.rows; i++) {
            for (int j = 0; j < c.cols; j++) {
                __m256i sum = _mm256_setzero_si256();
                for (int k = 0; k < a.cols; k += 8) {
                    __m256i aData = _mm256_loadu_si256((__m256i * )(a.dataFixed + i * a.cols + k));
                    __m256i bData = _mm256_loadu_si256((__m256i * )(b.dataFixed + k * b.cols + j));
                    sum = _mm256_add_epi16(sum, _mm256_mullo_epi16(aData, bData));
                }
                int32_t result[8];
                _mm256_storeu_si256((__m256i * ) result, sum);
                c.dataFixed[i * c.cols + j] = result[0] + result[1] + result[2] + result[3] + result[4] + result[5] + result[6] + result[7];
            }
        }

    }
    return c;
}

Matrix mulMatrixCommon(Matrix a, Matrix b) {
    Matrix c;
    c.rows = a.rows;
    c.cols = b.cols;
    c.isFloat = a.isFloat;

    if (a.isFloat) {
        c.dataFloat = new float[c.rows * c.cols];
        for (int i = 0; i < c.rows; i++) {
            for (int j = 0; j < c.cols; j++) {
                float sum = 0;
                for (int k = 0; k < a.cols; k++) {
                    sum += a.dataFloat[i * a.cols + k] * b.dataFloat[k * b.cols + j];
                }
                c.dataFloat[i * c.cols + j] = sum;
            }
        }
    } else {
        c.dataFixed = new int16_t[c.rows * c.cols];
        for (int i = 0; i < c.rows; i++) {
            for (int j = 0; j < c.cols; j++) {
                int sum = 0;
                for (int k = 0; k < a.cols; k++) {
                    sum += (int)(a.dataFixed[i * a.cols + k] * b.dataFixed[k * b.cols + j]) >> 8;
                }
                c.dataFixed[i * c.cols + j] = sum;
            }
        }

    }

    return c;
}

// Function for multi-threaded matrix multiplication
void multiThreadedMultiply(const Matrix& a, const Matrix& b, Matrix& c, int startRow, int endRow) {
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < c.cols; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < a.cols; ++k) {
                sum += a.dataFloat[i * a.cols + k] * b.dataFloat[k * b.cols + j];
            }
            c.dataFloat[i * c.cols + j] = sum;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <matrixA file> <matrixB file> <method>" << std::endl;
        std::cout << "Method options: intrin, common, multithread" << std::endl;
        return 1;
    }

    Matrix a = readMatrix(argv[1]);
    Matrix b = readMatrix(argv[2]);

    // Check if matrices can be multiplied
    if (a.cols != b.rows) {
        std::cerr << "Matrix dimensions are not compatible for multiplication." << std::endl;
        return 1;
    }

    // Initialize the result matrix with the same dimensions as a and b
    Matrix c;
    c.rows = a.rows;
    c.cols = b.cols;
    c.isFloat = a.isFloat;
    c.dataFloat = new float[c.rows * c.cols];

    auto start = std::chrono::high_resolution_clock::now();

    std::string method(argv[3]);
    if (method == "intrin") {
        c = mulMatrixIntrin(a, b);
    } else if (method == "common") {
        c = mulMatrixCommon(a, b);
    } else if (method == "multithread") {
        // Define the number of threads (you can adjust this based on your CPU)
        const int numThreads = std::thread::hardware_concurrency();
        std::vector<std::thread> threads;

        // Split the work among threads
        int rowsPerThread = c.rows / numThreads;
        int remainingRows = c.rows % numThreads;
        int currentRow = 0;

        for (int i = 0; i < numThreads; ++i) {
            int numRows = rowsPerThread + (i < remainingRows ? 1 : 0);
            threads.emplace_back(multiThreadedMultiply, std::ref(a), std::ref(b), std::ref(c), currentRow, currentRow + numRows);
            currentRow += numRows;
        }

        // Wait for all threads to finish
        for (auto& thread : threads) {
            thread.join();
        }
    } else {
        std::cerr << "Invalid method specified. Choose from intrin, common, multithread." << std::endl;
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Duration: " << duration << " milliseconds" << std::endl;

    // Clean up
    delete[] c.dataFloat;

    return 0;
}