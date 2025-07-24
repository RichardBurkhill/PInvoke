#include <CL/cl.h>
#include <iostream>

extern "C" void query_opencl() {
    cl_uint platformCount = 0;
    clGetPlatformIDs(0, nullptr, &platformCount);

    if (platformCount == 0) {
        std::cout << "No OpenCL platforms found.\n";
        return;
    }

    cl_platform_id* platforms = new cl_platform_id[platformCount];
    clGetPlatformIDs(platformCount, platforms, nullptr);

    std::cout << "Found " << platformCount << " OpenCL platform(s):\n";

    for (cl_uint i = 0; i < platformCount; ++i) {
        char name[256];
        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(name), name, nullptr);
        std::cout << "  Platform " << i << ": " << name << "\n";

        // List devices on this platform
        cl_uint deviceCount = 0;
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, nullptr, &deviceCount);

        if (deviceCount == 0) {
            std::cout << "    No devices found.\n";
            continue;
        }

        cl_device_id* devices = new cl_device_id[deviceCount];
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devices, nullptr);

        for (cl_uint j = 0; j < deviceCount; ++j) {
            char deviceName[256];
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, sizeof(deviceName), deviceName, nullptr);
            std::cout << "    Device " << j << ": " << deviceName << "\n";
        }

        delete[] devices;
    }

    delete[] platforms;
}
// This function can be called from C# using P/Invoke to query OpenCL platforms and devices.
// It prints the information to the console.