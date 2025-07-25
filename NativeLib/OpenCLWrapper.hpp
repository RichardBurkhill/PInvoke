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

    void checkErr(cl_int err, const char* name);
    void initOpenCL(const std::string& kernelSourceCode, const std::string& kernelFunctionName);
    void addOneToArray(std::vector<float>& data);

private:

    cl_platform_id platform = nullptr;
    cl_device_id device = nullptr;
    cl_context context = nullptr;
    cl_command_queue queue = nullptr;
    cl_program program = nullptr;
    cl_kernel kernel = nullptr;
};
