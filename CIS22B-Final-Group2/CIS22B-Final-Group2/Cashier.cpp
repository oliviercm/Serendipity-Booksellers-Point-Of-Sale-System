#define _CRT_SECURE_NO_WARNINGS

#include "Cashier.h"
#include <iostream>

// Constructor 
Cashier::Cashier(InventoryDatabase* pD)
{
	pInventoryDatabase = pD;
	cart = nullptr;
	cartSize = 0;
	inv = pInventoryDatabase->getInventoryArray;
}

// Adds book to cart by prompting the user for the ISBN number 
void Cashier::addBookToCart(std::string isbnNum){
   int invCount = pInventoryDatabase->getInventoryArraySize();

    for(int i = 0; i < invCount; i++){
        if((inv[i].isbn == isbnNum) && (inv[i].quantity > 0)){
            if(findBook(isbnNum) != -1){
                cart[findBook(isbnNum)].quantity++;
                //inv[i].quantity--; Only do this in checkout()
            }
            else {
                cart[cartSize] = inv[i];
                cart[cartSize].quantity = 0;
                cartSize++;
                //inv[i].quantity--; Only do this in checkout()
            }
        }
        else if(inv[i].isbn == isbnNum){
            //std::cout << "There are no more books of this ISBN number availiable." << std::endl; // Create function for this 
        }
        else {
            //std::cout << "Book not found." << std::endl;
        }
    }
}

// Removes book from cart by prompting the user for the ISBN number 
void Cashier::removeBookFromCart(std::string isbnNum) {
	std::unique_ptr<InventoryBook[]> inv = pInventoryDatabase->getInventoryArray();
	int invSize = pInventoryDatabase->getInventoryArraySize();

	for (int i = 0; i < invSize; i++) {
		if ((inv[i].isbn == isbnNum) && (inv[i].quantity > 0)) {
			if (findBook(isbnNum) != -1) {
				cart[findBook(isbnNum)].quantity--;
				inv[i].quantity++;
			}
		}
		else if (inv[i].isbn == isbnNum) {
			std::cout << "There are no more books of this ISBN number availiable." << std::endl; // Separate functions for this 
		}
		else {
			std::cout << "Book not found." << std::endl;
		}
	}
}

// Returns -1 if the book is not in the array, else returns the index the book
// is at
int Cashier::findBook(std::string isbnNum){
    for(int i = 0; i < cartSize; i++){
        if(cart[i].isbn == isbnNum){ 
            return i;
        }
    }
    return -1;
}

// Returns price of a book 
double bookPrice(std::string isbn) {
	if (findBook(isbn) != -1) {
		return 0; 
	}
}

// Returns the total price of the books in the cart 
double priceOfCart() {
	double totalPrice = 0; 
	for (int i = 0; i < cartSize; i++) {
		totalPrice += cart[i].quantity * cart[i].wholesale; 
	}
	return totalPrice * SALES_TAX; 
}

// Checks out books --> reduces quantity in inventory by the amount of books in the cart 
void Cashier::checkout() {
	for (int i = 0; i < cartSize; i++) {
		if (findBook(cart[i].isbn) != -1) {
			inv[findBook(cart[i].isbn)].quantity -= cart[i].quantity; 
		}
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