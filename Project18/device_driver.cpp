#include "device_driver.h"
#include <stdexcept>

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
            throw std::runtime_error("Read value is different. Error!");;
    }
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}