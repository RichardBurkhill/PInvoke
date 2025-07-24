#pragma once
#include <CL/cl.h>
#include <vector>
#include <string>

class OpenCLManager {
public:
    OpenCLManager();
    ~OpenCLManager();

    bool Initialize();
    std::string GetPlatformAndDeviceInfo();

private:
    cl_platform_id platformId = nullptr;
    cl_device_id deviceId = nullptr;
    cl_context context = nullptr;
    cl_command_queue commandQueue = nullptr;
};
