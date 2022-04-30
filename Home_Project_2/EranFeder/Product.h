#pragma once
#include "generalFuncs.h"

#define BARCODE_SIZE 7
#define MAX_PROD_PRICE 99999
#define NUM_OF_TYPES 4

typedef enum {Shelf=1,Frozen=2,Fridge=3,FruitVegetable=4} ProductType;


typedef struct
{
	char* productName;
	char* barCode;
	ProductType pType;
	float prodPrice;
	uint quantityInStock;

}Product;



Product* createProduct();

void printProduct(const Product* thisProduct);

char* checkBarcodeInput();

char* checkProdNameInput();

int prodTypeInput();

float inputPrice();

int inputInventory();

void freeProduct(Product* thisProduct);

char* printType(const Product* thisProduct);