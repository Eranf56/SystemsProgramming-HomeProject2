#pragma once
#include "ShoppingItem.h"
#include "Product.h"
#include "generalFuncs.h"



#define CART_BASE 0

typedef struct
{
	ShoppingItem** itemsInCart;
	uint totalVariousItemsInCart;
}ShoppingCart;

void addShoppingItem(ShoppingCart* thisShoppingCart, Product* productToAdd);

ShoppingCart* createShoppingCart();

float calcTotalCartValue(const ShoppingCart* thisShoppingCart);

int checkRepeatedPresence(const ShoppingCart* thisCart, const Product* thisProduct);

void freeShoppingCart(ShoppingCart* thisShoppingCart);

void printShoppingCart(const ShoppingCart* thisShoppingCart);
