// OpenCLWrapper.hpp
#pragma once
#include <CL/opencl.h>
#include <vector>
#include <fstream>

std::string loadKernelFromFile(const std::string& path);

class OpenCLWrapper {
public:
    OpenCLWrapper(const std::string& kernelSourceCode, const std::string& kernelFunctionName);
    ~OpenCLWrapper();

    OpenCLWrapper(const OpenCLWrapper&) = delete;
    OpenCLWrapper& operator=(const OpenCLWrapper&) = delete;
    OpenCLWrapper(OpenCLWrapper&&) = delete;
    OpenCLWrapper& operator=(OpenCLWrapper&&) = delete;

    void find_algorithm(const std::string& kernelSourceCode, const std::string& kernelFunctionName);
    void set_data_and_run_algorithm(std::vector<float>& data);

private:

    void checkErr(cl_int err, const char* name);

    cl_platform_id platform = nullptr;
    cl_device_id device = nullptr;
    cl_context context = nullptr;
    cl_command_queue queue = nullptr;
    cl_program program = nullptr;
    cl_kernel kernel = nullptr;

    size_t _dataSize = 0;
    void* _data = nullptr;
};
