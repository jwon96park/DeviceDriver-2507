#pragma once
#include "flash_memory_device.h"
#include <stdexcept>

class ReadFailException : public std::exception {
public:
    char const* what() const override {
        return "Read value is different. Error!";
    }
};

class WriteFailException : public std::exception {
public:
    char const* what() const override {
        return "There is another value already. Error!";
    }
};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void posetConditionCheck(long address, int readValue);
    void write(long address, int data);

    bool isNotWritable(int readValue);

protected:
    FlashMemoryDevice* m_hardware;
    const int REPEAT_NUM = 4;
};