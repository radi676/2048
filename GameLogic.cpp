/**
 *
 * Solution to course project #4
 * Introduction to programming course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2022/2023
 *
 * @author Radina Ovcharova
 * @idnumber 3MI0600151
 * @compiler VC
 *
 * Main game logic
 *
 */

#include <iostream>
#include <fstream>
#include "GameLogic.h"
#include "StringUtils.h"
#include "Helpers.h"
#include "ConstValues.h"
#include <cstddef>

void printMenu()
{
	std::cout << "1. Start game" << std::endl;
	std::cout << "2. Leaderboard" << std::endl;
	std::cout << "3. Quit" << std::endl;
	std::cout << std::endl;
	std::cout << "*********************" << std::endl;
	std::cout << "Choose from the menu :)" << std::endl;
	std::cout << "*********************" << std::endl;
	std::cout << "->   <-\n";
	std::cout << "\033[F-> ";
}

bool isValidDirection(const char *input)
{
	if (strLen(input) != 1)
	{
		return false;
	}

	return input[0] == MOVE_UP || input[0] == MOVE_LEFT || input[0] == MOVE_DOWN || input[0] == MOVE_RIGHT;
}

void moveUp(size_t **matrix, size_t n)
{
	for (size_t col = 0; col < n; col++)
	{
		size_t toMove = 0;
		for (size_t row = 0; row < n; row++)
		{
			if (matrix[row][col] == 0)
			{
				continue;
			}

			matrix[toMove][col] = matrix[row][col];
			if (row != toMove)
			{
				matrix[row][col] = 0;
			}
			toMove++;
		}
	}
}

void moveDown(size_t **matrix, size_t n)
{
	for (size_t col = 0; col < n; col++)
	{
		size_t toMove = n - 1;
		for (int row = n - 1; row >= 0; row--)
		{
			if (matrix[row][col] == 0)
			{
				continue;
			}

			matrix[toMove][col] = matrix[row][col];
			if (row != toMove)
			{
				matrix[row][col] = 0;
			}
			toMove--;
		}
	}
}

void moveRight(size_t **matrix, size_t n)
{
	for (size_t row = 0; row < n; row++)
	{
		size_t toMove = n - 1;
		for (int col = n - 1; col >= 0; col--)
		{
			if (matrix[row][col] == 0)
			{
				continue;
			}

			matrix[row][toMove] = matrix[row][col];
			if (col != toMove)
			{
				matrix[row][col] = 0;
			}
			toMove--;
		}
	}
}

void moveLeft(size_t **matrix, size_t n)
{
	for (size_t row = 0; row < n; row++)
	{
		size_t toMove = 0;
		for (size_t col = 0; col < n; col++)
		{
			if (matrix[row][col] == 0)
			{
				continue;
			}

			matrix[row][toMove] = matrix[row][col];
			if (col != toMove)
			{
				matrix[row][col] = 0;
			}
			toMove++;
		}
	}
}

void performMove(size_t **matrix, size_t n, char dir)
{
	if (dir == MOVE_UP)
	{
		moveUp(matrix, n);
		for (size_t row = 0; row < n - 1; row++)
		{
			for (size_t col = 0; col < n; col++)
			{
				if (matrix[row][col] == matrix[row + 1][col] ||
					matrix[row][col] == 0)
				{
					matrix[row][col] += matrix[row + 1][col];
					matrix[row + 1][col] = 0;
				}
			}
		}
		moveUp(matrix, n);
	}

	else if (dir == MOVE_LEFT)
	{
		moveLeft(matrix, n);
		for (size_t col = 0; col < n - 1; col++)
		{
			for (size_t row = 0; row < n; row++)
			{
				if (matrix[row][col] == matrix[row][col + 1] ||
					matrix[row][col] == 0)
				{
					matrix[row][col] += matrix[row][col + 1];
					matrix[row][col + 1] = 0;
				}
			}
		}
		moveLeft(matrix, n);
	}
	else if (dir == MOVE_DOWN)
	{
		moveDown(matrix, n);
		for (int row = n - 1; row > 0; row--)
		{
			for (size_t col = 0; col < n; col++)
			{
				if (matrix[row][col] == matrix[row - 1][col] ||
					matrix[row][col] == 0)
				{
					matrix[row][col] += matrix[row - 1][col];
					matrix[row - 1][col] = 0;
				}
			}
		}
		moveDown(matrix, n);
	}

	else if (dir == MOVE_RIGHT)
	{
		moveRight(matrix, n);
		for (int col = n - 1; col > 0; col--)
		{
			for (size_t row = 0; row < n; row++)
			{
				if (matrix[row][col] == matrix[row][col - 1] ||
					matrix[row][col] == 0)
				{
					matrix[row][col] += matrix[row][col - 1];
					matrix[row][col - 1] = 0;
				}
			}
		}
		moveRight(matrix, n);
	}
}

void updateLeaderboard(size_t dimension, char *name, size_t score)
{
	size_t count = 0;
	char *fileName = getFileName(dimension);
	std::ifstream leaderboardFile(fileName);

	char names[MAX_PLAYERS_LEADERBOARD + 1][BUFFER_SIZE];
	size_t scores[MAX_PLAYERS_LEADERBOARD + 1];
	char buffer[BUFFER_SIZE];

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
			swap(scores[i], scores[maxInd]);
			swap(names[i], names[maxInd]);
		}
	}

	if (count > 5)
	{
		count = 5;
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

void generateRandom(size_t **m, size_t n, size_t currentScore)
{
	srand(time(0));
	size_t row, col;
	do
	{
		row = rand() % n;
		col = rand() % n;
	} while (m[row][col] != 0);

	size_t start = 0;
	size_t end = 0;
	if (currentScore < CURRENT_SCORE_GENERATOR_LOWER_VALUES)
	{
		start = 0;
		end = 5;
	}
	else if (currentScore < CURRENT_SCORE_GENERATOR_HIGHER_VALUES)
	{
		start = 4;
		end = 9;
	}
	else
	{
		start = 6;
		end = 11;
	}

	size_t options[] = {2, 2, 2, 2, 4, 4, 4, 4, 8, 8, 8, 8};
	m[row][col] = options[rand() % (end - start + 1) + start];
}

bool hasSameNeighbours(size_t **board, size_t dimension)
{
	for (size_t i = 0; i < dimension; i++)
	{
		for (size_t j = 0; j < dimension; j++)
		{
			if ((j + 1 < dimension && board[i][j] == board[i][j + 1]) ||
				(i + 1 < dimension && board[i][j] == board[i + 1][j]))
			{
				return true;
			}
		}
	}

	return false;
}

bool isMovePossible(size_t **board, size_t dimension)
{
	return hasEmptySpace(board, dimension) || hasSameNeighbours(board, dimension);
}

void play()
{
	std::cout << "Enter your nickname: ";
	char *name = inputStr();
	std::cout << "Enter dimension you want to play in: ";
	int dimension = inputNum();
	while (dimension < LOWER_BOUND_DIMENSION || dimension > UPPER_BOUND_DIMENSION)
	{
		clearScreen();
		std::cout << "Invalid dimension! Should be a number between 4  and 10.\n"
				  << "Enter new: ";
		dimension = inputNum();
	}

	size_t **board = initializeMatrix(dimension);
	size_t score = 0;
	while (isMovePossible(board, dimension))
	{
		score = sumMatrix(board, dimension);

		if (hasEmptySpace(board, dimension))
		{
			generateRandom(board, dimension, score);
		}

		clearScreen();
		printMatrix(board, dimension);
		std::cout << "Current score: " << score << std::endl;
		std::cout << "Enter direction: ";
		char *dirInput = inputStr();
		while (!isValidDirection(dirInput))
		{
			std::cout << "Invalid direction! Enter new direction: ";
			delete[] dirInput;
			dirInput = inputStr();
		}

		performMove(board, dimension, dirInput[0]);
		delete[] dirInput;
	}

	score = sumMatrix(board, dimension);
	std::cout << "Game finished! Your final score is: " << score << std::endl
			  << std::endl;
	updateLeaderboard(dimension, name, score);
	delete[] name;
	freeMatrix(board, dimension);
}

void leaderboard()
{
	std::cout << "Enter dimension you want to see leaderboard in: ";

	int dimension = inputNum();
	while (dimension < LOWER_BOUND_DIMENSION || dimension > UPPER_BOUND_DIMENSION)
	{
		void clearScreen();
		std::cout << "Invalid dimension! Should be a number between 4  and 10.\n"
				  << "Enter new: ";
		dimension = inputNum();
	}

	size_t count = 0;
	char *fileName = getFileName(dimension);
	std::ifstream leaderboardFile(fileName);

	char name[BUFFER_SIZE];
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
		std::cout << "---------" << std::endl
				  << std::endl;
	}
	else
	{
		std::cout << "No leaderboard for the current dimension selected." << std::endl
				  << std::endl;
	}

	delete[] fileName;
}

void startGame()
{
	while (true)
	{
		printMenu();
		int option = inputNum();

		switch (option)
		{
		case 1:
			clearScreen();
			play();
			break;

		case 2:
			clearScreen();
			leaderboard();
			break;

		case 3:
			clearScreen();
			std::cout << "Come to play again!:)" << std::endl;
			return;

		default:
			clearScreen();
			std::cout << "Invalid option! Please choose again!" << std::endl
					  << std::endl;
			break;
		}
	}
}
