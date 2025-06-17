# OpenMP Programming Assignment

This repository contains OpenMP programming exercises demonstrating parallel computing concepts in C/C++.

## Overview

This assignment includes several OpenMP programs that showcase different parallel programming techniques:

- **tp0_hello.c**: Basic OpenMP "Hello World" with parallel threads
- **tp1_hello.c**: Parallel array addition with timing
- **tp2_hello.c**: Parallel matrix multiplication 
- **tp3_hello.cpp**: Parallel image processing (grayscale conversion) using OpenCV
- **tp4_hello.c**: Parallel image filtering (Gaussian blur) using OpenCV

## Prerequisites

### macOS Setup

1. **Install Homebrew** (if not already installed):
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

2. **Install required dependencies**:
   ```bash
   brew install libomp opencv gcc
   ```

## Compilation and Execution

### For C files (tp0, tp1, tp2):

```bash
# Compile with OpenMP support
clang -Xpreprocessor -fopenmp -lomp filename.c -o executable_name

# Example:
clang -Xpreprocessor -fopenmp -lomp tp0_hello.c -o tp0_hello
```

### For C++ files with OpenCV (tp3, tp4):

```bash
# Compile with OpenMP and OpenCV
clang++ -std=c++11 -Xpreprocessor -fopenmp -I$(brew --prefix libomp)/include -L$(brew --prefix libomp)/lib -lomp `pkg-config --cflags --libs opencv4` filename.cpp -o executable_name

# Example:
clang++ -std=c++11 -Xpreprocessor -fopenmp -I$(brew --prefix libomp)/include -L$(brew --prefix libomp)/lib -lomp `pkg-config --cflags --libs opencv4` tp3_hello.cpp -o tp3_hello
```

### Running the programs:

```bash
# Set number of threads (optional)
export OMP_NUM_THREADS=4

# Run the executable
./executable_name
```

## Program Descriptions

### TP0: Hello World (`tp0_hello.c`)
- Basic parallel execution
- Each thread prints its ID
- Demonstrates `#pragma omp parallel`

### TP1: Array Addition (`tp1_hello.c`)
- Parallel addition of two arrays (1M elements)
- Measures execution time
- Uses `#pragma omp parallel for`

### TP2: Matrix Multiplication (`tp2_hello.c`)
- Parallel matrix multiplication (500x500 matrices)
- Demonstrates nested loop parallelization with `collapse(2)`
- Measures execution time

### TP3: Image Grayscale (`tp3_hello.cpp`)
- Loads color image from `../docs/images/in.jpg`
- Converts to grayscale using parallel processing
- Saves result as `out_gray.jpg`
- Uses OpenCV for image I/O

### TP4: Image Filtering (`tp4_hello.c`)
- Applies Gaussian blur filter to image
- Parallel implementation of convolution
- Saves result as `out_gauss.jpg`

## Input Files

- Place input image as `docs/images/in.jpg` for tp3 and tp4
- Sample image is provided in the `docs/images/` directory

## Output Files

- `out_gray.jpg`: Grayscale converted image (from tp3)
- `out_gauss.jpg`: Gaussian blurred image (from tp4)

## Performance Notes

- Execution time varies based on system specifications
- Number of threads can be controlled via `OMP_NUM_THREADS` environment variable
- Default thread count is typically equal to the number of CPU cores

## Troubleshooting

### Common Issues:

1. **OpenMP header not found**:
   ```bash
   # Make sure libomp is installed
   brew install libomp
   ```

2. **OpenCV not found**:
   ```bash
   # Install OpenCV
   brew install opencv
   # Check installation
   pkg-config --cflags --libs opencv4
   ```

3. **Image loading errors**:
   - Verify image path: `../docs/images/in.jpg`
   - Ensure image file exists and is readable

## Learning Objectives

- Understanding OpenMP directives and parallel execution
- Performance measurement and optimization
- Parallel algorithms for numerical computation
- Image processing with parallel computing
- Memory access patterns in parallel programs

## Author

University Assignment - SoC and Parallel Programming Course