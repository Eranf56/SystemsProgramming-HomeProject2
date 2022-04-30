#include <stdio.h>
#include <stdlib.h>
#include "Customer.h"
#include "generalFuncs.h"


Customer* createCustomer()
{
	printf("--- Creating customer...\n");
	Customer* newCustomer = (Customer**)malloc(sizeof(Customer));
	newCustomer->customerName = getCompleteString("Please input a full name for the customer.");
	return newCustomer;
}

void printCustomer(const Customer* thisCustomer)
{
	printf("Customer: %s\n", thisCustomer->customerName);
}

// need to debug
void freeCustomer(Customer* thisCustomer)
{
	free(thisCustomer->customerName);
	free(thisCustomer);
}