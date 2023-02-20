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
* Game functions header file
*
*/

#pragma once

void printMenu();
bool isValidDirection(const char* input);
void moveUp(size_t** matrix, size_t n);
void moveDown(size_t** matrix, size_t n);
void moveRight(size_t ** matrix, size_t n);
void moveLeft(size_t** matrix, size_t n);
void performMove(size_t** matrix, size_t n, char dir);
void updateLeaderboard(size_t dimension, char* name, size_t score);
void generateRandom(size_t** m, size_t n, size_t currentScore);
bool hasSameNeighbours(size_t** board, size_t dimension);
bool isMovePossible(size_t** board, size_t dimension);
void play();
void leaderboard();
void startGame();

