#pragma once
#include <stdexcept>
#include<string>
#include "FlashMemoryDevice.h"

using namespace std;
class DeviceDriver
{
public:
    static const int READ_FAIL_ADDRESS = 0x100;
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};

class ReadFailException : public std::exception {
private:
    string message;

public:
    ReadFailException(string msg) : message(msg) {}
    string what() {
        return message;
    }
};