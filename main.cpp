#include "Stringulator.h"
#include <iostream>
#include <string>

int main(void)
{
	int tempInt = 0;

	StringNum someNum(std::string("This is a test"));
	std::cout << "String is:\t" << someNum.getStringNum() << std::endl;
	someNum.setStringNum(std::string("This is also test"));
	std::cout << "String is:\t" << someNum.getStringNum() << std::endl;
	someNum.setStringNum(std::string("1234"));
	std::cout << "String is:\t" << someNum.getStringNum() << std::endl;
	someNum.addOne();
	std::cout << "1234 + 1 = " << someNum.getStringNum() << std::endl;
	someNum.setStringNum(std::string("789"));
	someNum.addOne();
	std::cout << "789 + 1 = " << someNum.getStringNum() << std::endl;
	someNum.setStringNum(std::string("799"));
	someNum.addOne();
	std::cout << "799 + 1 = " << someNum.getStringNum() << std::endl;
	someNum.setStringNum(std::string("999"));
	someNum.addOne();
	std::cout << "999 + 1 = " << someNum.getStringNum() << std::endl;

	someNum.setStringNum(std::string("0"));
	for (int i = 1; i <= 10; ++i)
	{
		std::cout << someNum.getStringNum() << " + " << i << " = ";
		someNum.addNum(i);
		std::cout << someNum.getStringNum() << std::endl;
	}

	tempInt = 1234567890;
	someNum.setStringNum(std::string("1234567890"));
	std::cout << someNum.getStringNum() << " + " << tempInt << " = ";
	someNum.addNum(tempInt);
	std::cout << someNum.getStringNum() << std::endl;
	
	return 0;
}
