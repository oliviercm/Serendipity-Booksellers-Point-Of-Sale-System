#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"Book.h"
#include"InventoryDatabase.h"

class Report // Testing
{
private:
	int nu_books;				//Number of titles in the inventory
	Book *books;				//Somehow the program must calculate the number of books in the input file so we can make arrays of that size
	double wholesale_value;		//Counter to find the total wholesale value of all books in the inventory
	double retail_value;		//Counter to find the total retial value of all books in the inventory
	Book *inventory;			// OLIVER, I need a pointer to the array your module creates!

								//Private setters.
	Book *array_books();		//This function will dynamically allocate an array of Book objects
	void selectionSortQty(Book *books);			//Sort by Quantity
	void selectionSortCost(Book *books);		//Sort by Wholesale Cost
	void selectionSortAge(Book *books);			//Sort by date book was added to inventory

public:
	//Getters
	void setbookList();					//This function will match the "books" pointer with the new array and fill in the array.
	void getInvList();                  //Inventory List option. 
	double getInvWholesaleV();          //Inventory Wholesale Value. Returns the wholesale value of the entire inventory
	double getInvRetailV();             //Inventory Retail Value. Returns rhe retail value of the entire inventory
	void getListbyQty();                //List by Quantity
	void getListbyCost();               //List by Cost
	void getListbyAge();                //List by Age

										//Constructor
	Report(int num_books, Book *data);
	//Destructor
	~Report();
};
