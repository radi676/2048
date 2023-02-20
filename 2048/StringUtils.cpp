#include "StringUtils.h"
#include <iostream>
#include "ConstValues.h"

void strCpy(char* dest, char* source)
{
	size_t index = 0;
	while (source[index] != '\0')
	{
		dest[index] = source[index];
		index++;
	}

	dest[index] = '\0';
}

char* inputStr()
{
	char* input = new char[BUFFER_SIZE];
	std::cin.getline(input, BUFFER_SIZE);
	return input;
}

int inputNum()
{
	char* input = inputStr();
	int result = parseNum(input);
	delete[] input;
	return result;
}

int parseNum(const char* input) 
{
	size_t iter = 0;
	size_t result = 0;
	while (input[iter] != '\0')
	{
		if (input[iter] < '0' || input[iter]>'9')
		{
			return -1;
		}

		result = result * 10 + input[iter] - DIGIT_TO_CHAR;
		iter++;
	}

	return result;
}


size_t strLen(const char* str)
{
	size_t len = 0;
	while (str[len++] != '\0');
	return len - 1;
}

int strCmp(const char* first, const char* second)
{
	while (*first != '\0' && *second != '\0' && *first == *second) {
		first++;
		second++;
	}

	return *first - *second;
}