#define _CRT_SECURE_NO_WARNINGS

#include "Cashier.h"
#include "InventoryBook.h"

Cashier::Cashier(InventoryDatabase* pD)
{
	pInventoryDatabase = pD;
	cart = nullptr;
	cartSize = 0;
}

void Cashier::addBookToCart(InventoryBook book) {
	/*std::string isbn;
	std::cout << "What is the ISBN number of the book?: ";
	std::cin >> isbn;*/
	
	//InventoryDatabase *pInv;
	//pInv = new InventoryDatabase; //Do not forget to delet this

	//InventoryBook *pInvBook;
	//pInvBook = new InventoryBook; //Do not forget to delet this

	/*
	int bookCount = pInv->getInventoryArraySize(); //$Olivier I added this here, this is a probable way of getting the number of books in the inventory. You need inv to be a pointer to an InventoryDatabase object, don't create your own. Instead store a reference in a member variable and let main.cpp set your reference somehow.
	for(int i = 0; i < bookCount; i++){
		if((pInv->getInventoryArray[i].isbn).strcmp(isbn) == 0 && (pInv->getInventoryArray[i].quantity > 0)){
			if(findBook(isbn) != -1){
				pInvBook[findBook(isbn)].quantity++;
				pInvBook[i].quantity--;
			}
			else {
				pInvBook[cartLength] = pInvBook[i];
				pInvBook[cartLength].quantity = 0;
				cartLength++;
				pInvBook[i].quantity--;
			}
		}
		else if((pInv->getInventoryArray[i].isbn).strcmp(isbn) == 0){
			std::cout << "There are no more books of this ISBN number availiable." << std::endl;
		}
		else {
			std::cout << "Book not found." << std::endl;
		}
	}
	*/
}

// Returns -1 if the book is not in the array, else returns the index the book
// is at
int Cashier::findBook(std::string isbnNum) {
//	for (int i = 0; i < cartLength; i++) {
//		if (cart[i].isbn == isbnNum) { // -$Olivier: You were using strcmp here, we are using string class and not C strings so we should use string functions and string operators.
//			return i;
//		}
//	}
	return -1;
}

void Cashier::checkout() {
	//int price = 0, totalPrice = 0;
	//for (int i = 0; i < cartLength; i++) {
	//	//totalPrice += inv[i].quantity * inv[i].wholesale; -$Olivier Get inv to be a pointer to InventoryDatabase and this should work
	//}
	////int totalPrice = return totalPrice * SALES_TAX; -$Olivier Can't have a return statement on the right side of assignment, re-written following this comment
	//return totalPrice * SALES_TAX;
}