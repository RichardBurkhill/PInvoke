#include "opencl_manager.hpp"
#include <iostream>

extern "C" void query_opencl() {
    OpenCLManager manager;
    if (!manager.Initialize()) {
        std::cout << "Failed to initialize OpenCL manager.\n";
        return;
    }

    std::string info = manager.GetPlatformAndDeviceInfo();
    std::cout << info;
}
