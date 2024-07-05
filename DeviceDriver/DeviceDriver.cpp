#include "DeviceDriver.h"
#include <stdexcept>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properl
    int result;
    result = (int)(m_hardware->read(address));
    result = (int)(m_hardware->read(address));
    result = (int)(m_hardware->read(address));
    result = (int)(m_hardware->read(address));
    result = (int)(m_hardware->read(address));
    if (address == READ_FAIL_ADDRESS) {
        throw ReadFailException("Read Fail");
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}