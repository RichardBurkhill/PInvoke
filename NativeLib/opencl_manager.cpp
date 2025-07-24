#include "opencl_manager.hpp"
#include <iostream>
#include <sstream>

OpenCLManager::OpenCLManager() {}

OpenCLManager::~OpenCLManager() {
    if (commandQueue) clReleaseCommandQueue(commandQueue);
    if (context) clReleaseContext(context);
}

bool OpenCLManager::Initialize() {
    cl_uint platformCount = 0;
    clGetPlatformIDs(0, nullptr, &platformCount);
    if (platformCount == 0) return false;

    std::vector<cl_platform_id> platforms(platformCount);
    clGetPlatformIDs(platformCount, platforms.data(), nullptr);
    platformId = platforms[0];

    cl_uint deviceCount = 0;
    clGetDeviceIDs(platformId, CL_DEVICE_TYPE_GPU, 0, nullptr, &deviceCount);
    if (deviceCount == 0) return false;

    std::vector<cl_device_id> devices(deviceCount);
    clGetDeviceIDs(platformId, CL_DEVICE_TYPE_GPU, deviceCount, devices.data(), nullptr);
    deviceId = devices[0];

    context = clCreateContext(nullptr, 1, &deviceId, nullptr, nullptr, nullptr);
    commandQueue = clCreateCommandQueue(context, deviceId, 0, nullptr);

    return context != nullptr && commandQueue != nullptr;
}

std::string OpenCLManager::GetPlatformAndDeviceInfo() {
    char platformName[256], deviceName[256];
    clGetPlatformInfo(platformId, CL_PLATFORM_NAME, sizeof(platformName), platformName, nullptr);
    clGetDeviceInfo(deviceId, CL_DEVICE_NAME, sizeof(deviceName), deviceName, nullptr);

    std::ostringstream oss;
    oss << "Platform: " << platformName << "\n"
        << "Device: " << deviceName << "\n";
    return oss.str();
}
