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
* String helper functions header file
*
*/

#pragma once

void strCpy(char* dest, char* source);
char* inputStr();
int inputNum();
int parseNum(const char* input);
size_t strLen(const char* str);
int strCmp(const char* first, const char* second);