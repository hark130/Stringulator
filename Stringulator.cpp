#include "Stringulator.h"
#include <regex>


/****************************************************************************/
/***************************** PUBLIC FUNCTIONS *****************************/
/****************************************************************************/


StringNum::StringNum(std::string strNum)
{
	std::smatch m;
	std::regex nonNumbers (R"([^0-9])");

	if (!std::regex_search(strNum, m, nonNumbers))
	{
		strAsNum = strNum;	
	}
	else
	{
		strAsNum = std::string("");
	}	
}


void StringNum::setStringNum(std::string strNum)
{
	std::smatch m;
	std::regex nonNumbers (R"([^0-9])");

	if (!std::regex_search(strNum, m, nonNumbers))
	{
		strAsNum = strNum;	
	}
	else
	{
		strAsNum = std::string("");
	}	

	return;
}


std::string StringNum::getStringNum(void)
{
	return strAsNum;
}


void StringNum::addOne(void)
{
	bool addOne = true;
	auto number = strAsNum.end();

	if (strAsNum.length() > 0)
	{
		for (; number != strAsNum.begin(); --number)
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
		}

		// Number string becomes longer
		if (number == strAsNum.begin() && addOne)
		{
			strAsNum = "1" + strAsNum;
		}
	}

	return;
}


/****************************************************************************/
/**************************** PRIVATE FUNCTIONS *****************************/
/****************************************************************************/

