#ifndef __STRINGULATOR_H__
#define __STRINGULATOR_H__

#include <string>

class StringNum
{
	public:
		StringNum(std::string strNum);  // ctor
		void setStringNum(std::string strNum);
		std::string getStringNum(void);
		void addOne(void);
		void addNum(unsigned int num);
		void addStrNum(StringNum strNum);

	private:
		std::string strAsNum;

		bool check_it(void);
		char increment_char(char num, int numToAdd, int* carryVal);
		unsigned int get_position_value(unsigned int value, int digitNum);
		int count_num_digits(unsigned int value);
};

#endif  // __STRINGULATOR_H__