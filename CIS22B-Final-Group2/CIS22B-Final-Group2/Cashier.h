#pragma once

#include <string>
#include <memory>
#include "InventoryDatabase.h"
#include "InventoryBook.h"

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
	void removeBookFromCart(InventoryBook book);
	std::unique_ptr<InventoryBook[]> getCart() const;
	void checkout();
	int findBook(std::string isbnNum);
};