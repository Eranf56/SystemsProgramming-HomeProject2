#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ShoppingItem.h"
#include "ShoppingCart.h"
#include "Product.h"


#pragma warning(disable:4996)



ShoppingItem* createShoppingItem(const Product * productToBuy)
{
	ShoppingItem* newShopItem = (ShoppingItem*)malloc(sizeof(ShoppingItem));
	float shoppingItemPrice = productToBuy->prodPrice;
	char* shoppingItemName = createDynaString(productToBuy->productName);
	uint quantityForCart=0;
	printf("Enter the quantity you would like to add to the shopping cart\n");
	do
	{
		printf("Note - Quantity should Not be zero and must be equal or less to the quantity in stock ( %d ) \n", productToBuy->quantityInStock);
		scanf("%u", &quantityForCart);
		clearInputBuffer();

	} while ( (quantityForCart == CART_BASE) || (quantityForCart > productToBuy->quantityInStock) );

	newShopItem->shoppingItemName = shoppingItemName;
	newShopItem->shoppingItemPrice = shoppingItemPrice;
	newShopItem->quantityInCart = quantityForCart;
	return newShopItem;
}


void printShoppingItem(const ShoppingItem* thisShoppingItem)
{
	printf("--- Printing shopping item data to console : \n");
	printf("Shopping Item: %s, Price %.2f , quanitity in cart: %u\n", thisShoppingItem->shoppingItemName, thisShoppingItem->shoppingItemPrice, thisShoppingItem->quantityInCart);
}



float inputShoppingItemPrice()
{
	Boolean condition;
	printf("Now, please enter a price for the shopping Item\n");
	float price;
	do
	{
		price = 0;
		condition = FALSE;
		scanf("%f", &price);
		clearInputBuffer();
		if (price > MAX_PROD_PRICE || price < 0)
		{
			printf("Invalid input - Price must be a positive number. Try again.\n");
		}
		else if (price < MAX_PROD_PRICE && price > 0)
		{
			condition = TRUE;
		}
	} while (condition != TRUE);
	return price;
}

int inputShoppingItemQuantity()
{
	Boolean condition;
	printf("Last, input an quantity for the product's input:\n");
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

void freeShoppingItem(ShoppingItem* thisShoppingItem)
{
	free(thisShoppingItem->shoppingItemName);
	free(thisShoppingItem);
}


