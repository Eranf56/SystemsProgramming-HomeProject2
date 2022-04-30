#pragma once


typedef struct
{
	char* streetName;
	int streetNumber;
	char* city;
}Address;


void printAddress(const Address* thisAddress);

void houseNumInput(int* houseNum);

void freeAddress(Address* thisAddress);

Address* createAddress();

void switchSpacesWithHash(char* thisString);

void stringCheck(char* thisString);

void stringParse(char* wholeString, char* street, char* city, int* houseNumber);