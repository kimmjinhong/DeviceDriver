#pragma once
#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp"
#include "../DeviceDriver/Application.cpp"
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
	static const int READ_FAIL_ADDRESS = 0x100;
	static const int WRITE_FAIL_ADDRESS = 0x200;
};

TEST_F(HardwareFixture, BasicReadCallTest) {
	EXPECT_CALL(mock_hw, read).Times(5);

	DeviceDriver driver(&mock_hw);
	driver.read(0x01);
}

TEST_F(HardwareFixture, ReadExceptionTest) {
	EXPECT_CALL(mock_hw, read(READ_FAIL_ADDRESS))
		.WillOnce(Return(0x03))
		.WillOnce(Return(0x03))
		.WillOnce(Return(0x03))
		.WillOnce(Return(0x03))
		.WillOnce(Return(0x04));

	try {
		DeviceDriver driver(&mock_hw);
		int result = driver.read(READ_FAIL_ADDRESS);
		FAIL();
	}
	catch(ReadFailException& e){
		//assert
		EXPECT_EQ(string{ e.what() }, string{ "Read Fail" });
	}
}

TEST_F(HardwareFixture, BasicWriteCallTest) {
		DeviceDriver driver(&mock_hw);
		EXPECT_CALL(mock_hw, read(0x00))
			.Times(1)
			.WillRepeatedly(Return(0xff));

		driver.write(0x00, 'a');
}

TEST_F(HardwareFixture, WriteExceptionTest) {
	DeviceDriver driver(&mock_hw);
	EXPECT_CALL(mock_hw, read(WRITE_FAIL_ADDRESS))
		.Times(1)
		.WillRepeatedly(Return(0xfa));
	EXPECT_THROW({
			driver.write(WRITE_FAIL_ADDRESS, 'a');
		}, WriteFailException);
}

TEST_F(HardwareFixture, BasicApplicationReadAndPrintTest) {
	DeviceDriver driver(&mock_hw);
	Application app(&driver);
	int startAddr = 0x10;
	int endAddr = 0x20;
	for (int i = startAddr; i <= endAddr; i++) {
		EXPECT_CALL(mock_hw, read(i))
			.Times(5)
			.WillRepeatedly(Return(i));
	}
	app.ReadAndPrint(startAddr, endAddr);
}

TEST_F(HardwareFixture, ApplicationWriteAll) {
	DeviceDriver driver(&mock_hw);
	Application app(&driver);

	int startAddr = 0x00;
	int endAddr = 0x04;
	EXPECT_CALL(mock_hw, read(_))
		.Times(5)
		.WillRepeatedly(Return(0xff));
	app.WriteAll('a');
}
