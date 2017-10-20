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

	private:
		std::string strAsNum;

		

};

#endif  // __STRINGULATOR_H__