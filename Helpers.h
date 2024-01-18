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
* Helper functions header file
*
*/

#pragma once
#include <cstddef>

void swap(size_t& first, size_t& second);
void swap(char first[], char second[]);
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