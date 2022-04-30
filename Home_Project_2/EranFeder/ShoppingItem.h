#pragma once

#include "Product.h"
#include "generalFuncs.h"

typedef struct
{
	char* shoppingItemName;
	float shoppingItemPrice;
	uint quantityInCart;

}ShoppingItem;


ShoppingItem* createShoppingItem(const Product * productToBuy);

float inputShoppingItemPrice();

void printShoppingItem(const ShoppingItem* thisShoppingItem);

int inputShoppingItemQuantity();

void freeShoppingItem(ShoppingItem* thisShoppingItem);
