#include "Stringulator.h"
#include <climits>		// UINT_MAX
#include <cmath>
#include <iostream>		// cout
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
	--number;  // No longer pointing *past* the end

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
				else { }  // Something is wrong
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


void StringNum::addNum(unsigned int num)
{
	/* LOCAL VARIABLES */
	int numDigits = 0;
	int i = 1;
	auto number = strAsNum.end();
	--number;  // No longer pointing *past* the end
	int carryOver = 0;
	int placeValue = 0;

	/* INPUT VALIDATION */
	if (num == 1)
	{
		addOne();
	}
	else if (num > 1)
	{
		numDigits = count_num_digits(num);

		while (1)
		{
			// Extend the strAsNum as necessary
			while (numDigits > strAsNum.length())
			{
				// std::cout << "Extending strAsNum" << std::endl;  // DEBUGGING
				strAsNum = "0" + strAsNum;
				// std::cout << "strAsNum now == " << strAsNum << std::endl;  // DEBUGGING
				number = strAsNum.end();
				--number;
			}
			// std::cout << "Run #" << i << ":\t*number == " << *number << std::endl;  // DEBUGGING
			placeValue = get_position_value(num, i);
			std::cout << "Place value at " << i << " is " << placeValue << std::endl;  // DEBUGGING
			// std::cout << "Pre-increment digit at position " << i << " is " << *number << std::endl;  // DEBUGGING
			*number = increment_char(*number, placeValue, &carryOver);
			// std::cout << "Post-increment digit at position " << i << " is " << *number << std::endl;  // DEBUGGING

			if (carryOver)
			{
				std::cout << "Entering carry over condition" << std::endl;  // DEBUGGING
				// std::cout << "Pre-increment num:\t" << num << std::endl;  // DEBUGGING
				if (num == UINT_MAX || UINT_MAX - num < (carryOver * pow(10, i)))
				{
					std::cout << "OVERFLOW CONDITION EXISTS!1!" << std::endl;
				}
				else
				{
					num += (carryOver * pow(10, i));
				}
				// std::cout << "Post-increment num:\t" << num << std::endl;  // DEBUGGING
				numDigits = count_num_digits(num);
				if (number == strAsNum.begin())
				{
					strAsNum = std::to_string(carryOver + strAsNum[i]) + strAsNum;
				}
				carryOver = 0;	
			}

			if (i == numDigits || number == (strAsNum.begin() - 1))
			{
				break;
			}
			else
			{
				++i;
				--number;
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
		// std::cout << "BAD strAsNum == " << strAsNum << std::endl;  // DEBUGGING
		strAsNum = "";
	}

	return retVal;
}


char StringNum::increment_char(char num, int numToAdd, int* carryVal)
{
	char retVal = num;

	if (num >= 48 && num <= 57  			// Char is a num
		&& numToAdd >= 1 && numToAdd < 10 	// numToAdd is appropriate
		&& carryVal)						// Pointer is valid
	{
		// retVal = (char)(((int)((int)num + numToAdd) % 96) + 48);
		retVal = num + numToAdd;
		
		// Verify we didn't 'overflow' a "number"
		if (retVal > 57)
		{
			retVal -= 10;
		}

		if (retVal < num)
		{
			*carryVal = 1;
		}
		else
		{
			*carryVal = 0;
		}
	}

	return retVal;
}


unsigned int StringNum::get_position_value(unsigned int value, int digitNum)
{
	int retVal = value;
	// std::cout << "value == " << value << std::endl;  // DEBUGGING
	int numDigits = count_num_digits(value);

	/* INPUT VALIDATION */
	if (value && digitNum > 0 && digitNum <= numDigits)
	{
		// retVal = (unsigned int)((value % (unsigned int)pow(10, digitNum)) - (unsigned int)(value % (unsigned int)pow(10, digitNum - 1))) / (unsigned int)pow(10, digitNum - 1);
		retVal = (value % (unsigned int)pow(10, digitNum));
		retVal -= (unsigned int)(value % (unsigned int)pow(10, digitNum - 1));
		retVal /= (unsigned int)pow(10, digitNum - 1);
	}
	std::cout << "The digit at position " << digitNum << " in value " << value << " is " << retVal << std::endl;  // DEBUGGING

	return retVal;
}


int StringNum::count_num_digits(unsigned int value)
{
	int retVal = 0;

	while(value)
	{
		value = value / 10;
		++retVal;
	}

	return retVal;
}
