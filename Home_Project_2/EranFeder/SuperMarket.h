#pragma once

#include "Address.h"
#include "Customer.h"
#include "generalFuncs.h"
#include "Product.h"

#define INITIAL_AMOUNT_OF_CUSTOMERS 0
#define INITAL_AMOUNT_OF_PRODUCTS 0

typedef struct
{
	char* StoreName;
	Address* StoreAddress;
	Customer** StoreCustomers;
	uint numOfClients;
	Product** productsList;
	uint numOfVariousProducts;

}SuperMarket;

SuperMarket* createSuperMarket();

void freeSuperMarket(SuperMarket* thisSuperMarket);

void addCustomerToStore(SuperMarket* thisSuperMarket);

void addProductToInventory(SuperMarket* thisSuperMarket);

Boolean checkIfProductExists(const SuperMarket* thisSuperMarket, const Product* thisProduct);

Boolean checkIfCustomerExists(const SuperMarket* thisSuperMarket, const char* thisCustomerName);

void printAllProds(const SuperMarket* thisSuperMarket);

Product* searchProductViaBarcode(const SuperMarket* thisSuperMarket);

void printWholeSuperMarket(SuperMarket* thisSuperMarket);

void printSuperMarketProductsPerType(SuperMarket* thisSupermarket);

void printAllCustomers(SuperMarket* thisSuperMarket);

Boolean checkIfWantsToAddItems();

void ProceedToCheckout(SuperMarket* thisSuperMarket);