#define _CRT_SECURE_NO_WARNINGS

#include "Cashier.h"
#include "InventoryDatabase.h"

// Constructor 
Cashier::Cashier(InventoryDatabase* pD)
{
	pInventoryDatabase = pD;
	cart = nullptr;
	cartSize = 0;
}

// Adds book to cart by prompting the user for the ISBN number 
void Cashier::addBookToCart(InventoryBook book){
   std::unique_ptr<InventoryBook[]> books = pInventoryDatabase->getInventoryArray();
   int bookCount = pInventoryDatabase->getInventoryArraySize();

    for(int i = 0; i < bookCount; i++){
        if((books[i].isbn == book.isbn) && (books[i].quantity > 0)){
            if(findBook(book.isbn) != -1){
                cart[findBook(book.isbn)].quantity++;
                //inv[i].quantity--; Only do this in checkout()
            }
            else {
                cart[cartSize] = books[i];
                cart[cartSize].quantity = 0;
                cartSize++;
                //inv[i].quantity--; Only do this in checkout()
            }
        }
        else if(books[i].isbn == book.isbn){
            //std::cout << "There are no more books of this ISBN number availiable." << std::endl; // Create function for this 
        }
        else {
            //std::cout << "Book not found." << std::endl;
        }
    }
}

// Removes book from cart by prompting the user for the ISBN number 
void Cashier::removeBookFromCart(InventoryBook book) {
	std::unique_ptr<InventoryBook[]> books = pInventoryDatabase->getInventoryArray();
	int bookCount = pInventoryDatabase->getInventoryArraySize();

	for (int i = 0; i < bookCount; i++) {
		if ((books[i].isbn == book.isbn) && (books[i].quantity > 0)) {
			if (findBook(book.isbn) != -1) {
				cart[findBook(book.isbn)].quantity--;
				books[i].quantity++;
			}
		}
		else if (books[i].isbn == book.isbn) {
			//std::cout << "There are no more books of this ISBN number availiable." << std::endl;
		}
		else {
			//std::cout << "Book not found." << std::endl;
		}
	}
}

// Returns -1 if the book is not in the array, else returns the index the book
// is at
int Cashier::findBook(std::string isbnNum){
    for(int i = 0; i < cartSize; i++){
        if(cart[i].isbn == isbnNum){ // -$Olivier: You were using strcmp here, we are using string class and not C strings so we should use string functions and string operators.
            return i;
        }
    }
    return -1;
}

// Checks out books in cart by calculating the total price using sales tax 
void Cashier::checkout(){ // Change this to return price of books in cart and create function to return price of each book
    double price = 0, totalPrice = 0;
    for(int i = 0; i < cartSize; i++){
		totalPrice += cart[i].quantity * cart[i].wholesale; // -$Olivier Get inv to be a pointer to InventoryDatabase and this should work
    }
    //int totalPrice = return totalPrice * SALES_TAX; -$Olivier Can't have a return statement on the right side of assignment, re-written following this comment
	return;
}

// Create function that checks out books, or reduce quantity by 1 

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