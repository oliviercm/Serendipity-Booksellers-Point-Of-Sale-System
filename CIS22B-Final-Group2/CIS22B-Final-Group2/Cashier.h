#include <string>
#include <iostream>
#include "InventoryBook.h"
#include "InventoryDatabase.h"

class Cashier {
private:
    InventoryBook *cart;
    int cartLength;
    const double SALES_TAX = 0.9;
	InventoryDatabase * data; 
	std::unique_ptr<InventoryBook[]> inv; 

public:
    // Constructor
	Cashier();
    Cashier(InventoryDatabase * data2);

    // Destructor
    ~Cashier();
    
    void startCashier();
    void addBookToCart();
    double checkout();
    int findBook(std::string isbnNum);
};