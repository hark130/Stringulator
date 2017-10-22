#include "Stringulator.h"
#include <climits>		// UINT_MAX
#include <iostream>
#include <string>

#define NUM_RUNS 200
// UINT_MAX == 4294967295
#define LARGE_NUM 10000

int main(void)
{
	// int tempInt = 0;

	StringNum someNum(std::string("This is a test"));
	// std::cout << "String is:\t" << someNum.getStringNum() << std::endl;
	// someNum.setStringNum(std::string("This is also test"));
	// std::cout << "String is:\t" << someNum.getStringNum() << std::endl;
	// someNum.setStringNum(std::string("1234"));
	// std::cout << "String is:\t" << someNum.getStringNum() << std::endl;
	// someNum.addOne();
	// std::cout << "1234 + 1 = " << someNum.getStringNum() << std::endl;
	// someNum.setStringNum(std::string("789"));
	// someNum.addOne();
	// std::cout << "789 + 1 = " << someNum.getStringNum() << std::endl;
	// someNum.setStringNum(std::string("799"));
	// someNum.addOne();
	// std::cout << "799 + 1 = " << someNum.getStringNum() << std::endl;
	// someNum.setStringNum(std::string("999"));
	// someNum.addOne();
	// std::cout << "999 + 1 = " << someNum.getStringNum() << std::endl;

	// someNum.setStringNum(std::string("0"));
	// for (int i = 1; i <= 10; ++i)
	// {
	// 	std::cout << someNum.getStringNum() << " + " << i << " = ";
	// 	someNum.addNum(i);
	// 	std::cout << someNum.getStringNum() << std::endl;
	// }

	// tempInt = 1234567890;
	// someNum.setStringNum(std::string("1234567890"));
	// std::cout << someNum.getStringNum() << " + " << tempInt << " = ";
	// someNum.addNum(tempInt);
	// std::cout << someNum.getStringNum() << std::endl;

	someNum.setStringNum(std::string("0"));
	std::cout << "STARTING TEST" << std::endl;
	unsigned long long oldNum = 0;
	unsigned long long newNum = 0;
	for (int i = 0; i <= NUM_RUNS; ++i)
	{
		oldNum = newNum;
		// someNum.addNum(UINT_MAX);
		///////////////////////////////////////////////////////
		// .addNum() doesn't work properly for values > 9!!! //
		///////////////////////////////////////////////////////
		// someNum.addNum(9);
		// someNum.addNum(10);
		// someNum.addNum(UINT_MAX);
		// std::cout << "UINT_MAX / 2 == " << UINT_MAX / 2 << std::endl;  // DEBUGGING
		// someNum.addNum(UINT_MAX / 2);
		someNum.addNum(LARGE_NUM);
		newNum = stoll(someNum.getStringNum());
		// std::cout << "oldNum:\t" << oldNum << std::endl;
		std::cout << "newNum:\t" << newNum << std::endl;
		if (newNum <= oldNum)
		{
			std::cout << "oldNum >= newNum!!!" << std::endl;
			break;
		}
	}
	
	return 0;
}
