#include <string>
#include "Book.h"
#include <iostream>

class Cashier {
private:
    Book *cart;
    int cartLength;
    const int SALES_TAX;
public:
    // Constructor
    Cashier(Book* inv); // Oliver, I need access to the inventory array in the InventoryDatabase
    // Destructor
    ~Cashier();
    
    void startCashier();
    void addBookToCart();
    void checkout();
    int findBook(string isbnNum);
}
