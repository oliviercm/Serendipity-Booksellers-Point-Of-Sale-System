/********************************************************************************
************************************ Book ***************************************
*********************************************************************************
* The purpose of this class is to provide a simple and intuitive way to bundle
* information about a book.
*****************
***** USAGE *****
*****************
* In order to use this class, create a book object.
* Members are public so they can be accessed with the dot or arrow operator.
*********************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include "Book.h"

/****************************************
* CONSTRUCTORS / DESTRUCTORS
*****************************************/

Book::Book()
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

Book::Book(std::string is, std::string ti, std::string au, std::string pu, std::string ad, int qu, double wh, double re)
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

Book::~Book()
{

}

/****************************************
* OPERATOR OVERLOADS
*****************************************/

Book& Book::operator=(const Book& book)
{
	isbn = book.isbn;
	title = book.title;
	author = book.author;
	publisher = book.publisher;
	addDate = book.addDate;
	quantity = book.quantity;
	wholesale = book.wholesale;
	retail = book.retail;

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

Book& Book::operator+(const int n)
{
	this->quantity = this->quantity + n;

	return *this;
}

Book& Book::operator-(const int n)
{
	this->quantity = this->quantity - n;

	return *this;
}

Book& Book::operator+=(const int n)
{
	this->quantity = this->quantity + n;

	return *this;
}

Book& Book::operator-=(const int n)
{
	this->quantity = this->quantity - n;

	return *this;
}

//Prefix increment
Book& Book::operator++()
{
	this->quantity = this->quantity + 1;

	return *this;
}

//Prefix decrement
Book& Book::operator--()
{
	this->quantity = this->quantity - 1;

	return *this;
}

//Postfix increment
Book Book::operator++(int)
{
	Book temp = *this;
	
	this->quantity = this->quantity + 1;

	return temp;
}

//Postfix decrement
Book Book::operator--(int)
{
	Book temp = *this;

	this->quantity = this->quantity - 1;

	return temp;
}

std::ostream& operator<<(std::ostream& os, const Book& book)
{
	os << "ISBN: " << book.isbn << std::endl
		<< "Title: " << book.title << std::endl
		<< "Author: " << book.author << std::endl
		<< "Publisher: " << book.publisher << std::endl
		<< "Add Date: " << book.addDate << std::endl
		<< "Quantity: " << book.quantity << std::endl
		<< "Wholesale: " << book.wholesale << std::endl
		<< "Retail: " << book.retail << std::endl;

	return os;
}