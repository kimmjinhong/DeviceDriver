#pragma once
#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp"
#include "../DeviceDriver/FlashMemoryDevice.h"

using namespace std;
using namespace testing;

class MockHardware : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class HardwareFixture : public testing::Test {
protected:
	void SetUp() override {
	}
public:
	NiceMock<MockHardware> mock_hw;
};

TEST_F(HardwareFixture, BasicReadCallTest) {
	EXPECT_CALL(mock_hw, read).Times(5);

	DeviceDriver driver(&mock_hw);
	driver.read(0x00);
}

TEST_F(HardwareFixture, ReadExceptionTest) {
	EXPECT_CALL(mock_hw, read(DeviceDriver::READ_FAIL_ADDRESS))
		.WillOnce(Return(0x03))
		.WillOnce(Return(0x03))
		.WillOnce(Return(0x03))
		.WillOnce(Return(0x03))
		.WillOnce(Return(0x04));

	try {
		DeviceDriver driver(&mock_hw);
		int result = driver.read(DeviceDriver::READ_FAIL_ADDRESS);
		FAIL();
	}
	catch(ReadFailException& e){
		//assert
		EXPECT_EQ(string{ e.what() }, string{ "Read Fail" });
	}
}
