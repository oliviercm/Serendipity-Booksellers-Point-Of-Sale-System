#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include "Report.h"
#include "InventoryBook.h"

/*												Array of Books Creation Functions
	The purpose of these functions are to dynamically create an array of Book objects. With this, the Report class is going to be able to use
	all its member functions on its internal array. "array_books" will create the new array. "setbookList" will fill in the array with
	a for loop by streaming	in the data from the inventory file. We use the overloaded >> operator to fill in each part of a Book object.
*/
/*													Sorting Algorithms
	These algorithms will be used by several public functions of this class. They will sort by quantity, wholesale cost, and number of days
	the books have remained in the inventory. All 3 functions will used the Selection Sort algorithm.
*/
void Report::selectionSortQuantity(InventoryBook* books, int numBooks)
{
	for (int startScan = 0; startScan < numBooks - 1; startScan++)
	{
		int minIndex = startScan;
		int maxQuantity = books[startScan].quantity;

		for (int index = startScan + 1; index < numBooks; index++)
		{
			if (books[index].quantity > maxQuantity)
			{
				maxQuantity = books[index].quantity;
				minIndex = index;
			}
		}
		swap(books[startScan], books[minIndex]);
	}

	return;
}

void Report::selectionSortCost(InventoryBook* books, int numBooks)
{
	for (int startScan = 0; startScan < numBooks - 1; startScan++)
	{
		int minIndex = startScan;
		double maxWholesale = books[startScan].wholesale;

		for (int index = startScan + 1; index < numBooks; index++)
		{
			if (books[index].wholesale > maxWholesale)
			{
				maxWholesale = books[index].wholesale;
				minIndex = index;
			}
		}
		swap(books[startScan], books[minIndex]);
	}

	return;
}

void Report::selectionSortAge(InventoryBook* books, int numBooks)
{
	for (int startScan = 0; startScan < numBooks - 1; startScan++)
	{
		int minIndex = startScan;
		int minDate = convertDateToInt(books[startScan].addDate);

		for (int index = startScan + 1; index < numBooks; index++)
		{
			if (convertDateToInt(books[index].addDate) < minDate)
			{
				minDate = convertDateToInt(books[index].addDate);
				minIndex = index;
			}
		}
		swap(books[startScan], books[minIndex]);
	}

	return;
}

int Report::convertDateToInt(std::string date)
{
	int month = stoi(date.substr(0, 2));
	int day = stoi(date.substr(3, 2));
	int year = stoi(date.substr(6, 4));

	return 10000 * year + 100 * month + day;
}

template <typename T>
void Report::swap(T& a, T& b)
{
	T temp = std::move(a);
	a = std::move(b);
	b = std::move(temp);
}

/*											Inventory Wholesale Value Function
	A list of the wholesale value of all the books in the inventory and the total wholesale value of the inventory
*/
double Report::getBookTotalWholesale(InventoryBook book)
{
	return book.quantity * book.wholesale;
}
double Report::getInventoryTotalWholesale(InventoryBook* books, int numBooks)
{
	double totalWholesaleValue = 0;
	for (int i = 0; i < numBooks; i++)
	{
		totalWholesaleValue += getBookTotalWholesale(books[i]);
	}
	return totalWholesaleValue;
}

/*											 Inventory Retail Value Function
	A list of the retail value of all the books in the inventory and the total retail value of the inventory
*/
double Report::getBookTotalRetail(InventoryBook book)
{
	return book.quantity * book.retail;
}
double Report::getInventoryTotalRetail(InventoryBook* books, int numBooks)
{
	double totalRetailValue = 0;
	for (int i = 0; i < numBooks; i++)
	{
		totalRetailValue += getBookTotalRetail(books[i]);
	}
	return totalRetailValue;
}