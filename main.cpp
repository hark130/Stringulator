#include "Stringulator.h"
#include <iostream>
#include <string>

int main(void)
{
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
	
	return 0;
}
