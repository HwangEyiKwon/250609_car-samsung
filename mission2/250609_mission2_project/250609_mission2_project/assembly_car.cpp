#include "gmock/gmock.h"
#include "car.h"

using namespace testing;

class MockCar : public Car {
public:
	MOCK_METHOD(int, getSum, (int a, int b), ());
};

TEST(Group, TC1) {
	Car car;

	int ret = car.getSum(10, 20);

	EXPECT_EQ(30, ret);
}

TEST(Group, TC2) {
	MockCar mock;

	EXPECT_CALL(mock, getSum(1, 2)).WillRepeatedly(Return(999));

	int ret = mock.getSum(1, 2);
	EXPECT_EQ(999, ret);
}