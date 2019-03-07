/********************************************************************************
************************************ Book ***************************************
*********************************************************************************
* The purpose of this class is to provide a simple and intuitive way to bundle
* information about a book.
*****************
***** USAGE *****
*****************
* Note that in almost all cases, the child class InventoryBook should be used instead.
* In order to use this class, create a Book object.
* Members are public so they can be accessed with the dot or arrow operator.
*********************************************************************************/

#pragma once

#include <string>

struct Book
{
public:
	//Book information
	std::string isbn;
	std::string title;
	std::string author;
	std::string publisher;

	//Constructors
	Book();
	Book(std::string is, std::string ti, std::string au, std::string pu);

	//Destructors
	~Book();

	//Operator overloads
	Book& operator=(const Book& book);

	friend std::ostream& operator<<(std::ostream& os, const Book& book);
};