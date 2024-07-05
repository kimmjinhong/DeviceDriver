#include<iostream>
#include"DeviceDriver.h"
#include<iostream>

using namespace std;

class Application{
public:
	Application(DeviceDriver* driver)
		:m_driver{ driver } {

	}
	void ReadAndPrint(int startAddr, int endAddr) {
		int result;
		for (int i = startAddr; i <= endAddr; i++) {
			result = m_driver->read(i);
		}
	}

	void WriteAll(int value) {
		for (int addr = 0; addr <= 4; addr++) {
			m_driver->write(addr, value);
		}

	}
private:
	DeviceDriver* m_driver;
};
