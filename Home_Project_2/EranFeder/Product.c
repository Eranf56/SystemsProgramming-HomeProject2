#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Product.h"
#include "generalFuncs.h"

#pragma warning(disable:4996)


char const* prodTypes[] = { "Shelf", "Frozen","Fridge","FruitVegetable"};


Product* createProduct()
{
	Product* newProductToAdd = (Product*)malloc(sizeof(Product));
	newProductToAdd->productName = checkProdNameInput();
	newProductToAdd->barCode = checkBarcodeInput();
	newProductToAdd->pType = prodTypeInput();
	newProductToAdd->prodPrice = inputPrice();
	newProductToAdd->quantityInStock = inputInventory();
	return newProductToAdd;
}


// Prints the product to console
void printProduct(const Product* thisProduct)
{
	printf("Name: %s, Barcode: %s, Type: %s, Price: %.2f, Quantity: %u\n", thisProduct->productName, thisProduct->barCode, printType(thisProduct), thisProduct->prodPrice, thisProduct->quantityInStock);
}

// Checks product barcode input
char* checkBarcodeInput()
{
	// MUST BE exactly 7 chars, uppercased, and 3-5 digits
	printf("Please enter a barcode for the product (Length of exactly 7, must contain 3-5 digits and the rest - UpperCase characters):\n");
	char temp[MAX_STR_LENGTH];
	Boolean status;
	int lengthCounter;
	int digitCounter;
	int specialCharCounter;
	do
	{
		lengthCounter = 0; // Counts Barcode length
		digitCounter = 0; // Counts number of digits in the barcode
		specialCharCounter = 0;
		status = FALSE; // Exit condition for the input
		myGetStr(temp, MAX_STR_LENGTH);
		if (temp != NULL)
		{
			for (int offset = 0; *(offset+temp) != '\0'; offset++)
			{
				if ( isdigit(*(offset + temp)) )
				{
					digitCounter++;
				}
				else if (!isalpha((*(offset + temp))))
				{
					specialCharCounter++;
				}
				else if ( !(isupper(*(offset + temp))) )
				{
					(*(offset + temp)) = toupper(*(offset + temp));
				}
				lengthCounter++;
			}
			if ( (digitCounter >= 3 && digitCounter <= 5 ) && lengthCounter == BARCODE_SIZE && specialCharCounter == 0)
			{
				status = TRUE;
			}
			else
			{
				status = FALSE;
			}
		}
		if (status != TRUE)
		{
			printf("There was an error in the input, please try again:\n");
		}
	} while (status != TRUE);
	return createDynaString(temp);
}


// Checks product name input
char* checkProdNameInput()
{
	// MUST BE up to 20 chars
	printf("Please enter a name for the product (Up to 20 characters):\n");
	char temp[MAX_STR_LENGTH];
	Boolean status;
	int lengthCounter;
	do
	{
		lengthCounter = 0;
		status = FALSE;
		myGetStr(temp, MAX_STR_LENGTH);
		if (temp != NULL)
		{
			for (int offset = 0; *(offset + temp) != '\0'; offset++)
			{
				lengthCounter++;
			}
			if (lengthCounter <= 20)
			{
				status = 1;
				break;
			}
		}
	} while (status != TRUE);
	return createDynaString(temp);
}


// Check product type input
int prodTypeInput()
{
	int digit;
	printf("Enter a digit for the product type (1-Shelf, 2-Frozen, 3-Fridge, 4-FruitVegetable\n");
	do
	{
		digit = 0;
		scanf("%d", &digit);
		clearInputBuffer();
		if (digit > 4 || digit <1)
		{
			printf("Invalid input - Product type must be within the given range (1-4). Try again.\n");
		}
	} while ( isalpha(digit) || (digit < 1 || digit > 4) );
	return digit;
}


// Check price input
float inputPrice()
{
	Boolean condition;
	printf("Now, please enter a price for the product:\n");
	float price;
	do
	{
		price = 0;
		condition = FALSE;
		scanf("%f",&price);
		clearInputBuffer();
		if (price > MAX_PROD_PRICE || price < 0)
		{
			printf("Invalid input - Price must be a positive number. Try again.\n");
		}
		else if (price < MAX_PROD_PRICE && price > 0)
		{
			condition = TRUE;
		}
	} while ( condition != TRUE );
	return price;
}

// Checks inventory input
int inputInventory()
{
	Boolean condition;
	printf("Last, input a quantity for the product's input:\n");
	int quantity;
	do
	{
		quantity = 0;
		condition = FALSE;
		scanf("%d", &quantity);
		clearInputBuffer();
		if (quantity < 0)
		{
			printf("Invalid input - Quantity must be a Natural number. Try again.\n");
		}
		else if (quantity > 0)
		{
			condition = TRUE;
		}
	} while (condition != TRUE);
	return quantity;
}

// Free memory allocation function
void freeProduct(Product* thisProduct)
{
	free(thisProduct->productName);
	free(thisProduct->barCode);
	free(thisProduct);
}

// Returns string representative of enum value
char* printType(const Product* thisProduct)
{
	int valueCatch = thisProduct->pType;

	switch (valueCatch)
	{
	case 1:
		return "Shelf";
		break;

	case 2:
		return "Frozen";
		break;

	case 3:
		return "Fridge";
		break;

	case 4:
		return "VegetableFruit";
		break;

	default:
		// Never happens
		return "None";
		break;
	}
}