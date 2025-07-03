#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int readValue = (int)(m_hardware->read(address));
    posetConditionCheck(address, readValue);
    return readValue;
}

void DeviceDriver::posetConditionCheck(const long address, const int readValue)
{
    for (int turn = 1; turn <= REPEAT_NUM; turn++) {
        int repeatedReadValue = (int)(m_hardware->read(address));
        if (repeatedReadValue != readValue)
            throw ReadFailException();
    }
}

void DeviceDriver::write(long address, int data)
{
    int readValue = (int)(m_hardware->read(address));
    if (isWritable(readValue))
        m_hardware->write(address, (unsigned char)data);
}

bool DeviceDriver::isWritable(const int readValue)
{
    return readValue == 0xFF;
}
