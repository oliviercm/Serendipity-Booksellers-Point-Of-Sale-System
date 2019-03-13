#define _CRT_SECURE_NO_WARNINGS
#ifndef REPORT_M
#define REPORT_M
#include "Report.h"
#include "InventoryBook.h"
#include "InventoryDatabase.h"
#include "book.h"
#include<string>
#include<fstream>

/*												   	 Constructor
	From main, we must pass the number of titles in the inventory somehow. This is the only way to create a Report object.
*/
Report::Report(int num_books, InventoryBook *data)
{
	wholesale_value = 0;
	retail_value = 0;
	nu_books = num_books;
	books = data;
}

/*												Array of Books Creation Functions
	The purpose of these functions are to dynamically create an array of Book objects. With this, the Report class is going to be able to use
	all its member functions on its internal array. "array_books" will create the new array. "setbookList" will fill in the array with
	a for loop by streaming	in the data from the inventory file. We use the overloaded >> operator to fill in each part of a Book object.
*/
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
InventoryBook* Report::getInvList()
{
	return books;
}

/*											Inventory Wholesale Value Function
	A list of the wholesale value of all the books in the inventory and the total wholesale value of the inventory
*/
double Report::getInvWholesaleV()
{
	//When you call this in main, first you need to call getInvList to work with the wholesale value of all books. 
	for (int i = 0; i < 3; i++)
	{
		wholesale_value += (books + i)->wholesale;
	}
	return wholesale_value;
}

/*											 Inventory Retail Value Function
	A list of the retail value of all the books in the inventory and the total retail value of the inventory
*/
double Report::getInvRetailV()
{
	//When you call this in main, first you need to call getInvList to work with the wholesale value of all books.
	for (int i = 0; i < 3; i++)
	{
		retail_value += (books + i)->retail;
	}
	return retail_value;
}

/*													List by Quantity
	A list of all the books in the inventory, sorted by quantity on hand. The books with the greatest quantity on hand will be listed first
*/
InventoryBook* Report::getListbyQty()
{
	selectionSortQty(books);
	return books;
}

/*													List by Cost
	A list of all the books in the inventory, sorted by wholesale cost. The books with the greatest wholesale cost will be listed first
*/
InventoryBook* Report::getListbyCost()
{
	selectionSortCost(books);
	return books;
}

/*													List by Age
	A list of all the books in the inventory, sorted by purchase date. The books that have been in the inventory the longest will
	be listed first
*/
InventoryBook* Report::getListbyAge()
{
	selectionSortAge(books);
	return books;
}

/*													Destructor
	Delete dynamically allocated array of Book objects to prevent memory leak
*/
Report::~Report()
{
	delete books;
}

#endif