## Matrix-Matrix Multiplication
### Instructions
In this project, we need to implement a C/C++ module that carries out high-speed matrix-matrix multiplication by explicitly utilizing 

(i) Multiple threads

(ii) x86 SIMD instructions

(iii) Techniques to minimize cache miss rate via restructuring data access patterns (as discussed in class). 


The implementation should be able to support (1) configurable matrix size that can be much larger than the on-chip cache capacity, and (2) both fixed-point and floating-point data. Moreover, your implement should allow users to individually turn on/off the three optimization techniques (i.e., multi-threading, SIMD, and cache miss minimization) and configure the thread number so that users could easily observe the effect of any combination of these three optimization techniques.

### Quick Start
In this project, there are two program, the first one named 'matrix_generator.cc', which aims to generate 
