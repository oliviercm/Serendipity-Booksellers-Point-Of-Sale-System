#define _CRT_SECURE_NO_WARNINGS

#include "Cashier.h"
#include <iostream>

// Constructor 
Cashier::Cashier(InventoryDatabase* pD)
{
	pInventoryDatabase = pD;
	cart = std::make_unique<InventoryBook[]>(100); // Change this?
	cartSize = 0;
	inv = pInventoryDatabase->getInventoryArray();
}

// Adds book to cart by prompting the user for the ISBN number 
void Cashier::addBookToCart(std::string isbnNum){
   int invCount = pInventoryDatabase->getInventoryArraySize();

    for(int i = 0; i < invCount; i++){
        if((inv[i].isbn == isbnNum) && (inv[i].quantity > 0)){ // Will move these checks to main 
            if(findBook(isbnNum) != -1){
                cart[findBook(isbnNum)].quantity++; 
				// Inventory change number??
            }
            else {
                cart[cartSize] = inv[i];
                cart[cartSize].quantity = 0; // Check this 
                cartSize++;
            }
			return;
        }
        else if(inv[i].isbn == isbnNum){
            // std::cout << "There are no more books of this ISBN number availiable in the inventory." << std::endl; // Create function for this 
			return;
        }
    }
	// std::cout << "Book not found in the inventory." << std::endl; // Create function for this 
}

// Removes book from cart by prompting the user for the ISBN number 
void Cashier::removeBookFromCart(std::string isbnNum) {
	for (int i = 0; i < cartSize; i++) {
		if (cart[i].isbn == isbnNum && cart[i].quantity > 0) { // Will move these checks to main 
			cart[i].quantity--; 
			return;
		}
		else if (cart[i].isbn == isbnNum) {
			// std::cout << "There are no more books of this ISBN number availiable in the cart." << std::endl;
			return;
		}
	}
	// std::cout << "Book not found in cart." << std::endl; 
}

// Returns -1 if the book is not in the array (cart), else returns the index the book
// is at
int Cashier::findBook(std::string isbnNum){
	if (cart == nullptr) {
		return -1; 
	}
    for(int i = 0; i < cartSize; i++){
        if(cart[i].isbn == isbnNum){ 
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

// Returns the total price of the books in the cart 
double Cashier::priceOfCart() {
	double totalPrice = 0; 
	for (int i = 0; i < cartSize; i++) {
		totalPrice += cart[i].quantity * cart[i].wholesale; // Check whether we use wholesale or retail 
	}
	return totalPrice * SALES_TAX; 
}

// Checks out books --> reduces quantity in inventory by the amount of books in the cart 
void Cashier::checkout() {
	for (int i = 0; i < cartSize; i++) {
		inv[pInventoryDatabase->getBookIndexByIsbn(cart[i].isbn)].quantity -= cart[i].quantity; 
	}
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