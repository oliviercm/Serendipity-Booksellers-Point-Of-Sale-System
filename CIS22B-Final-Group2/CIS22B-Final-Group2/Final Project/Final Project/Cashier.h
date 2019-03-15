#pragma once

#include <string>
#include "InventoryDatabase.h"
#include "InventoryBook.h"
#include <memory>

class Cashier
{
private:
	InventoryDatabase* pInventoryDatabase;
	std::unique_ptr<InventoryBook[]> cart;
	int cartSize;
	const double SALES_TAX = 0.0725;
public:
	// Constructor
	Cashier(InventoryDatabase* pD);

	void addBookToCart(InventoryBook book);
	void checkout();
	int findBook(std::string isbnNum);
};