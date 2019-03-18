#pragma once

#include <string>
#include <memory>
#include "InventoryDatabase.h"

class Cashier
{
private:
	InventoryDatabase* pInventoryDatabase;
	std::unique_ptr<InventoryBook[]> cart;
	int cartSize;
	const double SALES_TAX = 0.0725;
	std::unique_ptr<InventoryBook[]> inv; 
public:
	// Constructor
	Cashier(InventoryDatabase* pD);

	void addBookToCart(std::string isbnNum);
	void removeBookFromCart(std::string isbnNum);
	std::unique_ptr<InventoryBook[]> getCart() const;
	void checkout();
	int findBook(std::string isbnNum);
	double bookPrice(std::string isbn);
	double priceOfCart(); 
	void printCart();
};