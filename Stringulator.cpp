#include "Stringulator.h"
#include <climits>		// UINT_MAX
#include <cmath>
#include <iostream>		// cout
#include <iterator>		// distance
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
	int i = 1;  // Iterating variable
	int j = 1;  // Iterating variable
	auto number = strAsNum.end();
	--number;  // No longer pointing *past* the end
	int carryOver = 0;
	int placeValue = 0;
	std::string tempString = "";
	StringNum tempStringNum("0");

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
			// std::cout << "Place value at " << i << " is " << placeValue << std::endl;  // DEBUGGING
			// std::cout << "Pre-increment digit at position " << i << " is " << *number << std::endl;  // DEBUGGING
			*number = increment_char(*number, placeValue, &carryOver);
			// std::cout << "Post-increment digit at position " << i << " is " << *number << std::endl;  // DEBUGGING

			if (carryOver)
			{
				// std::cout << "Entering carry over condition" << std::endl;  // DEBUGGING
				// std::cout << "Pre-increment num:\t" << num << std::endl;  // DEBUGGING
				// OLD VERSION... sometimes overflows the unsigned integer
				// if (num == UINT_MAX || UINT_MAX - num < (carryOver * pow(10, i)))
				// {
				// 	std::cout << "OVERFLOW CONDITION EXISTS!1!" << std::endl;
				// }
				// else
				// {
				// 	num += (carryOver * pow(10, i));
				// }
				// NEW VERSION... 
				tempString = std::to_string(carryOver);
				for (j = i; j > 0; --j)
				{
					tempString = tempString + "0";
				}
				// std::cout << "Carry over is adding " << tempString << " to " << strAsNum << std::endl;  // DEBUGGING
				//////////////////////////////////////////////////////////////
				// IMPLEMENT .addStrNum() method then add it here!!! /////////
				//////////////////////////////////////////////////////////////
				tempStringNum.setStringNum(tempString);
				addStrNum(tempStringNum);

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


void StringNum::addStrNum(StringNum strNum)
{
	/* LOCAL VARIABLES */
	std::string::iterator origNum;  // strAsNum iterator
	std::string::iterator plusNum;  // strNum iterator
	std::string strToAdd;			// Will hold the string from strNum
	std::string tempString = "";	// temp string object for carry over conversion
	StringNum tempStringNum("0");	// temp stringNum object for carry over addition
	int carryOver = 0;				// Holds carry over value from increment_char()
	int i = 0;						// Will hold current index in carry over situation
	int j = 0;						// Iterating variable
	//////////////////////////////////////////////////////////////////////////
	// REDEFINE i TO HOLD THE CURRENT LENGTH OF THE STRING SINCE THE ITERATORS ARE SO UNRELIABLE?!?!
	//////////////////////////////////////////////////////////////////////////	

	if (check_it())
	{
		// Adjust lengths as needed
		while (strNum.getStringNum().length() > strAsNum.length())
		{
			strAsNum = "0" + strAsNum;
		}

		// Setup necessary variables
		origNum = strAsNum.end();
		--origNum;
		strToAdd = strNum.getStringNum();
		std::cout << "strToAdd.length() == " << strToAdd.length() << std::endl;  // DEBUGGING
		std::cout << "strAsNum.length() == " << strAsNum.length() << std::endl;  // DEBUGGING
		// plusNum = strNum.getStringNum().end();
		plusNum = strToAdd.end();
		--plusNum;
		std::cout << "STARTING *origNum == " << *origNum << "\tSTARTING *plusNum == " << *plusNum << std::endl;  // DEBUGGING
		std::cout << "std::distance(origNum, strAsNum.begin()) == " << std::distance(origNum, strAsNum.begin()) << std::endl;  // DEBUGGING
		std::cout << "std::distance(plusNum, strNum.getStringNum().begin()) == " << std::distance(plusNum, strNum.getStringNum().begin()) << std::endl;  // DEBUGGING
		std::cout << "std::distance(origNum, strAsNum.end()) == " << std::distance(origNum, strAsNum.end()) << std::endl;  // DEBUGGING
		std::cout << "std::distance(plusNum, strNum.getStringNum().end()) == " << std::distance(plusNum, strNum.getStringNum().end()) << std::endl;  // DEBUGGING
		std::cout << "strNum == " << strNum.getStringNum() << std::endl;  // DEBUGGING

		// Perform addition
		while (1)
		{
			if (*plusNum != '0')
			{
				std::cout << ".addStrNum():\tEntering increment_char()" << std::endl;  // DEBUGGING
				std::cout << "*origNum == " << *origNum << "\t*plusNum == " << *plusNum << std::endl;  // DEBUGGING
				*origNum = increment_char(*origNum, *plusNum, &carryOver);
			}
			else
			{
				std::cout << "SKIPPING *origNum == " << *origNum << "\t*plusNum == " << *plusNum << std::endl;  // DEBUGGING
			}

			if (carryOver)
			{
				i = std::distance(origNum, strAsNum.end() - 1);
				tempString = std::to_string(carryOver);

				for (j = i; j > 0; --j)
				{
					tempString = tempString + "0";
				}
				tempStringNum.setStringNum(tempString);
				addStrNum(tempStringNum);
				carryOver = 0;

				// Reset strAsNum iterator
				origNum = strAsNum.end();
				--origNum;
				for (j = i; j > 0; --j)
				{
					std::cout << "RESET *origNum == " << *origNum << std::endl;  // DEBUGGING
					--origNum;
				}
			}

			// if (origNum == (strAsNum.begin() - 1) || (plusNum == (strNum.getStringNum().begin() - 1)))
			// if (origNum < strAsNum.begin() || plusNum < strNum.getStringNum().begin())
			if (0 >= std::distance(origNum, strAsNum.begin()) || 0 >= std::distance(plusNum, strNum.getStringNum().begin()))
			{
				std::cout << "std::distance(origNum, strAsNum.begin()) == " << std::distance(origNum, strAsNum.begin()) << std::endl;  // DEBUGGING
				std::cout << "std::distance(plusNum, strNum.getStringNum().begin()) == " << std::distance(plusNum, strNum.getStringNum().begin()) << std::endl;  // DEBUGGING
				std::cout << "BREAKING *origNum == " << *origNum << "\t*plusNum == " << *plusNum << std::endl;  // DEBUGGING
				break;
			}
			else
			{
				--origNum;
				--plusNum;
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
	// std::cout << "The digit at position " << digitNum << " in value " << value << " is " << retVal << std::endl;  // DEBUGGING

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
