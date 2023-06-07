#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../cal/cal.cpp"
#include <vector>

using namespace testing;
using namespace std;

TEST(TestCaseName, TC00)
{
	int x = 10;
	EXPECT_THAT(x, Eq(10));
	EXPECT_THAT(x, Ne(11));
	EXPECT_THAT(5, AnyOf(1, 3, 5, 8, 9));

	int arr[] = { 1,2,3,4,5 };
	EXPECT_THAT(3, AnyOfArray(arr));

	EXPECT_THAT(30, Gt(25));
	EXPECT_THAT(30, Lt(35));
	EXPECT_THAT(30, Ne(31));

	double pi = 3.14;
	EXPECT_THAT(pi, DoubleNear(3.1415, 0.1));

	vector<int> arr2 = { 1,3,5,7,9 };
	vector<int> arr3 = { 1,3,5,7,9 };
	EXPECT_THAT(arr2, Contains(3));
	EXPECT_EQ(arr2, arr3);
	EXPECT_THAT(arr2, ContainerEq(arr3));

	vector<int> arr4;
	EXPECT_THAT(arr4, IsEmpty());
}

TEST(TestCaseName, TC01)
{
	Cal c;

	vector<int> arr1 = { 1,5,7 };
	vector<int> arr2 = { 2,6,8 };	
	EXPECT_THAT(c.change(arr1), ContainerEq(arr2));
}

TEST(TestCaseName, TC02)
{
	Cal c;

	vector<int> arr1 = { 1,5,7,9 };
	vector<int> arr2 = { 2,6,8,0 };
	EXPECT_THAT(c.change(arr1), ContainerEq(arr2));
}

TEST(TestCaseName, TC03)
{
	Cal c;

	vector<int> arr1 = { 1,3,5,7 };
	vector<int> arr2 = { 2,5,6,8 };
	EXPECT_THAT(c.change(arr1), ContainerEq(arr2));
}

TEST(TestCaseName, TC04)
{
	Cal c;

	vector<int> arr1 = { 10,5,7 };
	vector<int> arr2 = { 2,6,8 };
	EXPECT_THROW(c.change(arr1), std::invalid_argument);
}

class MockCalculator : public Cal
{
public:
	MOCK_METHOD(int, getSum, (int a, int b), ());
	MOCK_METHOD(int, getValue, (), ());
};

class MockString : public string
{
public:
	MOCK_METHOD(int, length, (), ());
};

TEST(CalTest, CalMock)
{
	MockCalculator mock_cal;

	EXPECT_CALL(mock_cal, getSum(1, 2))
		.Times(2) // for behavior verification
		.WillRepeatedly(Return(100)); // for stubbing

	cout << mock_cal.getSum(1, 2) << "\n";
	cout <<  mock_cal.getSum(1, 2) << "\n";

	MockString mock_str;
	EXPECT_CALL(mock_str, length())
		.WillRepeatedly(Return(1));

	cout << mock_str.length() << "\n";
	cout << mock_str.length() << "\n";

	EXPECT_CALL(mock_cal, getSum);
	cout << mock_cal.getSum(10, 1) << "\n";


	EXPECT_CALL(mock_cal, getSum(1, 2))
		.WillRepeatedly(Return(10));
	cout << mock_cal.getSum(1, 2) << "\n";
	cout << mock_cal.getValue() << "\n";
}

class MockArr : public vector<int>
{
public:
	MOCK_METHOD(int, size, (), ());
};

TEST(CalTest, CalMockArr)
{
	MockArr mock_arr;

	EXPECT_CALL(mock_arr, size)
		.Times(2)
		.WillRepeatedly(Return(100));

	EXPECT_THAT(mock_arr.size(), Eq(100));
	cout << mock_arr.size() << "\n";
}

class TradingMock : public TradingAPI
{
public:
	MOCK_METHOD(string, buy, (), (override));
};

TEST(DBTest, DB00)
{
	TradingMock db_mock;
	EXPECT_CALL(db_mock, buy)
		.WillRepeatedly(Return(string("BOUGHT")));

	TradingSystem system(&db_mock);
	cout << system.getLogMessage("KFC");

	// state °ËÁõ
	EXPECT_THAT(system.getLogMessage("KFC"), Eq("[BOUGHT]KFC\n"));
}
