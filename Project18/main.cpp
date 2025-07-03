#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;

class MockFlash :public FlashMemoryDevice {
public:
	MockFlash() = default;
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriver, ReadFromHW) {
	// TODO : replace hardware with a Test Double
	MockFlash hardware;
	EXPECT_CALL(hardware, read(0xFF))
		.WillRepeatedly(Return(0));
	DeviceDriver driver{ &hardware };
	int data = driver.read(0xFF);
	EXPECT_EQ(0, data);
}

TEST(DeviceDriver, 5TimesRead) {
	// TODO : replace hardware with a Test Double
	MockFlash hardware;
	EXPECT_CALL(hardware, read(0xFF))
		.Times(5);
	DeviceDriver driver{ &hardware };
	int data = driver.read(0xFF);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}