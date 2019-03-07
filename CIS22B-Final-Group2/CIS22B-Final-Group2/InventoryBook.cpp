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

#define _CRT_SECURE_NO_WARNINGS

#include "InventoryBook.h"

/****************************************
* CONSTRUCTORS / DESTRUCTORS
*****************************************/

InventoryBook::InventoryBook()
{
	isbn = std::string();
	title = std::string();
	author = std::string();
	publisher = std::string();
	addDate = std::string();
	quantity = 0;
	wholesale = 0;
	retail = 0;
}

InventoryBook::InventoryBook(std::string is, std::string ti, std::string au, std::string pu, std::string ad, int qu, double wh, double re)
{
	isbn = is;
	title = ti;
	author = au;
	publisher = pu;
	addDate = ad;
	quantity = qu;
	wholesale = wh;
	retail = re;
}

InventoryBook::~InventoryBook()
{

}

/****************************************
* OPERATOR OVERLOADS
*****************************************/

InventoryBook& InventoryBook::operator=(const InventoryBook& inventoryBook)
{
	isbn = inventoryBook.isbn;
	title = inventoryBook.title;
	author = inventoryBook.author;
	publisher = inventoryBook.publisher;
	addDate = inventoryBook.addDate;
	quantity = inventoryBook.quantity;
	wholesale = inventoryBook.wholesale;
	retail = inventoryBook.retail;

	return *this;
}

/**
* operator+, operator-, operator+=, operator-=, operator++, operator--
*
* @brief Adds or subtracts from the book's quantity-on-hand. book + 1, book++, and book += 1 are all the same as book.quantity = book.quantity + 1.
* Note that prefix and postfix increments and decrements act similarly to native operators.
*
* @param n Right-hand side int to add or subract from quantity-on-hand.
*/

InventoryBook& InventoryBook::operator+(const int n)
{
	this->quantity = this->quantity + n;

	return *this;
}

InventoryBook& InventoryBook::operator-(const int n)
{
	this->quantity = this->quantity - n;

	return *this;
}

InventoryBook& InventoryBook::operator+=(const int n)
{
	this->quantity = this->quantity + n;

	return *this;
}

InventoryBook& InventoryBook::operator-=(const int n)
{
	this->quantity = this->quantity - n;

	return *this;
}

//Prefix increment
InventoryBook& InventoryBook::operator++()
{
	this->quantity = this->quantity + 1;

	return *this;
}

//Prefix decrement
InventoryBook& InventoryBook::operator--()
{
	this->quantity = this->quantity - 1;

	return *this;
}

//Postfix increment
InventoryBook InventoryBook::operator++(int)
{
	InventoryBook temp = *this;

	this->quantity = this->quantity + 1;

	return temp;
}

//Postfix decrement
InventoryBook InventoryBook::operator--(int)
{
	InventoryBook temp = *this;

	this->quantity = this->quantity - 1;

	return temp;
}

/**
* operator<<
*
* @brief Prints out a formatted listing of the book's attributes.
*/

std::ostream& operator<<(std::ostream& os, const InventoryBook& inventoryBook)
{
	os << "ISBN: " << inventoryBook.isbn << std::endl
		<< "Title: " << inventoryBook.title << std::endl
		<< "Author: " << inventoryBook.author << std::endl
		<< "Publisher: " << inventoryBook.publisher << std::endl
		<< "Add Date: " << inventoryBook.addDate << std::endl
		<< "Quantity: " << inventoryBook.quantity << std::endl
		<< "Wholesale: " << inventoryBook.wholesale << std::endl
		<< "Retail: " << inventoryBook.retail << std::endl;

	return os;
}