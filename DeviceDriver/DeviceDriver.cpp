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
    int result;
    result = (int)(m_hardware->read(address));
    if (result != 0xff) {
        throw WriteFailException("Write Fail");
    }
    m_hardware->write(address, (unsigned char)data);
}