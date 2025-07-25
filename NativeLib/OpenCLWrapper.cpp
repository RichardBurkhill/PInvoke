// OpenCLWrapper.cpp
#include "OpenCLWrapper.hpp"
#include <CL/opencl.h>
#include <iostream>
#include <stdexcept>
#include <cstring>

#define CL_TARGET_OPENCL_VERSION 120

extern const char* add_kernel_source;

std::string loadKernelFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Failed to open kernel file: " + path);
    return std::string((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
}

OpenCLWrapper::OpenCLWrapper(const std::string& kernelSourceCode, const std::string& kernelFunctionName){
    find_algorithm(kernelSourceCode, kernelFunctionName);
}

OpenCLWrapper::~OpenCLWrapper() {
    if (kernel) clReleaseKernel(kernel);
    if (program) clReleaseProgram(program);
    if (queue) clReleaseCommandQueue(queue);
    if (context) clReleaseContext(context);
}

void OpenCLWrapper::checkErr(cl_int err, const char* name) {
    if (err != CL_SUCCESS) {
        std::cerr << "ERROR: " << name << " (" << err << ")" << std::endl;
        throw std::runtime_error(name);
    }
}

void OpenCLWrapper::find_algorithm(const std::string& kernelSourceCode, const std::string& kernelFunctionName) {
    cl_int err;

    // Step 1: Get the first available OpenCL platform (e.g., Apple)
    cl_uint num_platforms;
    clGetPlatformIDs(1, &platform, &num_platforms);

    // Step 2: Get the first GPU device from that platform
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, nullptr);

    // Step 3: Create an OpenCL context for the device
    // This holds all the OpenCL objects (buffers, kernels, etc.)
    context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &err);

    // Step 4: Create a command queue for sending tasks to the device
    queue = clCreateCommandQueue(context, device, 0, &err);

    checkErr(err, "clCreateCommandQueueWithProperties");

    // Step 5: Create and build the OpenCL program from the string
    const char* src = kernelSourceCode.c_str();
    program = clCreateProgramWithSource(context, 1, &src, nullptr, &err);
    checkErr(err, "clCreateProgramWithSource");

    err = clBuildProgram(program, 0, nullptr, nullptr, nullptr, nullptr);
    checkErr(err, "clBuildProgram");

    // Step 6: Create the kernel function (name is now passed in)
    kernel = clCreateKernel(program, kernelFunctionName.c_str(), &err);
    checkErr(err, "clCreateKernel");
}

void OpenCLWrapper::set_data_and_run_algorithm(std::vector<float>& data) {
    cl_int err;
    size_t dataSize = data.size() * sizeof(float);

    // Step 1: Create a GPU buffer and copy input data into it
    cl_mem buffer = clCreateBuffer(
        context,
        CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, // Copy input to GPU
        dataSize,
        data.data(),
        &err
    );
    checkErr(err, "clCreateBuffer");

    /////////////////////////
    // Run the kernel
    /////////////////////////

    // Step 2: Set the buffer as the kernel argument
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &buffer);

    // Step 3: Define how many work-items (threads) to launch
    // One per element of the input array
    size_t global_size = data.size();

    // Step 4: Enqueue the kernel for execution on the device
    err = clEnqueueNDRangeKernel(
        queue,
        kernel,
        1,            // 1D range
        nullptr,      // Global offset
        &global_size, // Global size
        nullptr,      // Local size (let OpenCL choose)
        0, nullptr, nullptr
    );
    checkErr(err, "clEnqueueNDRangeKernel");

    // Step 5: Wait for kernel execution to complete
    clFinish(queue);

    // Step 6: Read the result data back from GPU into the original vector
    err = clEnqueueReadBuffer(queue, buffer, CL_TRUE, 0, dataSize, data.data(), 0, nullptr, nullptr);
    checkErr(err, "clEnqueueReadBuffer");

    // Step 7: Free the buffer memory on the GPU
    clReleaseMemObject(buffer);
}
