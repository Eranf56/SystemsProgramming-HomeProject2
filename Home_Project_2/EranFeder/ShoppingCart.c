#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ShoppingCart.h"
#include "ShoppingItem.h"
#include "Product.h"



void addShoppingItem(ShoppingCart* thisShoppingCart, Product* productToAdd)
{
	ShoppingItem *itemToAdd = createShoppingItem(productToAdd);
	int status = checkRepeatedPresence(thisShoppingCart, productToAdd);
	if (status != -1) // item already exists in the cart
	{
		(*((thisShoppingCart->itemsInCart) + status))->quantityInCart += itemToAdd->quantityInCart;
		productToAdd->quantityInStock -= itemToAdd->quantityInCart;
		freeShoppingItem(itemToAdd);
	}
	else // item does not exist in cart
	{
		thisShoppingCart->itemsInCart = (ShoppingItem**)realloc(thisShoppingCart->itemsInCart, sizeof(ShoppingItem*)*(thisShoppingCart->totalVariousItemsInCart + 1));
		*((thisShoppingCart->itemsInCart) + thisShoppingCart->totalVariousItemsInCart) = itemToAdd;
		thisShoppingCart->totalVariousItemsInCart += 1;
		productToAdd->quantityInStock -= itemToAdd->quantityInCart;
	}
}

// Creates a new shopping cart initialized empty
ShoppingCart* createShoppingCart()
{
	ShoppingCart* newShopCart = (ShoppingCart*)malloc(sizeof(ShoppingCart));
	newShopCart->totalVariousItemsInCart = CART_BASE;
	newShopCart->itemsInCart = (ShoppingItem**)malloc(sizeof(ShoppingItem*) * CART_BASE);
	return newShopCart;
}

// Calculates the total cart's value to be paid
float calcTotalCartValue(const ShoppingCart* thisShoppingCart)
{
	float totalPrice = 0;
	int quantityMultiplier = 0;
	float productPrice = 0;
	uint iterator;
	for ( iterator = 0; iterator < thisShoppingCart->totalVariousItemsInCart; iterator++)
	{
		productPrice = (*((thisShoppingCart->itemsInCart) + iterator))->shoppingItemPrice;
		quantityMultiplier = (*((thisShoppingCart->itemsInCart) + iterator))->quantityInCart;
		totalPrice += (productPrice * quantityMultiplier);
	}
	return totalPrice;
}


int checkRepeatedPresence(const ShoppingCart* thisCart, const Product* thisProduct)
{
	uint index;
	for (index = 0; index < thisCart->totalVariousItemsInCart; index++)
	{
		if ( strcmp((*((thisCart->itemsInCart)+index))->shoppingItemName, thisProduct->productName) == 0 )
		{
			return index;
		}
	}

	
	return -1;
}

void printShoppingCart(const ShoppingCart* thisShoppingCart)
{
	printf("--- Printing shopping cart data to console : \n");
	printf("Shopping Cart - Total various products: %d - Total Price: %.2f\n Products:\n", thisShoppingCart->totalVariousItemsInCart, calcTotalCartValue(thisShoppingCart));
	for (uint i = 0; i < thisShoppingCart->totalVariousItemsInCart; i++)
	{
		printf("- %d",i+1);
		printShoppingItem(*((thisShoppingCart->itemsInCart)+i));
	}

}

void freeShoppingCart(ShoppingCart* thisShoppingCart)
{
	for (uint iterator = 0; iterator < thisShoppingCart->totalVariousItemsInCart; iterator++)
	{
		freeShoppingItem(*((thisShoppingCart->itemsInCart)+iterator));
	}
	free(thisShoppingCart->itemsInCart);
	free(thisShoppingCart);
}