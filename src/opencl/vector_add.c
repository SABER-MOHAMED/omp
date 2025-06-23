#include <stdio.h>
#include <stdlib.h>
#include <OpenCL/opencl.h>

#define SIZE 1024

int main() {
    // memory allocation
    float *a = malloc(sizeof(float) * SIZE);
    float *b = malloc(sizeof(float) * SIZE);
    float *c = malloc(sizeof(float) * SIZE);

    for (int i = 0; i < SIZE; i++) {
        a[i] = i;
        b[i] = 2 * i;
    }

    // OpenCL Platform and Device Setup
    cl_platform_id plat;
    clGetPlatformIDs(1, &plat, NULL);

    cl_device_id dev;
    clGetDeviceIDs(plat, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);


    // context and command queue
    // creates an environment for OpenCL operations
    // command queue 'file d'attente'
    cl_context ctx = clCreateContext(NULL, 1, &dev, NULL, NULL, NULL);
    cl_command_queue queue = clCreateCommandQueue(ctx, dev, 0, NULL);


    // the code that runs on the GPU
    // __kernel: marks this as a GPU function
    // __global: indicates memory accessible by all gpu cores
    // get_global_id(0): gets the current thread's id
    // each gpu thread handles one array element
    const char *src =
        "__kernel void vec_add(__global const float *a,"
        "__global const float *b, __global float *c){"
        "int gid = get_global_id(0); c[gid] = a[gid] + b[gid];}";

    // compile the kernel
    cl_program prog = clCreateProgramWithSource(ctx, 1, &src, NULL, NULL);
    clBuildProgram(prog, 1, &dev, NULL, NULL, NULL);

    // creates gpu memory and copies arrays a and b toit
    // bufC is write-only for storing results
    cl_mem bufA = clCreateBuffer(ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                 sizeof(float) * SIZE, a, NULL);
    cl_mem bufB = clCreateBuffer(ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                 sizeof(float) * SIZE, b, NULL);
    cl_mem bufC = clCreateBuffer(ctx, CL_MEM_WRITE_ONLY, sizeof(float) * SIZE,
                                 NULL, NULL);

// links the kernel function to the memory buffers
// launches 1024 GPU threads (one per array element)
    cl_kernel kernel = clCreateKernel(prog, "vec_add", NULL);
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufA);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufB);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufC);

    size_t global = SIZE;
    clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global, NULL, 0, NULL,
                           NULL);

    clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0, sizeof(float) * SIZE, c, 0,
                        NULL, NULL);

    for (int i = 0; i < 10; i++) {
        printf("c[%d] = %f\n", i, c[i]);
    }

    clReleaseMemObject(bufA);
    clReleaseMemObject(bufB);
    clReleaseMemObject(bufC);
    clReleaseKernel(kernel);
    clReleaseProgram(prog);
    clReleaseCommandQueue(queue);
    clReleaseContext(ctx);

    free(a);
    free(b);
    free(c);

    return 0;
}