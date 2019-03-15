#pragma once

#include <string>
#include "InventoryBook.h"

class Report
{
private:
	//Helper Functions
	int convertDateToInt(std::string date);
	template <typename T>
	void swap(T& a, T& b);
public:
	//Sorting
	void selectionSortQuantity(InventoryBook* books, int numBooks); //Sort by Quantity
	void selectionSortCost(InventoryBook* books, int numBooks); //Sort by Wholesale Cost
	void selectionSortAge(InventoryBook* books, int numBooks); //Sort by Add Date
	//Calculation
	double getBookTotalWholesale(InventoryBook book);
	double getInventoryTotalWholesale(InventoryBook* books, int numBooks);
	double getBookTotalRetail(InventoryBook book);
	double getInventoryTotalRetail(InventoryBook* books, int numBooks);
};