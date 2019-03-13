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
}

Book::Book(std::string is, std::string ti, std::string au, std::string pu)
{
	isbn = is;
	title = ti;
	author = au;
	publisher = pu;
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

	return *this;
}

/**
* operator<<
*
* @brief Prints out a formatted listing of the book's attributes.
*/

std::ostream& operator<<(std::ostream& os, const Book& book)
{
	os << "ISBN: " << book.isbn << std::endl
		<< "Title: " << book.title << std::endl
		<< "Author: " << book.author << std::endl
		<< "Publisher: " << book.publisher << std::endl;

	return os;
}