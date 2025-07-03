#include <vector>
#include <iostream>
#include "device_driver.h"

class Applicaiton {
public:
	Applicaiton(DeviceDriver* driver)
		: driver{ driver } { }

	void readAndPrint(const int startAddr, const int endAddr) {
		for (int addr = startAddr; addr <= endAddr; addr++) {
			std::cout << driver->read(addr);
		}
	}

	void writeAll(const int value) {
		for (int addr = 0x00; addr <= 0x04; addr++) {
			driver->write(addr, value);
		}
	}
private:
	DeviceDriver* driver;
};