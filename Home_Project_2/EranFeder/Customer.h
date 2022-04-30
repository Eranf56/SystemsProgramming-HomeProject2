#pragma once


typedef struct
{
	char* customerName;
}Customer;

Customer* createCustomer();

void printCustomer(const Customer* thisCustomer);

void freeCustomer(Customer* thisCustomer);