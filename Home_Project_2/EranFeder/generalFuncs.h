#pragma once

#define MAX_STR_LENGTH 254

typedef unsigned int uint;
typedef enum { TRUE = 1, FALSE = 0 } Boolean;

char* myGetStr(char* buffer, int size);

char* createDynaString(char* inputString);

char* getCompleteString(char* inputRequest);

void printInstructions();

void clearInputBuffer();

