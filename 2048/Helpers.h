#pragma once

void swapInteger(size_t& first, size_t& second);
void swap(char first[], char second[]);
void selectionSort(size_t count, size_t scores[], char names[MAX_PLAYERS_LEADERBOARD + 1][BUFFER_SIZE]);
size_t** initializeMatrix(size_t n);
void freeMatrix(size_t** m, size_t n);
bool hasEmptySpace(size_t** m, size_t n);
size_t sumMatrix(size_t** m, size_t n);
size_t getNumLen(size_t n);
size_t getMaxElement(size_t** m, size_t n);
void setw(size_t x, size_t positions);
void printMatrix(size_t** m, size_t n);
char* getFileName(size_t n);
void clearScreen();