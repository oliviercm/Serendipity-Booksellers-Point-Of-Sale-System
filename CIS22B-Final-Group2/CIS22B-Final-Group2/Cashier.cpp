#define _CRT_SECURE_NO_WARNINGS
#include "Cashier.h"

Cashier::Cashier(){
    cart = new Book;
    cartLength = 0;
    SALES_TAX = 0.9;
}

int Cashier::startCashier(){
    cout << "Welcome to the cashier." << endl;
    
    int choice;
    do {
        cout << "Press 1 to add books to your cart, or press 2 to proceed to checkout: ";
        cin >> choice;
        if(choice == 1){
            addBookToCart();
        }
        else {
            checkout();
        }
    }while(choice != 2);
}

void Cashier::addBookToCart(){
    string isbn;
    cout << "What is the ISBN number of the book?: ";
    cin >> isbn;
    for(int i = 0; i < inv->getBookCount(); i++){
        if((inv[i].isbn).strcmp(isbn) == 0 && (inv[i].quantity > 0)){
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
        else if((inv[i].isbn).strcmp(isbn) == 0){
            cout << "There are no more books of this ISBN number availiable." << endl;
        }
        else {
            cout << "Book not found." << endl;
        }
    }
}

// Returns -1 if the book is not in the array, else returns the index the book
// is at
int Cashier::findBook(string isbnNum){
    for(int i = 0; i < cartLength; i++){
        if((cart[i].isbn).strcmp(isbn) == 0){
            return i;
        }
    }
    return -1;
}

void Cashier::checkout(){
    int price = 0;
    for(int i = 0; i < cartLength; i++){
        totalPrice += inv[i].quantity * inv[i].wholesale;
    }
    int totalPrice = return totalPrice * SALES_TAX;
}

// Destructor
Cashier::~Cashier()
{
    delete cart;
}
