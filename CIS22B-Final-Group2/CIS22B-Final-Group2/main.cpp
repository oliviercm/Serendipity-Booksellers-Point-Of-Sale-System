/*
CIS 22B
Final: Serendipity Booksellers POS System
Group 2:
	Olivier Chan Sion Moy
	Luis Guerrero
	Samuel Ruiz Cervantes
	Manasi Gowda
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>
#include "InventoryDatabase.h"
#include "InventoryBook.h"
#include "Cashier.h"
#include "Report.h"

using namespace std;

void displayMainMenu();
void displayCashierModule();
void displayInventoryModule();
void displayReportModule();
void displayInventoryList();
void displayGoodbye();
string generateBars(int number);
int getUserOption(int min, int max);
void clearScreen();

namespace UI
{
	const int TERMINAL_WIDTH = 200;
	const int TERMINAL_HEIGHT = 50;

	const string BARS_CHARACTER = "=";

	const string GOODBYE_MESSAGE = "Thank you, bye...";

	const string PROMPT_OPTION = "Choose an option: ";

	const string ERR_GENERIC = "ERROR: ";
	const string ERR_EXCEPTION_GENERIC = "ERROR: Exception";
	const string ERR_EXCEPTION_INVALID_ARGUMENT = "ERROR: Invalid option, option is not a valid argument. Are you correctly typing a number or a string?";
	const string ERR_EXCEPTION_OUT_OF_RANGE = "ERROR: Invalid option, option is out of range.";
	const string ERR_INVALID_OPTION_RANGE = "ERROR: Invalid option, option must be between ";

	enum MAIN_MENU_OPTIONS { NONE, CASHIER, INVENTORY, REPORT, EXIT };
}

int main()
{	
	//Initialize and setup InventoryDatabase
	const std::string filePath = "books.txt";

	InventoryDatabase inventoryDatabase;
	inventoryDatabase.buildInventoryArray(filePath);

	//Resize the terminal window
	string systemResizeStr = "mode " + to_string(UI::TERMINAL_WIDTH) + ", " + to_string(UI::TERMINAL_HEIGHT);
	system(systemResizeStr.c_str());

	//Display main menu, get user input
	int inputMainMenu, inputSubMenu;

	do
	{
		displayMainMenu();

		inputMainMenu = getUserOption(UI::MAIN_MENU_OPTIONS::CASHIER, UI::MAIN_MENU_OPTIONS::EXIT);

		switch (inputMainMenu)
		{
		case UI::MAIN_MENU_OPTIONS::CASHIER:
			displayCashierModule();
			inputSubMenu = getUserOption(1, 4);
			break;
		case UI::MAIN_MENU_OPTIONS::INVENTORY:
			displayInventoryModule();
			inputSubMenu = getUserOption(1, 4);
			break;
		case UI::MAIN_MENU_OPTIONS::REPORT:
			displayReportModule();
			inputSubMenu = getUserOption(1, 4);
			if (inputSubMenu == 1) {
				displayInventoryList();
			}
		case UI::MAIN_MENU_OPTIONS::EXIT:
			displayGoodbye();
			break;
		default:
			break;
		}
	}
	while (inputMainMenu != UI::MAIN_MENU_OPTIONS::EXIT);

	system("pause");
	return 0;
}

void displayMainMenu() {
	
	clearScreen();
	
	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string title = "Welcome to Serendipity Booksellers.";
	const string mainMenuText = "[ MAIN MENU ]";
	const string cashierText = "[ 1 ] CASHIER MODE";
	const string inventoryText = "[ 2 ] INVENTORY MODE";
	const string reportText = "[ 3 ] REPORT MODE";
	const string exitText = "[ 4 ] EXIT";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + title.length()) / 2;
	const size_t optionMargin = titleMargin - title.length();

	cout << setw(titleMargin) << title << endl << endl
		<< bars << endl << endl
		<< setw(optionMargin + mainMenuText.length()) << mainMenuText << endl << endl
		<< setw(optionMargin + cashierText.length()) << cashierText << endl << endl
		<< setw(optionMargin + inventoryText.length()) << inventoryText << endl << endl
		<< setw(optionMargin + reportText.length()) << reportText << endl << endl
		<< setw(optionMargin + exitText.length()) << exitText << endl << endl
		<< bars << endl << endl;

	return;
}

void displayCashierModule() {

	clearScreen();
	
	const string bars = "========================================================================================================================";
	const string cashierModeText = "[ CASHIER MODE ] ";
	const string purchaseText = "[ 1 ] PURCHASE A BOOK ";
	const string rentText = "[ 2 ] RENT A BOOK ";
	const string exitText = "[ 3 ] EXIT ";

	cout << endl;
	cout << bars << endl;
	cout << endl;
	cout << setw((bars.length() + cashierModeText.length()) / 2) << cashierModeText << endl;
	cout << endl;
	cout << setw((bars.length() + purchaseText.length()) / 2) << purchaseText << endl;
	cout << endl;
	cout << setw((bars.length() + rentText.length()) / 2) << rentText << endl;
	cout << endl;
	cout << setw((bars.length() + exitText.length()) / 2) << exitText << endl;
	cout << endl;
	cout << bars << endl;
	cout << endl;

	return;
}

void displayInventoryModule() {

	clearScreen();
	
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
	/*
	auto books = inventoryDatabase[i];
	for (int i = 0; i < 3; i++) {
		
		cout << left << book.title
			<< right << setw(5) << "#" << right << setw(12) << book.author
			<< right << setw(5) << "#" << right << setw(15) << book.publisher
			<< right << setw(7) << "#" << right << setw(8) << book.addDate
			<< right << setw(1) << "#" << right << setw(1) << book.quantity
			<< right << setw(2) << "#" << right << setw(18) << book.wholesale
			<< right << setw(2) << "#" << right << setw(14) << book.retail
			<< right << setw(3) << "#" << right << setw(10) << book.isbn << endl;
	}
	*/

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

void displayReportModule() {
	
	clearScreen();
	
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
	cout << setw((bars.length() + reportModuleText.length()) / 2) << reportModuleText << endl;
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

	clearScreen();
	
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

string generateBars(int number)
{
	string bars = string();
	string bar = UI::BARS_CHARACTER;

	for (int i = 0; i < number; i++)
	{
		bars.append(bar);
	}

	return bars;
}

int getUserOption(int min, int max)
{
	string inputString;
	int inputInt = -1;

	do
	{
		bool err = false;
		
		//Prompt the user for input
		cout << UI::PROMPT_OPTION;
		std::getline(std::cin, inputString);

		//Exception handling
		try
		{
			inputInt = stoi(inputString);
		}
		catch (invalid_argument&)
		{
			cerr << UI::ERR_EXCEPTION_INVALID_ARGUMENT << endl;
			err = true;
		}
		catch (out_of_range&)
		{
			cerr << UI::ERR_EXCEPTION_OUT_OF_RANGE << endl;
			err = true;
		}
		catch (...)
		{
			cerr << UI::ERR_EXCEPTION_GENERIC << endl;
			err = true;
		}

		//Check if the input was a valid option, between min and max
		if (!err)
		{
			if (inputInt < min || inputInt > max)
			{
				cerr << UI::ERR_INVALID_OPTION_RANGE << min << " and " << max << " inclusive." << endl;
			}
		}
	}
	while (!cin || inputInt < min || inputInt > max);

	return inputInt;
}

void displayGoodbye()
{
	clearScreen();
	
	cout << UI::GOODBYE_MESSAGE << endl << endl << endl;
}

void clearScreen()
{
	system("CLS");
	return;
} 