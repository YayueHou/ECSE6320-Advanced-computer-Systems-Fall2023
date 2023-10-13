## Matrix-Matrix Multiplication
### Instructions
In this project, we need to implement a C/C++ module that carries out high-speed matrix-matrix multiplication by explicitly utilizing 

(i) Multiple threads

(ii) x86 SIMD instructions

(iii) Techniques to minimize cache miss rate via restructuring data access patterns (as discussed in class). 


The implementation should be able to support (1) configurable matrix size that can be much larger than the on-chip cache capacity, and (2) both fixed-point and floating-point data. Moreover, your implement should allow users to individually turn on/off the three optimization techniques (i.e., multi-threading, SIMD, and cache miss minimization) and configure the thread number so that users could easily observe the effect of any combination of these three optimization techniques.

### Quick Start
In this project, there are two program, the first one named 'matrix_generator.cc', which aims to generate random matrix A and B. To use it, we need firstly compile it by using:
```
g++ -o matrix_generator matrix_generator.cc
```
After get the exe file named ```matrix_generator```, then use ```./matrix_generator <dimension><isFloat>```. For example 1000 dimension float32 matrix:
```
./matrix_generator 1000 1
```
Which will generate two matrix A: ```matrixA_1000_float.txt``` and matrix B: ```matrixB_1000_float.txt ```

The other program is ```main.cc```, which will execute the matrix-matrix multiplication in three modes: 1)Multiple threads 2)x86 SIMD instructions, and 3) Techniques to minimize cache miss rate via restructuring data access patterns.

Firstly, compile it by command line:
```
g++ -march=native -o main main.cc -std=c++11 -pthread
```
Then to execute the multiplication, use ```./main <matrixA> <matrixB> <mode> <the number of blocks when using loopblocked if not use set 0>```, for example:
```
./main matrixA_1000_float.txt matrixB_1000_float.txt intrin 0
./main matrixA_1000_float.txt matrixB_1000_float.txt common 0
./main matrixA_1000_float.txt matrixB_1000_float.txt multithread  0
./main matrixA_1000_float.txt matrixB_1000_float.txt loopblocked 32
```
The output will be the execution time of any modes, like:
```
Duration: 834 milliseconds
```
### Evaluation
Initially, we show the performance of our code under different matrix size 
1) 1,000x1,000
2) 5,000x5,000
3) 10,000x10,000

and different data precision float32 and int16.
1) 1,000 x 1,000 results

| **Original Float32(ms)** | **Original Int16(ms)**| **Multi Threads Float32(ms)** | **Multi Threads Int16(ms)** | **SIMD Float32(ms)** | **SIMD Int16(ms)** | **Loop Block 32 Float32(ms)** |**Loop Block 32 Int16(ms)** |
|-------------|-------------|---------------|------------------------------------|------------------------------------|------------------------------------|-------------------------------------|-------------------------|
|3187|3051|1093|995|806|770|7087|7125|

2) 5,000 x 5,000 results

| **Original Float32(ms)** | **Original Int16(ms)**| **Multi Threads Float32(ms)** | **Multi Threads Int16(ms)** | **SIMD Float32(ms)** | **SIMD Int16(ms)** | **Loop Block 32 Float32(ms)** |**Loop Block 32 Int16(ms)** |
|-------------|-------------|---------------|------------------------------------|------------------------------------|------------------------------------|-------------------------------------|-------------------------|
|590342|622639|224247|247460|121074|136192|986426|1006311|
   
3) 10,000 x 10,000 results

| **Original Float32(ms)** | **Original Int16(ms)**| **Multi Threads Float32(ms)** | **Multi Threads Int16(ms)** | **SIMD Float32(ms)** | **SIMD Int16(ms)** | **Loop Block 32 Float32(ms)** |**Loop Block 32 Int16(ms)** |
|-------------|-------------|---------------|------------------------------------|------------------------------------|------------------------------------|-------------------------------------|-------------------------|
|5606529 |5581535||1|1010447|3|1|1|

Finally, the results can be summarised in the following figure:


### Conclusion

