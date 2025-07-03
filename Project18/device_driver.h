#pragma once
#include "flash_memory_device.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void posetConditionCheck(long address, int readValue);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
    const int REPEAT_NUM = 4;
};