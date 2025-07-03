#include "gmock/gmock.h"
#include "device_driver.h"
#include "application.cpp"
#include <string>

using namespace testing;
using std::string;

class MockFlash :public FlashMemoryDevice {
public:
	MockFlash() = default;
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DDFixture : public Test {
protected:

	MockFlash hardware;
	DeviceDriver driver;
public:

	DDFixture() :driver{ &hardware } {};
};

TEST_F(DDFixture, ReadFromHW) {
	// TODO : replace hardware with a Test Double
	EXPECT_CALL(hardware, read(0xFF))
		.WillRepeatedly(Return(0));
	int data = driver.read(0xFF);
	EXPECT_EQ(0, data);
}

TEST_F(DDFixture, 5TimesRead) {
	// TODO : replace hardware with a Test Double
	EXPECT_CALL(hardware, read(0xFF))
		.Times(5);
	int data = driver.read(0xFF);
}

TEST_F(DDFixture, 5TimesReadButExcept) {
	// TODO : replace hardware with a Test Double
	EXPECT_CALL(hardware, read(0xFF))
		.WillOnce(Return(0))
		.WillRepeatedly(Return(1));
	try {
		int data = driver.read(0xFF);
		FAIL();
	}
	catch (ReadFailException& e) {
		EXPECT_EQ(string{ e.what() }, string{ "Read value is different. Error!" });
	}
}

TEST_F(DDFixture, WriteNormal) {
	// TODO : replace hardware with a Test Double
	EXPECT_CALL(hardware, read(0xAA))
		.Times(1)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(hardware, write(0xAA, _))
		.Times(1);
	driver.write(0xAA, 5);
}

TEST_F(DDFixture, WriteException) {
	// TODO : replace hardware with a Test Double
	EXPECT_CALL(hardware, read(0xAA))
		.Times(1)
		.WillRepeatedly(Return(0xFA));
	EXPECT_CALL(hardware, write(0xAA, _))
		.Times(0);

	try {
		driver.write(0xAA, 5);
		FAIL();
	}
	catch (WriteFailException& e) {
		EXPECT_EQ(string{ e.what() }, string{ "There is another value already. Error!" });
	}
}

TEST_F(DDFixture, TC1) {
	EXPECT_CALL(hardware, read(_))
		.Times(20)
		.WillRepeatedly(Return(0xFA));
	Applicaiton app{&driver};
	app.readAndPrint(0xA0, 0xA4);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}