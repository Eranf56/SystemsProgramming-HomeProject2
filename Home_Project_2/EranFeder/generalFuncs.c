#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "generalFuncs.h"

// Disables warnings for deprecated functions we are instructed to use anyway (scanf, strcpy, etc...) //
#pragma warning(disable:4996)

// Get string with input validation //
char* myGetStr(char* buffer, int size)
{
	if (buffer != NULL && size > 0)
	{
		if ( fgets(buffer,size,stdin) != NULL  )
		{
			buffer[strcspn(buffer, "\n")] = '\0';
			return buffer;
		}
		else
		{
			buffer[0] = '\0';
			return buffer;
		}
	}
	else
	{
		return NULL;
	}
}




// Dynamically allocates memory for the string //
char* createDynaString(char* inputString)
{
	char* resStr;
	resStr = (char*)malloc( (strlen(inputString) + 1) * sizeof(char));
	if (resStr == NULL)
	{
		return NULL;
	}
	else
	{
		strcpy(resStr, inputString);
		return resStr;
	}
}

// Utilizes other funcs to create a dynamically allocated string //
char* getCompleteString(char* inputRequest)
{
	char* dynamicString;
	char temp[MAX_STR_LENGTH];
	// Print input request //
	printf("%s\n", inputRequest);
	// Receive input into max size string//
	myGetStr(temp, MAX_STR_LENGTH);
	// Dynamically allocate the proper size for the string //
	dynamicString = createDynaString(temp);
	// Returns the dynamically allocated string's pointer //
	return dynamicString;
}


void clearInputBuffer()
{
	char c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}

void printInstructions()
{
	printf("(1) - Add Customer\n");
	printf("(2) - Add Products\n");
	printf("(3) - Proceed To Checkout\n");
	printf("(4) - Print Product Inventory\n");
	printf("(5) - Print Product Inventory - By their type\n");
	printf("(6) - Print The Whole Super Market\n");
	printf("(-1) Exit Program\n");


}
