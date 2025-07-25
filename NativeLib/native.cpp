#include <OpenCL/opencl.h>
#include <iostream>
#include "OpenCLWrapper.hpp"

typedef void(*CallbackFunc)(const char*);

static CallbackFunc g_callback = nullptr;

extern "C" void register_callback(CallbackFunc cb) {
    g_callback = cb;
}

extern "C" void trigger_callback() {
    if (g_callback) {
        g_callback("Hello from C++");
    }
}

extern "C" {
    int add_numbers(int a, int b) {
        return a + b;
    }
}

extern "C" void add1_to_array_elements(float* data, int length) {
    std::string kernelCode = loadKernelFromFile("/Users/richardburkhill/dev/PInoke/NativeLib/add_one.cl");
    OpenCLWrapper opencl(kernelCode, "add_one");
    
    std::vector<float> vec(data, data + length);
    opencl.addOneToArray(vec);
    std::memcpy(data, vec.data(), length * sizeof(float));
}


extern "C" {
    
    void query_opencl() {
        cl_uint platformCount = 0;
        clGetPlatformIDs(0, nullptr, &platformCount);
        std::cout << "Number of OpenCL platforms: " << platformCount << std::endl;

        if (platformCount == 0) {
            std::cout << "No OpenCL platforms found." << std::endl;
            return;
        }

        cl_platform_id* platforms = new cl_platform_id[platformCount];
        clGetPlatformIDs(platformCount, platforms, nullptr);

        for (cl_uint i = 0; i < platformCount; ++i) {
            char platformName[128];
            clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 128, platformName, nullptr);
            std::cout << "Platform " << i << ": " << platformName << std::endl;
        }

        delete[] platforms;

        trigger_callback();
        std::cout << "Callback triggered after querying OpenCL platforms." << std::endl;
    }
}