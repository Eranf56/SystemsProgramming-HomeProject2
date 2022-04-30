#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Address.h"
#include "generalFuncs.h"

#pragma warning(disable:4996)

// Print Address fields //
void printAddress(const Address* thisAddress)
{
	printf("Address: ");
	printf("%s %d, %s\n", thisAddress->streetName, thisAddress->streetNumber, thisAddress->city );
}


// Assuming that the user follows the instructions an enters an integer //
void houseNumInput(int* houseNum)
{
	printf("Please input a house number:");
	int temp;
	do
	{
		temp = 0;
		scanf("%d", &temp);
		if (temp < 1)
		{
			printf("Invalid input - try again.\n");
		}
	} while ( temp < 1 );
	*(houseNum) = temp;
}


void freeAddress(Address* thisAddress)
{
	free(thisAddress->city);
	free(thisAddress->streetName);
	free(thisAddress);
}


Address* createAddress()
{
	Address* newAddress = (Address*)malloc(sizeof(Address));
	printf("Please input an address as a complete string.\n");
	printf("- Street & City MUST contain only letters and space, at least one alphabet letter and house number MUST contain digits ONLY and lastly, must have two exclamation marks between them.\n");
	printf("Lastly, city and street name may have a space within them.\n");
	char* string = getCompleteString("Format: street!house number!city");
	switchSpacesWithHash(string);
	stringCheck(string);

	char temp[50];
	char delimiter[] = "!";

	newAddress->streetName = createDynaString(strtok(string, delimiter));

	strcpy(temp, strtok(NULL, delimiter));
	newAddress->streetNumber = atoi(temp);
	newAddress->city = createDynaString(strtok(NULL, delimiter));

	
//	stringParse(string, newAddress->streetName, (newAddress->streetNumber), newAddress->city);
	return newAddress;
}

void switchSpacesWithHash(char* thisString)
{
	if (thisString != NULL)
	{
		for (int iterator = 0; *(thisString+iterator) != '\0' ; iterator++)
		{
			if (*(thisString+iterator) == ' ')
			{
				*(thisString + iterator) = '#';
			}
		}
	}
}


void stringCheck(char* thisString)
{
	int hashCounter = 0;
	for (int iterator = 0; *(thisString + iterator) != '\0'; iterator++)
	{
		if (*(thisString + iterator) == '#')
		{
			hashCounter++;
		}

		else if (*(thisString + iterator) == '!' && isdigit(*(thisString + iterator+1)))
		{

			if (hashCounter == 0)
			{
				*(thisString + iterator - 1) = toupper(*(thisString+iterator-1));
				hashCounter = 0;
			}

			else
			{
				hashCounter = 0;
			}
		}

		if (*(thisString+iterator+1) == '\0' && hashCounter == 0)
		{
			*(thisString+iterator) = toupper(*(thisString+iterator));
			break;
		}
		
	}
}

// String example [street!house number!city]
void stringParse(char* wholeString, char* street, char* cityToParse, int* houseNumber)
{
	char temp[50];
	char delimiter[] = "!";

	street = createDynaString(strtok(wholeString, delimiter));

	strcpy(temp,strtok(NULL, delimiter));
	*houseNumber = atoi(temp);
	cityToParse = createDynaString(strtok(NULL, delimiter));
}