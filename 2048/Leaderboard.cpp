#include "Helpers.h"
#include "Leaderboard.h"
#include "StringUtils.h"
#include "ConstValues.h"
#include <fstream>
#include <iostream>
#include "Helpers.cpp"

void updateLeaderboard(size_t dimension, char* name, size_t score)
{
	size_t count = 0;
	char* fileName = getFileName(dimension);
	std::ifstream leaderboardFile(fileName);
	//std::ifstream е тип на променливата
//leaderboardFile е име или обекта на променливата
//поддава се параметъра fileName(комструктор)
//променливата е инстация от класа(поъок) ifstream

	char names[MAX_PLAYERS_LEADERBOARD + 1][BUFFER_SIZE];
	size_t scores[MAX_PLAYERS_LEADERBOARD + 1];
	char buffer[BUFFER_SIZE];
	//този буфер го ползвам само за да прочета линия ипосле да парсвам(предотвратявам невалидно число)

	bool shouldAdd = true;

	if (leaderboardFile.is_open())
	{
		leaderboardFile.getline(buffer, BUFFER_SIZE);
		count = parseNum(buffer);
		for (size_t i = 0; i < count; i++)
		{
			leaderboardFile.getline(buffer, BUFFER_SIZE);
			scores[i] = parseNum(buffer);
			leaderboardFile.getline(names[i], BUFFER_SIZE);
			if (strCmp(names[i], name) == 0)
			{
				shouldAdd = false;
				if (score > scores[i])
				{
					scores[i] = score;
				}
			}
		}

		leaderboardFile.close();
	}

	if (shouldAdd)
	{
		strCpy(names[count], name);
		scores[count] = score;
		count++;
	}
	selectionSort(count, scores, names);

	if (count > MAX_PLAYERS)
	{
		count = MAX_PLAYERS;
	}

	std::ofstream leaderboardFileOut(fileName);
	if (leaderboardFileOut.is_open())
	{
		leaderboardFileOut << count << std::endl;
		for (size_t i = 0; i < count; i++)
		{
			leaderboardFileOut << scores[i] << std::endl;
			leaderboardFileOut << names[i] << std::endl;
		}

		leaderboardFileOut.close();
	}

	delete[] fileName;
}

void leaderboardMenu()
{
	std::cout << "Enter dimension you want to see leaderboard in: ";
	int dimension = inputNum();
	while (dimension < LOWER_BOUND_DIMENSION || dimension> UPPER_BOUND_DIMENSION)
	{
		void clearScreen();
		std::cout << "Invalid dimension! Should be a number between 4  and 10.\n" <<
			"Enter new: ";
		dimension = inputNum();
	}

	size_t count = 0;
	char* fileName = getFileName(dimension);
	std::ifstream leaderboardFile(fileName);

	char name[BUFFER_SIZE];//едно име пазим-масив от чарове
	size_t score;
	char buffer[BUFFER_SIZE];

	if (leaderboardFile.is_open())
	{
		leaderboardFile.getline(buffer, BUFFER_SIZE);
		count = parseNum(buffer);
		for (size_t i = 0; i < count; i++)
		{
			leaderboardFile.getline(buffer, BUFFER_SIZE);
			score = parseNum(buffer);
			leaderboardFile.getline(name, BUFFER_SIZE);
			std::cout << (i + 1) << ". " << score << " " << name << std::endl;
		}

		leaderboardFile.close();
		std::cout << "---------" << std::endl << std::endl;
	}
	else
	{
		std::cout << "No leaderboard for the current dimension selected." <<
			std::endl << std::endl;
	}

	delete[] fileName;
}