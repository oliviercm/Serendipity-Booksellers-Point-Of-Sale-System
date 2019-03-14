#define _CRT_SECURE_NO_WARNINGS
#include "Cashier.h"
#include "InventoryDatabase.h"

// Constructor 
Cashier::Cashier(InventoryDatabase * data2){
    cart = new InventoryBook;
    cartLength = 0;
	data = data2; 
	inv = data->getInventoryArray();
}

void Cashier::startCashier(){
    std::cout << "Welcome to the cashier." << std::endl;
    
    int choice;
    do {
        std::cout << "Press 1 to add books to your cart, or press 2 to proceed to checkout: ";
        std::cin >> choice;
        if(choice == 1){
            addBookToCart();
        }
        else {
            checkout();
        }
    }while(choice != 2);

	return;
}

// Adds book to cart by prompting the user for the ISBN number 
void Cashier::addBookToCart(){
    std::string isbn;
	std::cout << "What is the ISBN number of the book?: ";
	std::cin >> isbn;

	// -$Olivier I added this here, this is a probable way of getting the number of books in the inventory. 
	// You need inv to be a pointer to an InventoryDatabase object, don't create your own. 
	// Instead store a reference in a member variable and let main.cpp set your reference somehow.
	int bookCount = data->getInventoryArraySize(); 

    for(int i = 0; i < bookCount; i++){
        if((inv[i].isbn == isbn) && (inv[i].quantity > 0)){
            if(findBook(isbn) != -1){
                cart[findBook(isbn)].quantity++;
                inv[i].quantity--; 
            }
            else {
                cart[cartLength] = inv[i];
                cart[cartLength].quantity = 0;
                cartLength++;
                inv[i].quantity--;
            }
        }
        else if(inv[i].isbn == isbn){
            std::cout << "There are no more books of this ISBN number availiable." << std::endl;
        }
        else {
            std::cout << "Book not found." << std::endl;
        }
    }
}

// Removes book from cart by prompting the user for the ISBN number 
void Cashier::removeBookFromCart() {
	std::string isbn;
	std::cout << "What is the ISBN number of the book?: ";
	std::cin >> isbn;

	// -$Olivier I added this here, this is a probable way of getting the number of books in the inventory. 
	// You need inv to be a pointer to an InventoryDatabase object, don't create your own. 
	// Instead store a reference in a member variable and let main.cpp set your reference somehow.
	int bookCount = data->getInventoryArraySize();

	for (int i = 0; i < bookCount; i++) {
		if ((inv[i].isbn == isbn) && (inv[i].quantity > 0)) {
			if (findBook(isbn) != -1) {
				cart[findBook(isbn)].quantity--;
				inv[i].quantity++;
			}
		}
		else if (inv[i].isbn == isbn) {
			std::cout << "There are no more books of this ISBN number availiable." << std::endl;
		}
		else {
			std::cout << "Book not found." << std::endl;
		}
	}
}

// Returns -1 if the book is not in the array, else returns the index the book
// is at
int Cashier::findBook(std::string isbnNum){
    for(int i = 0; i < cartLength; i++){
        if(cart[i].isbn == isbnNum){ // -$Olivier: You were using strcmp here, we are using string class and not C strings so we should use string functions and string operators.
            return i;
        }
    }
    return -1;
}

// Checks out books in cart by calculating the total price using sales tax 
double Cashier::checkout(){
    int price = 0, totalPrice = 0;
    for(int i = 0; i < cartLength; i++){
		totalPrice += cart[i].quantity * cart[i].wholesale; // -$Olivier Get inv to be a pointer to InventoryDatabase and this should work
    }
    //int totalPrice = return totalPrice * SALES_TAX; -$Olivier Can't have a return statement on the right side of assignment, re-written following this comment
	return totalPrice * SALES_TAX;
}

// Destructor
Cashier::~Cashier()
{
    delete cart;
}
