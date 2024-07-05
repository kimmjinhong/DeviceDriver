#include "DeviceDriver.h"
#include <stdexcept>

#include<iostream>

using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properl
    int result;
    result = (int)(m_hardware->read(address));
    std::cout << "read : " << result << std::endl;
    for(int i = 0; i < 4; i++) {
        if (result != (int)(m_hardware->read(address))) {
            throw ReadFailException("Read Fail");
        }
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}