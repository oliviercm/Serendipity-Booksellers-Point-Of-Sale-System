/********************************************************************************
******************************* InventoryBook ***********************************
*********************************************************************************
* The purpose of this class is to provide a simple and intuitive way to bundle
* information about a book in our inventory system.
*****************
***** USAGE *****
*****************
* In order to use this class, create an InventoryBook object.
* Members are public so they can be accessed with the dot or arrow operator.
*********************************************************************************/

#pragma once

#include <string>
#include "Book.h"

struct InventoryBook : public Book
{
public:
	//Inventory information
	std::string addDate;
	int quantity;
	double wholesale;
	double retail;

	//Constructors
	InventoryBook();
	InventoryBook(std::string is, std::string ti, std::string au, std::string pu, std::string ad, int qu, double wh, double re);

	//Destructors
	~InventoryBook();

	//Operator overloads
	InventoryBook& operator=(const InventoryBook& inventoryBook);
	InventoryBook& operator+(const int n);
	InventoryBook& operator-(const int n);
	InventoryBook& operator+=(const int n);
	InventoryBook& operator-=(const int n);
	InventoryBook& operator++(); //Prefix
	InventoryBook& operator--(); //Prefix
	InventoryBook operator++(int); //Postfix
	InventoryBook operator--(int); //Postfix

	friend std::ostream& operator<<(std::ostream& os, const InventoryBook& inventoryBook);
};