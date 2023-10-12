#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include <fstream>
#include <iostream>
#include <random>
#include <string>

// Declare random number generators at file scope
std::random_device rd;
std::mt19937 rng(rd()); // For float values
std::mt19937 rng_int(rd()); // For int16 values

// Function to generate a random float between -1.0 and 1.0
float randomFloat() {
    static std::uniform_real_distribution<float> dist(-1.0, 1.0);
    return dist(rng);
}

// Function to generate a random 2-byte fixed-point value between -32767 and 32767
int16_t randomFixedPoint() {
    static std::uniform_int_distribution<int16_t> dist(-32767, 32767);
    return dist(rng_int);
}

// Rest of your code...


// Function to generate and save a random matrix to a file
void generateMatrix(int rows, int cols, bool isFloat, const std::string &filename) {
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cerr << "Error: Unable to open file '" << filename << "' for writing." << std::endl;
        return;
    }

    // Write matrix dimensions and data type to the file
    ofs << rows << " " << cols << " " << (isFloat ? "float" : "int16") << std::endl;

    // Generate and write random values to the file
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (isFloat) {
                ofs << randomFloat() << " ";
            } else {
                ofs << randomFixedPoint() << " ";
            }
        }
        ofs << std::endl;
    }

    std::cout << "Matrix saved to '" << filename << "'" << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <dimension> <isFloat (1/0)>" << std::endl;
        return 1;
    }

    int dimension = std::stoi(argv[1]);
    bool isFloat = std::stoi(argv[2]) != 0;

    std::string filenameA = "matrixA_" + std::to_string(dimension) + "_" + (isFloat ? "float" : "int16") + ".txt";
    std::string filenameB = "matrixB_" + std::to_string(dimension) + "_" + (isFloat ? "float" : "int16") + ".txt";

    generateMatrix(dimension, dimension, isFloat, filenameA);
    generateMatrix(dimension, dimension, isFloat, filenameB);

    return 0;
}
