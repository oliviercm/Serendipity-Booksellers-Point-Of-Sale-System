#include <string>
#include <iostream>
#include "InventoryBook.h"

class Cashier {
private:
    Book *cart;
    int cartLength;
    const double SALES_TAX = 0.9;
public:
    // Constructor
	Cashier();
    //Cashier(Book* inv); // Oliver, I need access to the inventory array in the InventoryDatabase
    // Destructor
    ~Cashier();
    
    void startCashier();
    void addBookToCart();
    double checkout();
    int findBook(std::string isbnNum);
};