#define _CRT_SECURE_NO_WARNINGS

#include "Cashier.h"
#include <iostream>
#include <iomanip>

// Constructor 
Cashier::Cashier(InventoryDatabase* pD)
{
	pInventoryDatabase = pD;
	cart = std::make_unique<InventoryBook[]>(100); // Change this?
	cartSize = 0;
	inv = pInventoryDatabase->getInventoryArray();
}

// Adds book to cart by prompting the user for the ISBN number 
void Cashier::addBookToCart(std::string isbnNum) {
	int invCount = pInventoryDatabase->getInventoryArraySize();

	for (int i = 0; i < invCount; i++) {
		if (inv[i].isbn == isbnNum) {
			if (getBookCartIndex(isbnNum) != -1) {
				cart[getBookCartIndex(isbnNum)].quantity++;
				inv[i].quantity--; 
			}
			else {
				cart[cartSize] = inv[i];
				cart[cartSize].quantity = 0;
				cart[cartSize].quantity++;
				inv[i].quantity--;
				cartSize++;
			}
			return;
		}
	}
}
// Removes book from cart by prompting the user for the ISBN number 
void Cashier::removeBookFromCart(std::string isbnNum) {
	for (int i = 0; i < cartSize; i++) {
		if (cart[i].isbn == isbnNum && cart[i].quantity > 0) { // Will move these checks to main 
			cart[i].quantity--;
			cart[i].title = "";
			cart[i].isbn = "";
			//cart[i].title.erase(0, cart[i].title.length());
			//cart[i].isbn.erase(0, cart[i].isbn.length());
			cart[i].retail = 0.0;

			inv[pInventoryDatabase->getBookIndexByIsbn(cart[i].isbn)].quantity++;
			pInventoryDatabase->setBookQuantityByIsbn(isbnNum, inv[pInventoryDatabase->getBookIndexByIsbn(cart[i].isbn)].quantity);
			//std::cout << "The book has been removed." << std::endl << std::endl;
			cartSize--;
			return;
		}
		else if (cart[i].isbn == isbnNum) {
			std::cout << "There are no more books of this ISBN number availiable in the cart." << std::endl << std::endl;
			return;
		}
	}
}

// Returns -1 if the book is not in the array (cart), else returns the index the book
// is at
int Cashier::getBookCartIndex(std::string isbnNum) {
	if (cart == nullptr) {
		return -1;
	}
	for (int i = 0; i < cartSize; i++) {
		if (cart[i].isbn == isbnNum) {
			return i;
		}
	}
	return -1;
}

// Returns price of a book including sales tax 
double Cashier::bookPrice(std::string isbn) {
	if (pInventoryDatabase->getBookIndexByIsbn(isbn) != -1) {
		std::cout << "A book of this isbn number is not in the inventory";
		return -1;
	}
	else {
		return inv[pInventoryDatabase->getBookIndexByIsbn(isbn)].wholesale * SALES_TAX;
	}
}

// Returns the subtotal price of the books in the cart 
double Cashier::subTotal() {
	double totalPrice = 0;

	for (int i = 0; i < cartSize; i++) {

		totalPrice += (cart[i].quantity * cart[i].retail); // Check whether we use wholesale or retail 

	}

	return totalPrice;
}

// Returns the total price of the cart.
double Cashier::totalPriceOfCart() {

	double totalPriceOfCart = 0;
	double salesTax;

	for (int i = 0; i < cartSize; i++) {

		totalPriceOfCart += (cart[i].quantity * cart[i].retail); // Check whether we use wholesale or retail 

	}

	salesTax = subTotal() * SALES_TAX;

	totalPriceOfCart += salesTax;

	return totalPriceOfCart;
}


// Checks out books --> reduces quantity in inventory by the amount of books in the cart
void Cashier::checkout() {
	for (int i = 0; i < cartSize; i++) {
		inv[pInventoryDatabase->getBookIndexByIsbn(cart[i].isbn)].quantity -= cart[i].quantity;
		pInventoryDatabase->addToBookQuantityByIsbn(cart[i].isbn, -1);
	}
	clearCart();
}

std::unique_ptr<InventoryBook[]> Cashier::getCart() const
{
	std::unique_ptr<InventoryBook[]> copyCartArray = std::make_unique<InventoryBook[]>(cartSize);

	for (int i = 0; i < cartSize; i++)
	{
		copyCartArray[i].isbn = cart[i].isbn;
		copyCartArray[i].title = cart[i].title;
		copyCartArray[i].author = cart[i].author;
		copyCartArray[i].publisher = cart[i].publisher;
		copyCartArray[i].addDate = cart[i].addDate;
		copyCartArray[i].quantity = cart[i].quantity;
		copyCartArray[i].wholesale = cart[i].wholesale;
		copyCartArray[i].retail = cart[i].retail;
	}

	return copyCartArray;
}

// For testing purposes 
namespace UI {
	const int TERMINAL_WIDTH = 200;
}
void Cashier::printCart() {
	const std::string bookIsbnText = "ISBN:";
	const std::string bookTitleText = "TITLE:";
	const std::string bookQuantityText = "QUANTITY:";
	const std::string bookPriceText = "PRICE:";
	const std::string totalPriceText = "TOTAL PRICE: $";

	const size_t columnSpacing = 3;

	const size_t isbnColumnLength = 13 + columnSpacing;
	const size_t quantityColumnLength = bookQuantityText.length() + columnSpacing;
	const size_t bookPriceColumnLength = bookPriceText.length() + columnSpacing;
	const size_t totalPriceColumnLength = totalPriceText.length() + columnSpacing;

	const size_t titleColumnLength = UI::TERMINAL_WIDTH - isbnColumnLength - quantityColumnLength - totalPriceColumnLength - bookPriceColumnLength;

	for (int i = 0; i < cartSize; i++) {
		std::cout << std::left;

		std::cout << std::setw(isbnColumnLength) << cart[i].isbn
			<< std::setw(titleColumnLength) << cart[i].title
			<< std::setw(quantityColumnLength) << cart[i].quantity
			<< std::setw(totalPriceColumnLength) << cart[i].retail
			<< std::endl << std::endl;
	}
}

void Cashier::printCartForReceipt() {

	for (int i = 0; i < cartSize; i++) {

		std::cout << "\t" << cart[i].isbn << " " << cart[i].title.substr(0, 25) << "...";
		std::cout << std::right << " " << cart[i].retail << std::endl;

	}

	return;
}

void Cashier::clearCart() {

	cart.reset();
	cart = std::make_unique<InventoryBook[]>(100);
	cartSize = 0;

}