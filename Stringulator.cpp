#include "Stringulator.h"
#include <regex>


/****************************************************************************/
/***************************** PUBLIC FUNCTIONS *****************************/
/****************************************************************************/


StringNum::StringNum(std::string strNum)
{

		strAsNum = strNum;	

		check_it();
}


void StringNum::setStringNum(std::string strNum)
{
	strAsNum = strNum;	

	check_it();

	return;
}


std::string StringNum::getStringNum(void)
{
	check_it();

	return strAsNum;
}


void StringNum::addOne(void)
{
	bool addOne = true;
	auto number = strAsNum.end();

	if (check_it())
	{
		while(1)
		{
			// Start adding at the ones place
			if (addOne)
			{
				if (*number == '0') { *number = '1'; addOne = false; }
				else if (*number == '1') { *number = '2'; addOne = false; }
				else if (*number == '2') { *number = '3'; addOne = false; }
				else if (*number == '3') { *number = '4'; addOne = false; }
				else if (*number == '4') { *number = '5'; addOne = false; }
				else if (*number == '5') { *number = '6'; addOne = false; }
				else if (*number == '6') { *number = '7'; addOne = false; }
				else if (*number == '7') { *number = '8'; addOne = false; }
				else if (*number == '8') { *number = '9'; addOne = false; }
				else if (*number == '9') { *number = '0'; }
				else { } // Something is wrong
			}

			if (!addOne)
			{
				break;
			}

			// Number string becomes longer
			if (number == strAsNum.begin() && addOne)
			{
				strAsNum = "1" + strAsNum;
				addOne = false;
				break;
			}

			if (number != strAsNum.begin())
			{
				--number;  // Decrement the iterator
			}
			else
			{
				break;
			}
		}
	}

	return;
}


/****************************************************************************/
/**************************** PRIVATE FUNCTIONS *****************************/
/****************************************************************************/


bool StringNum::check_it(void)
{
	bool retVal = false;

	std::smatch m;
	std::regex nonNumbers (R"([^0-9])");

	if (!std::regex_search(strAsNum, m, nonNumbers) && strAsNum.length() > 0)
	{
		retVal = true;
	}
	else
	{
		strAsNum = "";
	}

	return retVal;
}
