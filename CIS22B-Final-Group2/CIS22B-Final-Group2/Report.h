#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Book.h"
#include "InventoryBook.h"
#include "InventoryDatabase.h"

class Report // Testing
{
private:
	int nu_books;				//Number of titles in the inventory
	InventoryBook *books;				//Somehow the program must calculate the number of books in the input file so we can make arrays of that size
	double wholesale_value;		//Counter to find the total wholesale value of all books in the inventory
	double retail_value;		//Counter to find the total retial value of all books in the inventory

	//Private setters.
	void selectionSortQty(InventoryBook *books);			//Sort by Quantity
	void selectionSortCost(InventoryBook *books);		//Sort by Wholesale Cost
	void selectionSortAge(InventoryBook *books);			//Sort by date book was added to inventory

public:
	//Getters
public:
	//Getters
	InventoryBook* getInvList();                 //Inventory List option. 
	double getInvWholesaleV();					 //Inventory Wholesale Value. Returns the wholesale value of the entire inventory
	double getInvRetailV();						 //Inventory Retail Value. Returns rhe retail value of the entire inventory
	InventoryBook* getListbyQty();               //List by Quantity
	InventoryBook* getListbyCost();              //List by Cost
	InventoryBook* getListbyAge();               //List by Age

//Constructor
	Report(int num_books, InventoryBook *data);
	//Destructor
	~Report();
};

