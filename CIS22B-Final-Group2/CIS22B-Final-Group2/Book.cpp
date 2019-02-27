#define _CRT_SECURE_NO_WARNINGS

#include "Book.h"

Book::Book()
{
	isbn = "0000000000000";
	title = "Title";
	author = "Author";
	publisher = "Publisher";
	addDate = "01/01/1970";
	quantity = 0;
	wholesale = 0;
	retail = 0;
}

Book::~Book()
{

}