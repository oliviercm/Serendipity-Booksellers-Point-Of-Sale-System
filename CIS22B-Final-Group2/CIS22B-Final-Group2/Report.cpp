#define _CRT_SECURE_NO_WARNINGS
// -$Olivier: I'm not sure what's going on here - if these are include guards, you don't need them since the header file already has #pragma once.
//#ifndef REPORT_M
//#define REPORT_M
#include "Report.h"
#include "InventoryDatabase.h"
#include "InventoryBook.h"
#include <string>
//#include <fstream> -$Olivier: I might be wrong, but you don't need fstream for this class.

/*												   	 Constructor
	From main, we must pass the number of titles in the inventory somehow. This is the only way to create a Report object.
*/
Report::Report(int num_books, InventoryBook *data)
{
	wholesale_value = 0;
	retail_value = 0;
	nu_books = num_books;
	inventory = data;
}

/*												Array of Books Creation Functions
	The purpose of these functions are to dynamically create an array of InventoryBook objects. With this, the Report class is going to be able to use
	all its member functions on its internal array. "array_books" will create the new array. "setbookList" will fill in the array with
	a for loop by streaming	in the data from the inventory file. We use the overloaded >> operator to fill in each part of a InventoryBook object.
*/
InventoryBook* Report::array_books()
{
	InventoryBook *ptrBL = new InventoryBook[nu_books];
	return ptrBL;
}
void Report::setbookList()
{
	books = array_books();

	for (int i = 0; i < nu_books; i++)
	{
		(books + i)->isbn = (inventory + i)->isbn;
		(books + i)->title = (inventory + i)->title;
		(books + i)->author = (inventory + i)->author;
		(books + i)->publisher = (inventory + i)->publisher;
		(books + i)->addDate = (inventory + i)->addDate;
		(books + i)->quantity = (inventory + i)->quantity;
		(books + i)->wholesale = (inventory + i)->wholesale;
		(books + i)->retail = (inventory + i)->retail;
	}
}

/*													Sorting Algorithms
	These algorithms will be used by several public functions of this class. They will sort by quantity, wholesale cost, and number of days
	the books have remained in the inventory. All 3 functions will used the Selection Sort algorithm.
*/
void Report::selectionSortQty(InventoryBook *books)
{
	int startScan, minIndex, minValue;

	for (startScan = 0; startScan < (nu_books - 1); startScan++)
	{
		minIndex = startScan;
		minValue = (books + startScan)->quantity;
		for (int index = startScan + 1; index < nu_books; index++)
		{
			if ((books + index)->quantity < minValue)
			{
				minValue = (books + index)->quantity;
				minIndex = index;
			}
		}
		(books + minIndex)->quantity = (books + startScan)->quantity;
		(books + startScan)->quantity = minValue;
	}
}
void Report::selectionSortCost(InventoryBook *books)
{
	int startScan, minIndex;
	double minValue;

	for (startScan = 0; startScan < (nu_books - 1); startScan++)
	{
		minIndex = startScan;
		minValue = (books + startScan)->wholesale;
		for (int index = startScan + 1; index < nu_books; index++)
		{
			if ((books + index)->wholesale < minValue)
			{
				minValue = (books + index)->wholesale;
				minIndex = index;
			}
		}
		(books + minIndex)->wholesale = (books + startScan)->wholesale;
		(books + startScan)->wholesale = minValue;
	}
}
void Report::selectionSortAge(InventoryBook *books)
{
	int startScan, minIndex;
	std::string minValue;

	for (startScan = 0; startScan < (nu_books - 1); startScan++)
	{
		minIndex = startScan;
		minValue = (books + startScan)->addDate;
		for (int index = startScan + 1; index < nu_books; index++)
		{
			if ((books + index)->addDate < minValue)
			{
				minValue = (books + index)->addDate;
				minIndex = index;
			}
		}
		(books + minIndex)->addDate = (books + startScan)->addDate;
		(books + startScan)->addDate = minValue;
	}
}

/*												Inventory List Function
	A list of information on all books.
*/
void Report::getInvList()
{
	for (int i = 0; i < nu_books; i++)
	{
		std::cout << *(books + i);
	}
}

/*											Inventory Wholesale Value Function
	A list of the wholesale value of all the books in the inventory and the total wholesale value of the inventory
*/
double Report::getInvWholesaleV()
{
	for (int i = 0; i < nu_books; i++)
	{
		std::cout << *(books + i);
		wholesale_value += (books + i)->wholesale;
	}
	return wholesale_value;
}

/*											 Inventory Retail Value Function
	A list of the retail value of all the books in the inventory and the total retail value of the inventory
*/
double Report::getInvRetailV()
{
	for (int i = 0; i < nu_books; i++)
	{
		std::cout << *(books + i);
		retail_value += (books + i)->retail;
	}
	return retail_value;
}

/*													List by Quantity
	A list of all the books in the inventory, sorted by quantity on hand. The books with the greatest quantity on hand will be listed first
*/
void Report::getListbyQty()
{
	selectionSortQty(books);
	getInvList();
}

/*													List by Cost
	A list of all the books in the inventory, sorted by wholesale cost. The books with the greatest wholesale cost will be listed first
*/
void Report::getListbyCost()
{
	selectionSortCost(books);
	getInvList();
}

/*													List by Age
	A list of all the books in the inventory, sorted by purchase date. The books that have been in the inventory the longest will
	be listed first
*/
void Report::getListbyAge()
{
	selectionSortAge(books);
	getInvList();
}

/*													Destructor
	Delete dynamically allocated array of InventoryBook objects to prevent memory leak
*/
Report::~Report()
{
	delete books;
}

//#endif -$Olivier: If this is for an include guard, you don't need it since the header file already has #pragma once
