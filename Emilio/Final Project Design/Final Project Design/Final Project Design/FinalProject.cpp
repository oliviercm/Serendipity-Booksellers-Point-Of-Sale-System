/*
CIS 22B
Final: Serendipity Booksellers POS System
Group 2:
Olivier Chan Sion Moy
Luis Guerrero
Natalia Coelho Mendonca
Samuel Ruiz Cervantes
Manasi Gowda
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include "InventoryDatabase.h"
#include "Book.h"

using namespace std;	

void displayMainMenu();
void displayCashierModule();
void displayInventoryModule();
void displayReport();
void displayInventoryList();


int main() {
	system("mode 120, 50");

	const bool debug = true;
	if (debug)
	{
		InventoryDatabase inventoryDatabase("book.txt");
		inventoryDatabase.buildInventoryArray();
	}
	
	Book book = Book();
	/*
	book.quantity = 1;

	std::cout << book << std::endl;

	std::cout << ++book << std::endl;

	std::cin.get();
	*/
	
	int input, userOption, again;
	ifstream inputFile("Text.txt");
	string str;
	string title, s;
	
	enum options {option0, cashierModule, inventoryModule, reportModule, exit};
	do {
		displayMainMenu();
		cout << "Choose an option : ";
		cin >> input;
		while (input != 1 && input != 2 && input != 3 && input != 4) {
			cerr << endl;
			cerr << "EEROR: Not an option, try again" << endl << endl;
			cerr << "Choose one of the options: ";
			cin >> input;
			cerr << endl;
		}
		switch (input)
		{
		case cashierModule:
			displayCashierModule();
			cin >> userOption;
			break;
		case inventoryModule:
			displayInventoryModule();
			break;
		case reportModule:
			displayReport();
			cout << "Choose an option: ";
			cin >> userOption;
			if (userOption == 1) {
				displayInventoryList();
			}
		case exit:
			cout << "Thank you, bye..." << endl;
			break;
		default:
			break;
		}

		cout << "Would you like to see the main manu again?" << endl;
		cout << "\t[1]Yes	[2]No: ";
		cout << endl;
		cin >> again;
	} while ( again == 1);

	system("pause");
	return 0;
}

void displayMainMenu() {

	const string bars = "========================================================================================================================";
	const string title = "Welcome to Serendipity Booksellers.";
	const string mainMenuText = "[ MAIN MENU ]";
	const string cashierModeText = "[ 1 ] CASHIER MODE";
	const string inventoryText = "[ 2 ] INVENTORY MODE ";
	const string reportText = "[ 3 ] REPORT MODE ";
	const string exitText = "[ 4 ] EXIT ";

	cout << endl;
	cout << setw((bars.length() + title.length()) / 2) << title << endl;
	cout << endl;
	cout << bars << endl;
	cout << endl;
	cout << setw((bars.length() + mainMenuText.length())/2) << mainMenuText << endl;
	cout << endl;
	cout << setw((bars.length() + cashierModeText.length())/2) << cashierModeText << endl;
	cout << endl;
	cout << setw(((bars.length() + inventoryText.length())) - ((bars.length() + cashierModeText.length()))) << inventoryText << endl;
	cout << endl;
	cout << setw((bars.length() + reportText.length())/2) << reportText << endl;
	cout << endl;
	cout << setw((bars.length() + exitText.length()) / 2) << exitText << endl;
	cout << endl;
	cout << bars << endl;
	cout << endl;

	return;
}

void displayCashierModule() {

	const string bars = "========================================================================================================================";
	const string cashierModeText = "[ CASHIER MODE ] ";
	const string purchaseText = "[ 1 ] PURCHASE A BOOK ";
	const string rentText = "[ 2 ] RENT A BOOK ";
	const string exitText = "[ 4 ] EXIT ";

	cout << endl;
	cout << bars << endl;
	cout << endl;
	cout << setw((bars.length() + cashierModeText.length())/2) << cashierModeText << endl;
	cout << endl;
	cout << setw((bars.length() + purchaseText.length()) / 2) << purchaseText << endl;
	cout << endl;
	cout << setw((bars.length() + rentText.length()) / 2) << rentText << endl;
	cout << endl;
	cout << setw((bars.length() + exitText.length()) / 2) << exitText << endl;
	cout << endl;
	cout <<bars << endl;
	cout << endl;

	return;
}

void displayInventoryModule() {

	//Book book = Book("1234567890", "Harry Potter", "J.K Rolling", "blabla", "02/03/2019", 3, 35.29, 30.99);
	const string bars = "========================================================================================================================";
	const string inventoryModuleText = "[ INVENTORY ] ";
	const string bookTitle = "TITLE: ";
	const string bookAuthor = "AUTHOR: ";
	const string bookPublisher = "PUBLISHER: ";
	const string bookDate = "DATE: ";
	const string bookOnHand = "ON-HAND: ";
	const string bookWholePrice = "WHOLESALE-PRICE: ";
	const string bookRetailprice = "RETAIL-PRICE: ";
	const string bookIsbn = "ISBN: ";
	cout << endl;
	cout << bars << endl;
	cout << endl;
	cout << right << setw((bars.length() + inventoryModuleText.length()) / 2) << "[ INVENTORY ] " << endl;
	cout << endl;
	cout << left << "TITLE:"
		<< right << setw(17) << "AUTHOR:"
		<< right << setw(20) << "PUBLISHER:"
		<< right << setw(15) << "DATE:"
		<< right << setw(11) << "ON-HAND:"
		<< right << setw(21) << "WHOLESALE-PRICE:"
		<< right << setw(15) << "RETAIL PRICE:"
		<< right << setw(10) << "ISBN:" << endl;
	cout << endl;
	cout << bars;

	for (int i = 0; i < 3; i++) {
		Book book = InventoryDatabase::inventoryArray[i];
		cout << left << book.title
			<< right << setw(5) << "#" << right << setw(12)<< book.author
			<< right << setw(5) << "#" << right << setw(15) << book.publisher
			<< right << setw(7) << "#" << right << setw(8) << book.addDate
			<< right << setw(1) << "#" << right << setw(1) << book.quantity
			<< right << setw(2) << "#" << right << setw(18) << book.wholesale
			<< right << setw(2) << "#" << right << setw(14) << book.retail
			<< right << setw(3) << "#" << right << setw(10) << book.isbn << endl;
	}

	/*
	cout << setw((bars.length() + cashierModeText.length()) / 2) << "TITLE: " << " Physics for Scientist and Engineers (9th edition)" << endl << endl
		<< setw((bars.length() + cashierModeText.length()) / 2) << "AUTHOR: " << "Jewett Serway" << endl << endl
		<< setw((bars.length() + cashierModeText.length()) / 2) << "PUBLISHER: " <<"Cengage Learning" << endl << endl
		<< setw((bars.length() + cashierModeText.length()) / 2) << "DATE: " << "02/21/2019" << endl << endl
		<< setw((bars.length() + cashierModeText.length()) / 2) << "ON-HAND: " << "5" << endl << endl
		<< setw((bars.length() + cashierModeText.length()) / 2) << "WHOLESALE-PRICE: " << "155.93" << endl << endl
		<< setw((bars.length() + cashierModeText.length()) / 2) << "RETAIL-PRICE: " << "164.99" << endl << endl
		<< setw((bars.length() + cashierModeText.length()) / 2) << "ISBN: " << "9781305116405"  << endl;
	cout << endl;
	*/
	cout << endl;
	cout << bars << endl;
	cout << endl;

	return;
}

void displayReport() {
	const string bars = "========================================================================================================================";
	const string reportModuleText = "[ REPORT MODE ] ";
	const string inventoryListText = "[ 1 ] INVENTORY LIST ";
	const string wholeSaleText = "[ 2 ] WHOLESALE INVENTORY ";
	const string retailInventoryText = "[ 3 ] RETAIL INVENTORY ";
	const string listByQuantityText = "[ 4 ] LIST BY QUANTITY ";
	const string listByCostText = "[ 5 ] LIST BY COST ";
	const string listByAgedText = "[ 6 ] LIST BY AGE ";
	
	cout << endl;
	cout << bars << endl;
	cout << endl;
	cout << setw((bars.length() + reportModuleText.length())/2) << reportModuleText << endl;
	cout << endl;
	cout << setw((bars.length() + inventoryListText.length()) / 2) << inventoryListText << endl;
	cout << endl;
	cout << setw((bars.length() + wholeSaleText.length()) / 2) << wholeSaleText << endl;
	cout << endl;
	cout << setw((bars.length() + retailInventoryText.length()) / 2) << retailInventoryText << endl;
	cout << endl;
	cout << setw((bars.length() + listByQuantityText.length()) / 2) << listByQuantityText << endl;
	cout << endl;
	cout << setw((bars.length() + listByCostText.length()) / 2) << listByCostText << endl;
	cout << endl;
	cout << setw((bars.length() + listByAgedText.length()) / 2) << listByAgedText << endl;
	cout << endl;
	cout << bars << endl;
	cout << endl;

	return;
}

void displayInventoryList() {

	cout << "===================================================" << endl;
	cout << endl;
	cout << setw(31) << "[ INVENTORY LIST ] " << endl;
	cout << endl;
	cout << setw(5) << "TITLE: " << " Physics for Scientist and Engineers (9th edition)" << endl << endl
		<< setw(5) << "AUTHOR: " << "Jewett Serway" << endl << endl
		<< setw(5) << "PUBLISHER: " << "Cengage Learning" << endl << endl
		<< setw(5) << "DATE: " << "02/21/2019" << endl << endl
		<< setw(5) << "ON-HAND: " << "5" << endl << endl
		<< setw(5) << "WHOLESALE-PRICE: " << "155.93" << endl << endl
		<< setw(5) << "RETAIL-PRICE: " << "164.99" << endl << endl
		<< setw(5) << "ISBN: " << "9781305116405" << endl;
	cout << endl;


	cout << "===================================================" << endl;
	cout << endl;

	return;
}

/*
void displayInventory() {
	
	cout << "===================================================" << endl;
	cout << endl;
	cout << right << setw(31) << "[ INVENTORY ] " << endl;
	cout << endl;
	cout << left << setw(5) << "TITLE " << right << setw(10) << " AUTHOR " 
		<< right << setw(10) << " PUBLISHER " << right << setw(10) << " DATE "
		<< right << setw(10) << " ON-HAND "
		<< right << setw(10) << " WHOLESALE-PRICE "
		<< right << setw(10) << " RETAIL-PRICE "
		<< right << setw(10) << " ISBN " << endl;

	cout << left << setw(5) << "Physics for Scientist and Engineers (9th edition) " << right << setw(10) << " Jewett Serway "
		<< right << setw(10) << " Cengage Learning " << right << setw(10) << " 02/21/2019 "
		<< right << setw(10) << " 5 "
		<< right << setw(10) << " 155.93 "
		<< right << setw(10) << " 164.99 " 
		<< right << setw(10) << " 9781305116405 " << endl;
	
	cout << "===================================================" << endl;
	cout << endl;

	return;
}
*/