#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "SuperMarket.h"
#include "generalFuncs.h"
#include "Address.h"
#include "Product.h"
#include "ShoppingCart.h"

#pragma warning(disable:4996)



SuperMarket* createSuperMarket()
{
	SuperMarket* newSuperMarket = (SuperMarket*)malloc(sizeof(SuperMarket));
	newSuperMarket->StoreName = getCompleteString("Input a name for the new Super-Market - (Must contain at least one character):");
	newSuperMarket->StoreAddress = createAddress();
	//Clients
	newSuperMarket->numOfClients = INITIAL_AMOUNT_OF_CUSTOMERS;
	newSuperMarket->StoreCustomers = (Customer*)malloc(sizeof(Customer*)*INITIAL_AMOUNT_OF_CUSTOMERS);
	//Products 
	newSuperMarket->numOfVariousProducts = INITAL_AMOUNT_OF_PRODUCTS;
	newSuperMarket->productsList = (Product**)malloc(sizeof(Product*)*INITAL_AMOUNT_OF_PRODUCTS);
	return newSuperMarket;
}

void freeSuperMarket(SuperMarket* thisSuperMarket)
{
	freeAddress(thisSuperMarket->StoreAddress);
	free(thisSuperMarket->StoreName);
	for (uint iterator = 0; iterator < thisSuperMarket->numOfClients; iterator++)
	{
		freeCustomer(*((thisSuperMarket->StoreCustomers)+ iterator));
	}
	for (uint iterator = 0; iterator < thisSuperMarket->numOfVariousProducts; iterator++)
	{
		freeProduct( *((thisSuperMarket->productsList)+iterator) );
	}
	free(thisSuperMarket);
}

void addCustomerToStore(SuperMarket* thisSuperMarket)
{
	Customer* newCustomer = createCustomer();
	Boolean status = checkIfCustomerExists(thisSuperMarket,newCustomer->customerName);
	while (status == TRUE)
	{
		printf("This customer already exists in the store, try again.\n");
		freeCustomer(newCustomer);
		newCustomer = createCustomer();
		status = checkIfCustomerExists(thisSuperMarket, newCustomer->customerName);
	}
	thisSuperMarket->StoreCustomers = (Customer*)realloc(thisSuperMarket->StoreCustomers, sizeof(Customer*)*(thisSuperMarket->numOfClients + 1));
	*( (thisSuperMarket->StoreCustomers) + (thisSuperMarket->numOfClients) ) = newCustomer;
	(thisSuperMarket->numOfClients)++;
}

void addProductToInventory(SuperMarket* thisSuperMarket)
{
	Product* newProduct = createProduct();
	Boolean status = checkIfProductExists(thisSuperMarket, newProduct);
	while (status == TRUE)
	{
		printf("This product already exists in the store, try again.\n");
		freeProduct(newProduct);
		newProduct = createProduct();
		status = checkIfProductExists(thisSuperMarket, newProduct);
	}
	thisSuperMarket->productsList = (Product**)realloc(thisSuperMarket->productsList, sizeof(Product*)* (thisSuperMarket->numOfVariousProducts+1));
	*((thisSuperMarket->productsList) + (thisSuperMarket->numOfVariousProducts)) = newProduct;
	thisSuperMarket->numOfVariousProducts++;
}

Boolean checkIfProductExists(const SuperMarket* thisSuperMarket, const Product* thisProduct)
{
	for (uint iterator = 0; iterator < thisSuperMarket->numOfVariousProducts; iterator++)
	{	
		if ((strcmp((*((thisSuperMarket->productsList) + iterator))->productName, thisProduct->productName) == 0))
		{
			printf("(Name Match!) This product already exists\n");
			return TRUE;
		}
		if (strcmp((*((thisSuperMarket->productsList) + iterator))->barCode, thisProduct->barCode) == 0)
		{
			printf("(Barcode Match!) This product already exists.\n");
			return TRUE;
		}
	}
	return FALSE;
}

Boolean checkIfCustomerExists(const SuperMarket* thisSuperMarket, const char* thisCustomerName)
{
	for (uint iterator = 0; iterator < thisSuperMarket->numOfClients; iterator++)
	{
		if (strcmp((*((thisSuperMarket->StoreCustomers)+iterator))->customerName, thisCustomerName) == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void printAllProds(const SuperMarket* thisSuperMarket)
{
	printf("---Printing all products:\n");
	printf("There are currently %d different of products in the store's inventory.\n", thisSuperMarket->numOfVariousProducts);
	for (uint iterator = 0; iterator < thisSuperMarket->numOfVariousProducts; iterator++)
	{
		printf("-%d- ", iterator+1);
		printProduct(*((thisSuperMarket->productsList)+iterator));
	}
}


Product* searchProductViaBarcode(const SuperMarket* thisSuperMarket) 
{
	char* tempBarcode = getCompleteString("Please enter a barcode to search the product with.");
	
	for (uint iterator = 0; iterator < thisSuperMarket->numOfVariousProducts; iterator++)
	{
		if (strcmp((*((thisSuperMarket->productsList) + iterator))->barCode, tempBarcode) == 0)
		{
			free(tempBarcode);
			return *((thisSuperMarket->productsList)+iterator);
		}
	}
	return NULL;
}

void printSuperMarketProductsPerType(SuperMarket* thisSupermarket)
{
	for (int typeIterator = 1; typeIterator <= NUM_OF_TYPES; typeIterator++)
	{
		for (uint iterator = 0; iterator < thisSupermarket->numOfVariousProducts; iterator++)
		{
			if ( (*((thisSupermarket->productsList)+iterator))->pType == typeIterator)
			{
				printProduct(*((thisSupermarket->productsList)+iterator));
			}
		}
	}
}

void printWholeSuperMarket(SuperMarket* thisSuperMarket)
{
	printf("--- Printing the entire super market's data:\n");
	printf("Store Name: %s\n", thisSuperMarket->StoreName);
	printAddress(thisSuperMarket->StoreAddress);
	printAllProds(thisSuperMarket);
	printAllCustomers(thisSuperMarket);
}

void printAllCustomers(SuperMarket* thisSuperMarket)
{
	for (uint iterator = 0; iterator < thisSuperMarket->numOfClients; iterator++)
	{
		printf("-%d- ", iterator + 1);
		printCustomer(*((thisSuperMarket->StoreCustomers)+iterator));
	}
}

void ProceedToCheckout(SuperMarket* thisSuperMarket)
{
	clearInputBuffer();
	if (thisSuperMarket->numOfClients == 0)
	{
		printf("There are currently no customers, please add customers via the main menu and then return for the checkout.\n");
		return;
	}
	ShoppingCart* newCart = createShoppingCart();
	char* customerForCheckout = getCompleteString("Please input the customer's name to proceed to checkout:");
	Boolean customerStatus = checkIfCustomerExists(thisSuperMarket, customerForCheckout);
	
	while (customerStatus == FALSE)
	{
		customerForCheckout = getCompleteString("That client does not exist, try again.");
		customerStatus = checkIfCustomerExists(thisSuperMarket, customerForCheckout);
	}
	// first run, shopping cart is empty
	printSuperMarketProductsPerType(thisSuperMarket);
	printf("Please enter (1) to add the first product to your cart. If you would like to cancel, input (-1).\n");
	Boolean checkoutStatus = checkIfWantsToAddItems();
	while (checkoutStatus == TRUE)
	{
		Product* selectedProduct = searchProductViaBarcode(thisSuperMarket);
		while (selectedProduct == NULL)
		{
			printf("The barcode you have entered does not match any product, please try again.\n");
			selectedProduct = searchProductViaBarcode(thisSuperMarket);
		}
		addShoppingItem(newCart, selectedProduct);
		printf("Item added! There are currently %d various items in the shopping cart. Enter (1) to add more products or (-1) to checkout and pay.\n", newCart->totalVariousItemsInCart);
		checkoutStatus = checkIfWantsToAddItems();
	}
	printf("You have selected to checkout:\n");
	printf("%s --- Transaction Summary ---\n", customerForCheckout);
	printShoppingCart(newCart);

	free(customerForCheckout);
	freeShoppingCart(newCart);
}

Boolean checkIfWantsToAddItems()
{
	int tempChoice = 0;
	
	do
	{
		scanf("%d", &tempChoice);
		clearInputBuffer();
	} while (tempChoice != 1 && tempChoice != -1);

	if (tempChoice == 1)
	{
		//wants to add products
		return TRUE;
	}
	else
	{
		// doesn't want to add products
		return FALSE;
	}
}