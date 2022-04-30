#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "generalFuncs.h"
#include "Address.h"
#include "Product.h"
#include "Customer.h"
#include "ShoppingItem.h"
#include "ShoppingCart.h"
#include "SuperMarket.h"

#pragma warning(disable:4996)

// changed customer* to customer but not completely, need to fix
int main(void)
{
	
	SuperMarket* newSuperMarket = createSuperMarket();
	int input = 0;
	
	do
	{
		printf("Welcome to the SuperMarket Program main menu. Please enter an input for what to do:\n");
		printInstructions();
		scanf("%d", &input);
		
		switch (input)
		{
		case 1:
			// add customer
			clearInputBuffer();
			addCustomerToStore(newSuperMarket);
			break;

		case 2:
			// add products
			clearInputBuffer();
			addProductToInventory(newSuperMarket);
			break;

		case 3:
			// checkout (buy) - 1 customer at a time 
			ProceedToCheckout(newSuperMarket);
			break;

		case 4:
			// print the Super Market's products
			printf("Printing all products currently in the store:\n");
			printAllProds(newSuperMarket);
			break;

		case 5:

		// print all products by their type
			printSuperMarketProductsPerType(newSuperMarket);
			break;
		
		case 6:
			// print the whole superMarket
			printWholeSuperMarket(newSuperMarket);
			break;
		// print by type
		case (-1):
			// Exit, free allocations and close program
			freeSuperMarket(newSuperMarket);
			printf("You have selected to exit - Freeing all memory allocations.\n");
			break;

		default:
			break;
		}
	} while (input != -1 || isspace(input));
	printf("Bye bye!\n");
	


	return 0;
}

