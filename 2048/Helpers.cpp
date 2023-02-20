#include "Helpers.h"
#include "StringUtils.h"
#include <iostream>
#include "ConstValues.h"
#include "Leaderboard.h"

void swapInteger(size_t& first, size_t& second) {
	size_t temp = first;
	first = second;
	second = temp;
}

void swap(char first[], char second[]) {
	char* temp = new char[strLen(first) + 1];
	strCpy(temp, first);
	strCpy(first, second);
	strCpy(second, temp);
	delete[] temp;
}

void selectionSort(size_t count, size_t scores[], char names[MAX_PLAYERS_LEADERBOARD + 1][BUFFER_SIZE])
{
	for (size_t i = 0; i < count - 1; i++)
	{
		size_t maxInd = i;
		for (size_t j = i + 1; j < count; j++)
		{
			if (scores[j] > scores[maxInd])
			{
				maxInd = j;
			}
		}

		if (maxInd != i)
		{
			swapInteger(scores[i], scores[maxInd]);
			swap(names[i], names[maxInd]);
		}
	}
}

size_t** initializeMatrix(size_t n)
{
	size_t** m = new size_t * [n] {};
	for (size_t i = 0; i < n; i++)
	{
		m[i] = new size_t[n];
		for (size_t j = 0; j < n; j++)
		{
			m[i][j] = 0;
		}
	}

	return m;
}

void freeMatrix(size_t** m, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		delete[] m[i];
	}

	delete[] m;
}

bool hasEmptySpace(size_t** m, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			if (m[i][j] == 0)
			{
				return true;
			}
		}
	}

	return false;
}

size_t sumMatrix(size_t** m, size_t n)
{
	size_t sum = 0;

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			sum += m[i][j];
		}
	}

	return sum;
}

size_t getNumLen(size_t n)
{
	if (n == 0)
	{
		return 1;
	}
	return 1 + getNumLen(n / 10);
}

size_t getMaxElement(size_t** m, size_t n)
{
	size_t max = 0;

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			if (m[i][j] > max)
			{
				max = m[i][j];
			}
		}
	}

	return max;
}

void setw(size_t x, size_t positions)
{
	size_t whitespace = positions - getNumLen(x);
	for (size_t i = 0; i < whitespace; i++)
	{
		std::cout << " ";
	}
	std::cout << x;
}

void printMatrix(size_t** m, size_t n)
{
	size_t positions = getNumLen(getMaxElement(m, n)) + 1;//колкото е най-голямото число плюс едно за спесйче-толкова клетки да освободим
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			setw(m[i][j], positions);
		}
		std::cout << std::endl;
	}
}

char* getFileName(size_t n)
{
	char* fileName = new char[LENGTH_PATH];
	size_t i = 0;
	if (n < 10)
	{
		fileName[i++] = n + DIGIT_TO_CHAR;
	}
	else
	{
		fileName[i++] = n / 10 + DIGIT_TO_CHAR;
		fileName[i++] = n % 10 + DIGIT_TO_CHAR;
	}

	fileName[i++] = '.';
	fileName[i++] = 't';
	fileName[i++] = 'x';
	fileName[i++] = 't';
	fileName[i++] = '\0';

	return fileName;
}

void clearScreen() {
	std::cout << "\033[2J\033[1;1H";
}