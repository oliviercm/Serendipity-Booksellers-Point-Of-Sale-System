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
void displayWholeSaleInv();
void displayRetailInv();
void displayListQuantity();
void displayListCost();
void displayListAged();
void displayGoodbye();
string generateBars(int number);
int getUserOption(int min, int max);
void clearScreen();

namespace UI
{
	const int TERMINAL_WIDTH = 130;
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

	//Pointer to cashier
	Cashier *pCashierMode;
	pCashierMode = new Cashier; //Do not forget to delet this

	do
	{
		displayMainMenu();

		inputMainMenu = getUserOption(UI::MAIN_MENU_OPTIONS::CASHIER, UI::MAIN_MENU_OPTIONS::EXIT);

		switch (inputMainMenu)
		{
		case UI::MAIN_MENU_OPTIONS::CASHIER:
			displayCashierModule();
			inputSubMenu = getUserOption(1, 4);
			if (inputSubMenu = 1) {
				pCashierMode->startCashier();
				system("pause");
			}
			break;
		case UI::MAIN_MENU_OPTIONS::INVENTORY:
			displayInventoryModule();
			inputSubMenu = getUserOption(1, 4);
			break;
		case UI::MAIN_MENU_OPTIONS::REPORT:
			displayReportModule();
			inputSubMenu = getUserOption(1, 6);
			if (inputSubMenu == 1) {
				displayInventoryList();
				system("pause");
			}else if (inputSubMenu == 2) {
				displayWholeSaleInv();
				system("pause");
			}else if (inputSubMenu == 3) {
				displayRetailInv();
				system("pause");
			}else if (inputSubMenu == 4) {
				displayListQuantity();
				system("pause");
			}else if (inputSubMenu == 5) {
				displayListCost();
				system("pause");
			}else if (inputSubMenu == 6) {
				displayListAged();
				system("pause");
			}
			break;
		case UI::MAIN_MENU_OPTIONS::EXIT:
			displayGoodbye();
			break;
		default:
			break;
		}
	} while (inputMainMenu != UI::MAIN_MENU_OPTIONS::EXIT);

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

	cout << setw(titleMargin - 5) << title << endl << endl
		<< bars << endl << endl
		<< setw((optionMargin + mainMenuText.length())+3) << mainMenuText << endl << endl
		<< setw(optionMargin + cashierText.length()) << cashierText << endl << endl
		<< setw(optionMargin + inventoryText.length()) << inventoryText << endl << endl
		<< setw(optionMargin + reportText.length()) << reportText << endl << endl
		<< setw(optionMargin + exitText.length()) << exitText << endl << endl
		<< bars << endl << endl;

	return;
}

void displayCashierModule() {

	clearScreen();

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string cashierModeText = "[ CASHIER MODE ] ";
	const string purchaseText = "[ 1 ] PURCHASE A BOOK ";
	const string rentText = "[ 2 ] RENT A BOOK ";
	const string exitText = "[ 3 ] EXIT ";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + cashierModeText.length()) / 2;
	const size_t optionMargin = titleMargin - cashierModeText.length();

	cout << endl;
	cout << bars << endl;
	cout << endl;
	cout << setw(titleMargin + 3) << cashierModeText << endl;
	cout << endl;
	cout << setw(optionMargin + purchaseText.length()) << purchaseText << endl;
	cout << endl;
	cout << setw(optionMargin + rentText.length()) << rentText << endl;
	cout << endl;
	cout << setw(optionMargin + exitText.length()) << exitText << endl;
	cout << endl;
	cout << bars << endl;
	cout << endl;

	return;
}

void displayInventoryModule() {

	clearScreen();

	//Pointer to Inventory Database
	InventoryDatabase *pInvMode;
	pInvMode = new InventoryDatabase; //Do not forget to delet this


	//Book book = Book("1234567890", "Harry Potter", "J.K Rolling", "blabla", "02/03/2019", 3, 35.29, 30.99);
	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string inventoryModuleText = "[ INVENTORY ]";
	const string bookTitle = "TITLE:";
	const string bookAuthor = "AUTHOR:";
	const string bookPublisher = "PUBLISHER:";
	const string bookDate = "DATE:";
	const string bookOnHand = "ON-HAND:";
	const string bookWholePrice = "WHOLESALE-PRICE:";
	const string bookRetailPrice = "RETAIL-PRICE:";
	const string bookIsbn = "ISBN:";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + inventoryModuleText.length()) / 2;
	const size_t optionMargin = titleMargin - inventoryModuleText.length();

	cout << endl;
	cout << bars << endl << endl;
	cout << right << setw(titleMargin + 3) << inventoryModuleText << endl << endl;
	cout << left << bookTitle
		<< right << setw((UI::TERMINAL_WIDTH)/7) << bookAuthor
		<< right << setw((UI::TERMINAL_WIDTH) / 7) << bookPublisher
		<< right << setw((UI::TERMINAL_WIDTH) / 7) << bookDate
		<< right << setw((UI::TERMINAL_WIDTH) / 7) << bookOnHand
		<< right << setw((UI::TERMINAL_WIDTH) / 7) << bookWholePrice
		<< right << setw((UI::TERMINAL_WIDTH) / 7) << bookRetailPrice
		<< right << setw(((UI::TERMINAL_WIDTH) / 7)-5) << bookIsbn << endl << endl;
	cout << bars;
	
	int bookNum = pInvMode->getInventoryArraySize();
	std::unique_ptr<InventoryBook[]> inventoryArray = pInvMode->getInventoryArray();

	for (int i = 0; i < bookNum; i++) {

		cout << left << inventoryArray[i].title
			<< right << setw(5) << "*" << right << setw(12) << inventoryArray[i].author
			<< right << setw(5) << "*" << right << setw(15) << inventoryArray[i].publisher
			<< right << setw(7) << "*" << right << setw(8) << inventoryArray[i].addDate
			<< right << setw(1) << "*" << right << setw(1) << inventoryArray[i].quantity
			<< right << setw(2) << "*" << right << setw(18) << inventoryArray[i].wholesale
			<< right << setw(2) << "*" << right << setw(14) << inventoryArray[i].retail
			<< right << setw(3) << "*" << right << setw(10) << inventoryArray[i].isbn << endl;
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

void displayReportModule() {

	clearScreen();

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string reportModuleText = "[ REPORT MODE ] ";
	const string inventoryListText = "[ 1 ] INVENTORY LIST ";
	const string wholeSaleText = "[ 2 ] WHOLESALE INVENTORY ";
	const string retailInventoryText = "[ 3 ] RETAIL INVENTORY ";
	const string listByQuantityText = "[ 4 ] LIST BY QUANTITY ";
	const string listByCostText = "[ 5 ] LIST BY COST ";
	const string listByAgedText = "[ 6 ] LIST BY AGE ";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + reportModuleText.length()) / 2;
	const size_t optionMargin = titleMargin - reportModuleText.length();

	cout << endl;
	cout << bars << endl;
	cout << endl;
	cout << setw(titleMargin + 3) << reportModuleText << endl;
	cout << endl;
	cout << setw(optionMargin + inventoryListText.length()) << inventoryListText << endl;
	cout << endl;
	cout << setw(optionMargin + wholeSaleText.length()) << wholeSaleText << endl;
	cout << endl;
	cout << setw(optionMargin + retailInventoryText.length()) << retailInventoryText << endl;
	cout << endl;
	cout << setw(optionMargin + listByQuantityText.length()) << listByQuantityText << endl;
	cout << endl;
	cout << setw(optionMargin + listByCostText.length()) << listByCostText << endl;
	cout << endl;
	cout << setw(optionMargin + listByAgedText.length()) << listByAgedText << endl;
	cout << endl;
	cout << bars << endl;
	cout << endl;

	return;
}

void displayInventoryList() {

	clearScreen();

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string inventoryModuleText = "[ INVENTORY ]";
	const string bookTitle = "TITLE:";
	const string bookAuthor = "AUTHOR:";
	const string bookOnHand = "ON-HAND:";
	const string bookIsbn = "ISBN:";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + inventoryModuleText.length()) / 2;
	const size_t optionMargin = titleMargin - inventoryModuleText.length();

	cout << endl;
	cout << bars << endl;
	cout << endl;
	cout << right << setw(titleMargin + 3) << inventoryModuleText << endl;
	cout << endl;
	cout << left << bookTitle
		<< right << setw((UI::TERMINAL_WIDTH) / 4) << bookAuthor
		//<< right << setw((UI::TERMINAL_WIDTH) / 7) << bookPublisher
		//<< right << setw((UI::TERMINAL_WIDTH) / 7) << bookDate
		<< right << setw((UI::TERMINAL_WIDTH) / 4) << bookOnHand
		//<< right << setw((UI::TERMINAL_WIDTH) / 7) << bookWholePrice
		//<< right << setw((UI::TERMINAL_WIDTH) / 7) << bookRetailPrice
		<< right << setw((UI::TERMINAL_WIDTH) / 4) << bookIsbn << endl;
	cout << endl;
	cout << bars;



	/*
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
	*/
	return;
}

void displayWholeSaleInv() {

	cout << endl;
	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string wholeSaleText = "[ WHOLESALE INVENTORY ]";
	const string bookTitle = "TITLE:";
	const string bookAuthor = "AUTHOR:";
	const string bookWholePrice = "WHOLESALE-PRICE:";
	const string bookIsbn = "ISBN:";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + wholeSaleText.length()) / 2;

	//Pointer to Inventory Database
	InventoryDatabase *pInvMode;
	pInvMode = new InventoryDatabase; //Do not forget to delet this

	cout << bars << endl << endl;
	cout << setw(titleMargin + 3) << wholeSaleText << endl << endl;
	cout << left << bookWholePrice
		<< right << setw((UI::TERMINAL_WIDTH) / 4) << bookTitle
		<< right << setw((UI::TERMINAL_WIDTH) / 4) << bookAuthor
		<< right << setw((UI::TERMINAL_WIDTH) / 4) << bookIsbn << endl <<endl;
	cout << bars;



	return;
}

void displayRetailInv() {

	cout << endl;
	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string retailInventoryText = "[ RETAIL INVENTORY ]";
	const string bookTitle = "TITLE:";
	const string bookAuthor = "AUTHOR:";
	const string bookRetailPrice = "RETAIL-PRICE:";
	const string bookIsbn = "ISBN:";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + retailInventoryText.length()) / 2;

	//Pointer to Inventory Database
	InventoryDatabase *pInvMode;
	pInvMode = new InventoryDatabase; //Do not forget to delet this

	cout << bars << endl << endl;
	cout << setw(titleMargin + 3) << retailInventoryText << endl << endl;
	cout << left << bookRetailPrice
		<< right << setw((UI::TERMINAL_WIDTH) / 4) << bookTitle
		<< right << setw((UI::TERMINAL_WIDTH) / 4) << bookAuthor
		<< right << setw((UI::TERMINAL_WIDTH) / 4) << bookIsbn << endl << endl;
	cout << bars;
	return;
}

void displayListQuantity() {

	cout << endl;
	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string listByQuantityText = "[ LIST BY QUANTITY ]";
	const string bookTitle = "TITLE:";
	const string bookAuthor = "AUTHOR:";
	const string bookOnHand = "ON-HAND:";
	const string bookIsbn = "ISBN:";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + listByQuantityText.length()) / 2;

	//Pointer to Inventory Database
	InventoryDatabase *pInvMode;
	pInvMode = new InventoryDatabase; //Do not forget to delet this

	cout << bars << endl << endl;
	cout << setw(titleMargin + 3) << listByQuantityText << endl << endl;
	cout << left << bookOnHand
		<< right << setw((UI::TERMINAL_WIDTH) / 4) << bookTitle
		<< right << setw((UI::TERMINAL_WIDTH) / 4) << bookAuthor
		<< right << setw((UI::TERMINAL_WIDTH) / 4) << bookIsbn << endl << endl;
	cout << bars;

	return;
}

void displayListCost() {

	cout << endl;
	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string listByCostText = "[ LIST BY COST ]";
	const string bookTitle = "TITLE:";
	const string bookAuthor = "AUTHOR:";
	const string bookWholePrice = "WHOLESALE-PRICE:";
	const string bookRetailPrice = "RETAIL-PRICE:";
	const string bookIsbn = "ISBN:";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + listByCostText.length()) / 2;

	//Pointer to Inventory Database
	InventoryDatabase *pInvMode;
	pInvMode = new InventoryDatabase; //Do not forget to delet this

	cout << bars << endl << endl;
	cout << setw(titleMargin + 3) << listByCostText << endl << endl;
	cout << left << bookWholePrice
		<< right << setw((UI::TERMINAL_WIDTH) / 5) << bookRetailPrice
		<< right << setw((UI::TERMINAL_WIDTH) / 5) << bookTitle
		<< right << setw((UI::TERMINAL_WIDTH) / 5) << bookAuthor
		<< right << setw((UI::TERMINAL_WIDTH) / 5) << bookIsbn << endl << endl;
	cout << bars;

	return;
}

void displayListAged() {

	cout << endl;
	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string listByAgedText = "[ LIST BY AGE ]";
	const string bookTitle = "TITLE:";
	const string bookAuthor = "AUTHOR:";
	const string bookDate = "DATE:";
	const string bookIsbn = "ISBN:";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + listByAgedText.length()) / 2;

	//Pointer to Inventory Database
	InventoryDatabase *pInvMode;
	pInvMode = new InventoryDatabase; //Do not forget to delet this

	cout << bars << endl << endl;
	cout << setw(titleMargin + 3) << listByAgedText << endl << endl;
	cout << left << bookDate
		<< right << setw((UI::TERMINAL_WIDTH) / 4) << bookTitle
		<< right << setw((UI::TERMINAL_WIDTH) / 4) << bookAuthor
		<< right << setw((UI::TERMINAL_WIDTH) / 4) << bookIsbn << endl << endl;
	cout << bars;

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
	} while (!cin || inputInt < min || inputInt > max);

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