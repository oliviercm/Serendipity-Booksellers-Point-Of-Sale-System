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

using namespace std;

void displayMainMenu();

void displayCashierModule();
void cashierSellBooks(InventoryDatabase* pD);

void displayReportModule();
void displayReportInventoryList(std::unique_ptr<InventoryBook[]> books, int numBooks);
void displayReportInventoryWholesaleValue(std::unique_ptr<InventoryBook[]> books, int numBooks);
void displayReportInventoryRetailValue(std::unique_ptr<InventoryBook[]> books, int numBooks);
void displayReportListByQuantity(std::unique_ptr<InventoryBook[]> books, int numBooks);
void displayReportListByCost(std::unique_ptr<InventoryBook[]> books, int numBooks);
void displayReportListByAge(std::unique_ptr<InventoryBook[]> books, int numBooks);
void reportSelectionSortQuantity(InventoryBook* books, int numBooks);
void reportSelectionSortCost(InventoryBook* books, int numBooks);
void reportSelectionSortAge(InventoryBook* books, int numBooks);

/*
void inventoryLookUpBookByIsbn();
void inventoryLookUpBookByTitle();
void inventoryLookUpBookByAuthor();
void inventoryLookUpBookByPublisher();
void inventoryAddBookToFile();
void inventoryDeleteBookFromFile();
void inventoryEditBookByIsbn();
*/

void printHeader();

int getUserInputInt(const int& min = INT_MIN, const int& max = INT_MAX);
double getUserInputDouble(const double& min = DBL_MIN, const double& max = DBL_MAX);
string getUserInputString();

string generateBars(int number);
void clearScreen(bool displayHeader = false);
void pause();
int convertDateToInt(string date);

void displayGoodbye();

namespace UI
{
	const int TERMINAL_WIDTH = 200;
	const int TERMINAL_HEIGHT = 50;

	const string BARS_CHARACTER = "=";

	const string PROMPT_OPTION = "Choose an option: ";

	const string ERR_EXCEPTION_GENERIC = "ERROR: An exception occured.";
	const string ERR_EXCEPTION_INVALID_ARGUMENT = "ERROR: Invalid option, option is not a valid argument. Are you correctly typing a number or a string?";
	const string ERR_EXCEPTION_OUT_OF_RANGE = "ERROR: Invalid option, option is out of range.";
	const string ERR_INVALID_OPTION_RANGE = "ERROR: Invalid option, option must be between ";

	enum MAIN_MENU_OPTIONS { MAIN_NONE, MAIN_CASHIER, MAIN_INVENTORY, MAIN_REPORT, MAIN_EXIT };
	enum CASHIER_OPTIONS { CASHIER_NONE, CASHIER_SELL_BOOKS, CASHIER_BACK };
	enum REPORT_OPTIONS { REPORT_NONE, REPORT_INVENTORY_LIST, REPORT_INVENTORY_WHOLESALE, REPORT_INVENTORY_RETAIL, REPORT_LIST_QUANTITY, REPORT_LIST_COST, REPORT_LIST_AGE, REPORT_BACK };
}

int main()
{
	//Resize the terminal window
	string systemResizeStr = "mode " + to_string(UI::TERMINAL_WIDTH) + ", " + to_string(UI::TERMINAL_HEIGHT);
	system(systemResizeStr.c_str());

	//Format cout
	cout << fixed << setprecision(2);
	
	//Initialize and setup InventoryDatabase
	const std::string filePath = "books.txt";

	InventoryDatabase inventoryDatabase;
	inventoryDatabase.buildInventoryArray(filePath);

	//Display main menu, get user inputs
	int inputMainMenu, inputSubMenu;

	do
	{
		displayMainMenu();

		inputMainMenu = getUserInputInt(UI::MAIN_MENU_OPTIONS::MAIN_CASHIER, UI::MAIN_MENU_OPTIONS::MAIN_EXIT);

		switch (inputMainMenu)
		{
		case UI::MAIN_MENU_OPTIONS::MAIN_CASHIER:
			do
			{
				displayCashierModule();

				inputSubMenu = getUserInputInt(UI::CASHIER_OPTIONS::CASHIER_SELL_BOOKS, UI::CASHIER_OPTIONS::CASHIER_BACK);

				switch (inputSubMenu)
				{
				case UI::CASHIER_OPTIONS::CASHIER_SELL_BOOKS:
					break;
				case UI::CASHIER_OPTIONS::CASHIER_BACK:
					break;
				default:
					break;
				}
			} while (inputSubMenu != UI::CASHIER_OPTIONS::CASHIER_BACK);
			break;
		case UI::MAIN_MENU_OPTIONS::MAIN_INVENTORY:
			//displayInventoryModule(inventoryDatabase);
			inputSubMenu = getUserInputInt(1, 4);
			break;
		case UI::MAIN_MENU_OPTIONS::MAIN_REPORT:
			do
			{
				displayReportModule();

				inputSubMenu = getUserInputInt(UI::REPORT_OPTIONS::REPORT_INVENTORY_LIST, UI::REPORT_OPTIONS::REPORT_BACK);

				switch (inputSubMenu)
				{
				case UI::REPORT_OPTIONS::REPORT_INVENTORY_LIST:
					displayReportInventoryList(inventoryDatabase.getInventoryArray(), inventoryDatabase.getInventoryArraySize());
					pause();
					break;
				case UI::REPORT_OPTIONS::REPORT_INVENTORY_WHOLESALE:
					displayReportInventoryWholesaleValue(inventoryDatabase.getInventoryArray(), inventoryDatabase.getInventoryArraySize());
					pause();
					break;
				case UI::REPORT_OPTIONS::REPORT_INVENTORY_RETAIL:
					displayReportInventoryRetailValue(inventoryDatabase.getInventoryArray(), inventoryDatabase.getInventoryArraySize());
					pause();
					break;
				case UI::REPORT_OPTIONS::REPORT_LIST_QUANTITY:
					displayReportListByQuantity(inventoryDatabase.getInventoryArray(), inventoryDatabase.getInventoryArraySize());
					pause();
					break;
				case UI::REPORT_OPTIONS::REPORT_LIST_COST:
					displayReportListByCost(inventoryDatabase.getInventoryArray(), inventoryDatabase.getInventoryArraySize());
					pause();
					break;
				case UI::REPORT_OPTIONS::REPORT_LIST_AGE:
					displayReportListByAge(inventoryDatabase.getInventoryArray(), inventoryDatabase.getInventoryArraySize());
					pause();
					break;
				case UI::REPORT_OPTIONS::REPORT_BACK:
					break;
				default:
					break;
				}
			} while (inputSubMenu != UI::REPORT_OPTIONS::REPORT_BACK);
			break;
		case UI::MAIN_MENU_OPTIONS::MAIN_EXIT:
			displayGoodbye();
			break;
		default:
			break;
		}
	} while (inputMainMenu != UI::MAIN_MENU_OPTIONS::MAIN_EXIT);

	std::cout << "Press ENTER to exit.";
	std::cin.get();
	return 0;
}

void displayMainMenu() {

	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string titleText = "[ MAIN MENU ]";
	const string cashierText = "[ 1 ] CASHIER MODE";
	const string inventoryText = "[ 2 ] INVENTORY MODE";
	const string reportText = "[ 3 ] REPORT MODE";
	const string exitText = "[ 4 ] EXIT";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + titleText.length()) / 2;
	const size_t optionMargin = titleMargin - titleText.length();
	
	cout << right;
	
	cout << setw(titleMargin) << titleText << endl << endl << bars << endl << endl;

	cout << setw(optionMargin + cashierText.length()) << cashierText << endl << endl
		<< setw(optionMargin + inventoryText.length()) << inventoryText << endl << endl
		<< setw(optionMargin + reportText.length()) << reportText << endl << endl
		<< setw(optionMargin + exitText.length()) << exitText << endl << endl
		<< bars << endl << endl;

	return;
}

/***************************************************************************
*********** CASHIER MODULE
****************************************************************************/

void displayCashierModule() {

	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string cashierModeText = "[ CASHIER MODE ]";
	const string purchaseText = "[ 1 ] SELL BOOKS";
	const string backText = "[ 2 ] BACK";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + cashierModeText.length()) / 2;
	const size_t optionMargin = titleMargin - cashierModeText.length();

	cout << setw(titleMargin) << cashierModeText << endl << endl << bars << endl << endl;

	cout << setw(optionMargin + purchaseText.length()) << cashierModeText << endl << endl
		<< setw(optionMargin + backText.length()) << backText << endl << endl
		<< bars << endl << endl;

	return;
}

void cashierSellBooks(InventoryDatabase* pD)
{
	Cashier cashier(pD);
	bool stop = false;

	while (!stop)
	{
		clearScreen(true);

		const string bars = generateBars(UI::TERMINAL_WIDTH);
		const string sellBooksText = "[ SELL BOOKS ]";
		const string addBooksText = "[ 1 ] ADD BOOKS TO CART";
		const string removeBooksText = "[ 2 ] REMOVE BOOKS FROM CART";
		const string checkoutText = "[ 3 ] CHECKOUT CART";
		const string cancelText = "[ 4 ] CANCEL";

		const size_t titleMargin = (UI::TERMINAL_WIDTH + sellBooksText.length()) / 2;
		const size_t optionMargin = titleMargin - sellBooksText.length();

		cout << setw(titleMargin) << sellBooksText << endl << endl << bars << endl << endl;

		cout << setw(optionMargin + addBooksText.length()) << addBooksText << endl << endl
			<< setw(optionMargin + removeBooksText.length()) << removeBooksText << endl << endl
			<< setw(optionMargin + checkoutText.length()) << checkoutText << endl << endl
			<< setw(optionMargin + cancelText.length()) << cancelText << endl << endl
			<< bars << endl << endl;
	}
}

/***************************************************************************
*********** REPORT MODULE
****************************************************************************/

void displayReportModule() {

	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string reportModeText = "[ REPORT MODE ]";
	const string inventoryListText = "[ 1 ] INVENTORY LIST";
	const string wholesaleValueText = "[ 2 ] INVENTORY WHOLESALE VALUE";
	const string retailValueText = "[ 3 ] INVENTORY RETAIL VALUE";
	const string listByQuantityText = "[ 4 ] LIST BY QUANTITY";
	const string listByCostText = "[ 5 ] LIST BY COST";
	const string listByAgeText = "[ 6 ] LIST BY AGE";
	const string backText = "[ 7 ] BACK";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + reportModeText.length()) / 2;
	const size_t optionMargin = titleMargin - reportModeText.length();

	cout << setw(titleMargin) << reportModeText << endl << endl << bars << endl << endl;

	cout << setw(optionMargin + inventoryListText.length()) << inventoryListText << endl << endl
		<< setw(optionMargin + wholesaleValueText.length()) << wholesaleValueText << endl << endl
		<< setw(optionMargin + retailValueText.length()) << retailValueText << endl << endl
		<< setw(optionMargin + listByQuantityText.length()) << listByQuantityText << endl << endl
		<< setw(optionMargin + listByCostText.length()) << listByCostText << endl << endl
		<< setw(optionMargin + listByAgeText.length()) << listByAgeText << endl << endl
		<< setw(optionMargin + backText.length()) << backText << endl << endl
		<< bars << endl << endl;

	return;
}

void displayReportInventoryList(std::unique_ptr<InventoryBook[]> books, int numBooks) {

	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string titleText = "[ INVENTORY LIST ]";
	const string bookIsbnText = "ISBN:";
	const string bookTitleText = "TITLE:";
	const string bookAuthorText = "AUTHOR:";
	const string bookPublisherText = "PUBLISHER:";
	const string bookDateText = "DATE ADDED:";
	const string bookQuantityText = "ON-HAND:";
	const string bookWholesaleText = "WHOLESALE:";
	const string bookRetailText = "RETAIL:";

	const size_t columnSpacing = 3;

	const size_t isbnColumnLength = 13 + columnSpacing;
	const size_t dateColumnLength = 10 + columnSpacing;
	const size_t quantityColumnLength = bookQuantityText.length() + columnSpacing;
	const size_t wholesaleColumnLength = bookWholesaleText.length() + columnSpacing;
	const size_t retailColumnLength = bookRetailText.length() + columnSpacing;

	const size_t titleColumnLength = (UI::TERMINAL_WIDTH - isbnColumnLength - dateColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 2;
	const size_t authorColumnLength = (UI::TERMINAL_WIDTH - isbnColumnLength - dateColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 4;
	const size_t publisherColumnLength = (UI::TERMINAL_WIDTH - isbnColumnLength - dateColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 4;
	
	const size_t titleMargin = (UI::TERMINAL_WIDTH + titleText.length()) / 2;

	cout << right;
	
	cout << setw(titleMargin) << titleText << endl << endl << bars << endl << endl;

	cout << left;

	cout << setw(isbnColumnLength) << bookIsbnText
		<< setw(titleColumnLength) << bookTitleText
		<< setw(authorColumnLength) << bookAuthorText
		<< setw(publisherColumnLength) << bookPublisherText
		<< setw(dateColumnLength) << bookDateText
		<< setw(quantityColumnLength) << bookQuantityText
		<< setw(wholesaleColumnLength) << bookWholesaleText
		<< setw(retailColumnLength) << bookRetailText
		<< endl << endl;

	for (int i = 0; i < numBooks; i++)
	{
		cout << left;
		
		cout << setw(isbnColumnLength) << books[i].isbn
			<< setw(titleColumnLength) << books[i].title
			<< setw(authorColumnLength) << books[i].author
			<< setw(publisherColumnLength) << books[i].publisher
			<< setw(dateColumnLength) << books[i].addDate
			<< setw(quantityColumnLength) << books[i].quantity
			<< setw(wholesaleColumnLength) << books[i].wholesale
			<< setw(retailColumnLength) << books[i].retail
			<< endl;
	}
	
	cout << endl << bars << endl << endl;

	return;
}

void displayReportInventoryWholesaleValue(std::unique_ptr<InventoryBook[]> books, int numBooks) {

	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string titleText = "[ INVENTORY WHOLESALE VALUE ]";
	const string bookIsbnText = "ISBN:";
	const string bookTitleText = "TITLE:";
	const string bookQuantityText = "ON-HAND:";
	const string bookWholesaleText = "INDIVIDUAL WHOLESALE:";
	const string bookTotalWholesaleText = "COMBINED WHOLESALE:";
	const string inventoryTotalWholesaleText = "INVENTORY TOTAL WHOLESALE VALUE: $";

	const size_t columnSpacing = 3;

	const size_t isbnColumnLength = 13 + columnSpacing;
	const size_t quantityColumnLength = bookQuantityText.length() + columnSpacing;
	const size_t wholesaleColumnLength = bookWholesaleText.length() + columnSpacing;
	const size_t totalWholesaleColumnLength = bookTotalWholesaleText.length() + columnSpacing;

	const size_t titleColumnLength = UI::TERMINAL_WIDTH - isbnColumnLength - quantityColumnLength - wholesaleColumnLength - totalWholesaleColumnLength;

	const size_t titleMargin = (UI::TERMINAL_WIDTH + titleText.length()) / 2;

	cout << right;

	cout << setw(titleMargin) << titleText << endl << endl << bars << endl << endl;

	cout << left;

	cout << setw(isbnColumnLength) << bookIsbnText
		<< setw(titleColumnLength) << bookTitleText
		<< setw(quantityColumnLength) << bookQuantityText
		<< setw(wholesaleColumnLength) << bookWholesaleText
		<< setw(totalWholesaleColumnLength) << bookTotalWholesaleText
		<< endl << endl;

	double inventoryTotalWholesale = 0;
	
	for (int i = 0; i < numBooks; i++)
	{
		double totalWholesale = books[i].quantity * books[i].wholesale;
		inventoryTotalWholesale += totalWholesale;
		
		cout << left;

		cout << setw(isbnColumnLength) << books[i].isbn
			<< setw(titleColumnLength) << books[i].title
			<< setw(quantityColumnLength) << books[i].quantity
			<< setw(wholesaleColumnLength) << books[i].wholesale
			<< setw(totalWholesaleColumnLength) << totalWholesale
			<< endl;
	}

	cout << right;

	cout << endl << bars << endl << endl << setw((UI::TERMINAL_WIDTH + inventoryTotalWholesaleText.length()) / 2) << inventoryTotalWholesaleText << inventoryTotalWholesale << endl << endl << bars << endl << endl;

	return;
}

void displayReportInventoryRetailValue(std::unique_ptr<InventoryBook[]> books, int numBooks) {

	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string titleText = "[ INVENTORY RETAIL VALUE ]";
	const string bookIsbnText = "ISBN:";
	const string bookTitleText = "TITLE:";
	const string bookQuantityText = "ON-HAND:";
	const string bookRetailText = "INDIVIDUAL RETAIL:";
	const string bookTotalRetailText = "COMBINED RETAIL:";
	const string inventoryTotalRetailText = "INVENTORY TOTAL RETAIL VALUE: $";

	const size_t columnSpacing = 3;

	const size_t isbnColumnLength = 13 + columnSpacing;
	const size_t quantityColumnLength = bookQuantityText.length() + columnSpacing;
	const size_t retailColumnLength = bookRetailText.length() + columnSpacing;
	const size_t totalRetailColumnLength = bookTotalRetailText.length() + columnSpacing;

	const size_t titleColumnLength = UI::TERMINAL_WIDTH - isbnColumnLength - quantityColumnLength - retailColumnLength - totalRetailColumnLength;

	const size_t titleMargin = (UI::TERMINAL_WIDTH + titleText.length()) / 2;

	cout << right;

	cout << setw(titleMargin) << titleText << endl << endl << bars << endl << endl;

	cout << left;

	cout << setw(isbnColumnLength) << bookIsbnText
		<< setw(titleColumnLength) << bookTitleText
		<< setw(quantityColumnLength) << bookQuantityText
		<< setw(retailColumnLength) << bookRetailText
		<< setw(totalRetailColumnLength) << bookTotalRetailText
		<< endl << endl;

	double inventoryTotalRetail = 0;

	for (int i = 0; i < numBooks; i++)
	{
		double totalRetail = books[i].quantity * books[i].retail;
		inventoryTotalRetail += totalRetail;

		cout << left;

		cout << setw(isbnColumnLength) << books[i].isbn
			<< setw(titleColumnLength) << books[i].title
			<< setw(quantityColumnLength) << books[i].quantity
			<< setw(retailColumnLength) << books[i].retail
			<< setw(totalRetailColumnLength) << totalRetail
			<< endl;
	}

	cout << right;

	cout << endl << bars << endl << endl << setw((UI::TERMINAL_WIDTH + inventoryTotalRetailText.length()) / 2) << inventoryTotalRetailText << inventoryTotalRetail << endl << endl << bars << endl << endl;

	return;
}

void displayReportListByQuantity(std::unique_ptr<InventoryBook[]> books, int numBooks) {

	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string titleText = "[ LIST BY QUANTITY ]";
	const string bookIsbnText = "ISBN:";
	const string bookTitleText = "TITLE:";
	const string bookQuantityText = "ON-HAND:";

	const size_t columnSpacing = 3;

	const size_t isbnColumnLength = 13 + columnSpacing;
	const size_t quantityColumnLength = bookQuantityText.length() + columnSpacing;

	const size_t titleColumnLength = UI::TERMINAL_WIDTH - isbnColumnLength - quantityColumnLength;

	const size_t titleMargin = (UI::TERMINAL_WIDTH + titleText.length()) / 2;

	cout << right;

	cout << setw(titleMargin) << titleText << endl << endl << bars << endl << endl;

	cout << left;

	cout << setw(isbnColumnLength) << bookIsbnText
		<< setw(titleColumnLength) << bookTitleText
		<< setw(quantityColumnLength) << bookQuantityText
		<< endl << endl;

	std::unique_ptr<InventoryBook[]> copyBooks = std::make_unique<InventoryBook[]>(numBooks);

	for (int i = 0; i < numBooks; i++)
	{
		copyBooks[i].isbn = books[i].isbn;
		copyBooks[i].title = books[i].title;
		copyBooks[i].quantity = books[i].quantity;
	}

	reportSelectionSortQuantity(copyBooks.get(), numBooks);

	for (int i = 0; i < numBooks; i++)
	{
		cout << left;

		cout << setw(isbnColumnLength) << copyBooks[i].isbn
			<< setw(titleColumnLength) << copyBooks[i].title
			<< setw(quantityColumnLength) << copyBooks[i].quantity
			<< endl;
	}

	cout << endl << bars << endl << endl;

	return;
}

void displayReportListByCost(std::unique_ptr<InventoryBook[]> books, int numBooks) {

	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string titleText = "[ LIST BY COST ]";
	const string bookIsbnText = "ISBN:";
	const string bookTitleText = "TITLE:";
	const string bookWholesaleText = "WHOLESALE COST:";

	const size_t columnSpacing = 3;

	const size_t isbnColumnLength = 13 + columnSpacing;
	const size_t wholesaleColumnLength = bookWholesaleText.length() + columnSpacing;

	const size_t titleColumnLength = UI::TERMINAL_WIDTH - isbnColumnLength - wholesaleColumnLength;

	const size_t titleMargin = (UI::TERMINAL_WIDTH + titleText.length()) / 2;

	cout << right;

	cout << setw(titleMargin) << titleText << endl << endl << bars << endl << endl;

	cout << left;

	cout << setw(isbnColumnLength) << bookIsbnText
		<< setw(titleColumnLength) << bookTitleText
		<< setw(wholesaleColumnLength) << bookWholesaleText
		<< endl << endl;

	std::unique_ptr<InventoryBook[]> copyBooks = std::make_unique<InventoryBook[]>(numBooks);

	for (int i = 0; i < numBooks; i++)
	{
		copyBooks[i].isbn = books[i].isbn;
		copyBooks[i].title = books[i].title;
		copyBooks[i].wholesale = books[i].wholesale;
	}

	reportSelectionSortCost(copyBooks.get(), numBooks);

	for (int i = 0; i < numBooks; i++)
	{
		cout << left;

		cout << setw(isbnColumnLength) << copyBooks[i].isbn
			<< setw(titleColumnLength) << copyBooks[i].title
			<< setw(wholesaleColumnLength) << copyBooks[i].wholesale
			<< endl;
	}

	cout << endl << bars << endl << endl;

	return;
}

void displayReportListByAge(std::unique_ptr<InventoryBook[]> books, int numBooks) {

	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string titleText = "[ LIST BY AGE ]";
	const string bookIsbnText = "ISBN:";
	const string bookTitleText = "TITLE:";
	const string bookDateText = "ADD DATE:";

	const size_t columnSpacing = 3;

	const size_t isbnColumnLength = 13 + columnSpacing;
	const size_t dateColumnLength = 10 + columnSpacing;

	const size_t titleColumnLength = UI::TERMINAL_WIDTH - isbnColumnLength - dateColumnLength;

	const size_t titleMargin = (UI::TERMINAL_WIDTH + titleText.length()) / 2;

	cout << right;

	cout << setw(titleMargin) << titleText << endl << endl << bars << endl << endl;

	cout << left;

	cout << setw(isbnColumnLength) << bookIsbnText
		<< setw(titleColumnLength) << bookTitleText
		<< setw(dateColumnLength) << bookDateText
		<< endl << endl;

	std::unique_ptr<InventoryBook[]> copyBooks = std::make_unique<InventoryBook[]>(numBooks);

	for (int i = 0; i < numBooks; i++)
	{
		copyBooks[i].isbn = books[i].isbn;
		copyBooks[i].title = books[i].title;
		copyBooks[i].addDate = books[i].addDate;
	}

	reportSelectionSortAge(copyBooks.get(), numBooks);

	for (int i = 0; i < numBooks; i++)
	{
		cout << left;

		cout << setw(isbnColumnLength) << copyBooks[i].isbn
			<< setw(titleColumnLength) << copyBooks[i].title
			<< setw(dateColumnLength) << copyBooks[i].addDate
			<< endl;
	}

	cout << endl << bars << endl << endl;

	return;
}

void reportSelectionSortQuantity(InventoryBook* books, int numBooks)
{
	for (int startScan = 0; startScan < numBooks - 1; startScan++)
	{
		int minIndex = startScan;
		int maxQuantity = books[startScan].quantity;

		for (int index = startScan + 1; index < numBooks; index++)
		{
			if (books[index].quantity > maxQuantity)
			{
				maxQuantity = books[index].quantity;
				minIndex = index;
			}
		}
		std::swap(books[startScan], books[minIndex]);
	}

	return;
}

void reportSelectionSortCost(InventoryBook* books, int numBooks)
{
	for (int startScan = 0; startScan < numBooks - 1; startScan++)
	{
		int minIndex = startScan;
		double maxWholesale = books[startScan].wholesale;

		for (int index = startScan + 1; index < numBooks; index++)
		{
			if (books[index].wholesale > maxWholesale)
			{
				maxWholesale = books[index].wholesale;
				minIndex = index;
			}
		}
		std::swap(books[startScan], books[minIndex]);
	}

	return;
}

void reportSelectionSortAge(InventoryBook* books, int numBooks)
{
	for (int startScan = 0; startScan < numBooks - 1; startScan++)
	{
		int minIndex = startScan;
		int minDate = convertDateToInt(books[startScan].addDate);

		for (int index = startScan + 1; index < numBooks; index++)
		{
			if (convertDateToInt(books[index].addDate) < minDate)
			{
				minDate = convertDateToInt(books[index].addDate);
				minIndex = index;
			}
		}
		std::swap(books[startScan], books[minIndex]);
	}

	return;
}

/***************************************************************************
*********** HELPER FUNCTIONS
****************************************************************************/

void printHeader()
{
	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string header = "Welcome to Serendipity Booksellers.";

	const size_t headerMargin = (UI::TERMINAL_WIDTH + header.length()) / 2;

	cout << right;
	cout << setw(headerMargin) << header << endl << endl << bars << endl << endl;

	return;
}

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

int getUserInputInt(const int& min, const int& max)
{
	string input;
	int inputInt;
	bool err;

	do
	{
		err = false;

		getline(cin, input);

		//Exception handling
		try
		{
			inputInt = stoi(input);

			//Input must be between min and max
			if (inputInt < min || inputInt > max)
			{
				cerr << UI::ERR_INVALID_OPTION_RANGE << min << " and " << max << " inclusive." << endl;
				err = true;
			}
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

	} while (err || !cin);

	return inputInt;
}

double getUserInputDouble(const double& min, const double& max)
{
	string input;
	double inputDouble;
	bool err;

	do
	{
		err = false;

		getline(cin, input);

		//Exception handling
		try
		{
			inputDouble = stod(input);

			//Input must be between min and max
			if (inputDouble < min || inputDouble > max)
			{
				cerr << UI::ERR_INVALID_OPTION_RANGE << min << " and " << max << " inclusive." << endl;
				err = true;
			}
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

	} while (err || !cin);

	return inputDouble;
}

string getUserInputString()
{
	string input;

	getline(cin, input);

	return input;
}

void clearScreen(bool displayHeader)
{
	system("CLS");
	if (displayHeader)
	{
		printHeader();
	}
	return;
}

void pause()
{
	cout << "Press ENTER to continue.";
	cin.get();
}

int convertDateToInt(string date)
{
	int month = stoi(date.substr(0, 2));
	int day = stoi(date.substr(3, 2));
	int year = stoi(date.substr(6, 4));

	return 10000 * year + 100 * month + day;
}

void displayGoodbye()
{
	clearScreen();

	cout << R"(
  _______   _                       _                                   __                            _         _   _     _                 
 |__   __| | |                     | |                                 / _|                          (_)       (_) | |   (_)                
    | |    | |__     __ _   _ __   | | __    _   _    ___    _   _    | |_    ___    _ __    __   __  _   ___   _  | |_   _   _ __     __ _ 
    | |    | '_ \   / _` | | '_ \  | |/ /   | | | |  / _ \  | | | |   |  _|  / _ \  | '__|   \ \ / / | | / __| | | | __| | | | '_ \   / _` |
    | |    | | | | | (_| | | | | | |   <    | |_| | | (_) | | |_| |   | |   | (_) | | |       \ V /  | | \__ \ | | | |_  | | | | | | | (_| |
    |_|    |_| |_|  \__,_| |_| |_| |_|\_\    \__, |  \___/   \__,_|   |_|    \___/  |_|        \_/   |_| |___/ |_|  \__| |_| |_| |_|  \__, |
                                              __/ |                                                                                    __/ |
                                             |___/                                                                                    |___/ 
   _____                                    _   _           _   _               ____                    _                   _   _                         
  / ____|                                  | | (_)         (_) | |             |  _ \                  | |                 | | | |                        
 | (___     ___   _ __    ___   _ __     __| |  _   _ __    _  | |_   _   _    | |_) |   ___     ___   | | __  ___    ___  | | | |   ___   _ __   ___     
  \___ \   / _ \ | '__|  / _ \ | '_ \   / _` | | | | '_ \  | | | __| | | | |   |  _ <   / _ \   / _ \  | |/ / / __|  / _ \ | | | |  / _ \ | '__| / __|    
  ____) | |  __/ | |    |  __/ | | | | | (_| | | | | |_) | | | | |_  | |_| |   | |_) | | (_) | | (_) | |   <  \__ \ |  __/ | | | | |  __/ | |    \__ \  _ 
 |_____/   \___| |_|     \___| |_| |_|  \__,_| |_| | .__/  |_|  \__|  \__, |   |____/   \___/   \___/  |_|\_\ |___/  \___| |_| |_|  \___| |_|    |___/ (_)
                                                   | |                 __/ |                                                                              
                                                   |_|                |___/                                                                               



   ___                      _              _     _             _ 
  / __|  _ _   ___   __ _  | |_   ___   __| |   | |__   _  _  (_)
 | (__  | '_| / -_) / _` | |  _| / -_) / _` |   | '_ \ | || |  _ 
  \___| |_|   \___| \__,_|  \__| \___| \__,_|   |_.__/  \_, | (_)
                                                        |__/     
   ___    _   _         _                  ___   _                  
  / _ \  | | (_) __ __ (_)  ___   _ _     / __| | |_    __ _   _ _  
 | (_) | | | | | \ V / | | / -_) | '_|   | (__  | ' \  / _` | | ' \ 
  \___/  |_| |_|  \_/  |_| \___| |_|      \___| |_||_| \__,_| |_||_|
  _             _           ___                                            
 | |     _  _  (_)  ___    / __|  _  _   ___   _ _   _ _   ___   _ _   ___ 
 | |__  | || | | | (_-<   | (_ | | || | / -_) | '_| | '_| / -_) | '_| / _ \
 |____|  \_,_| |_| /__/    \___|  \_,_| \___| |_|   |_|   \___| |_|   \___/
  ___                               _     ___          _           ___                                   _              
 / __|  __ _   _ __    _  _   ___  | |   | _ \  _  _  (_)  ___    / __|  ___   _ _  __ __  __ _   _ _   | |_   ___   ___
 \__ \ / _` | | '  \  | || | / -_) | |   |   / | || | | | |_ /   | (__  / -_) | '_| \ V / / _` | | ' \  |  _| / -_) (_-<
 |___/ \__,_| |_|_|_|  \_,_| \___| |_|   |_|_\  \_,_| |_| /__|    \___| \___| |_|    \_/  \__,_| |_||_|  \__| \___| /__/
  __  __                             _      ___                     _        
 |  \/  |  __ _   _ _    __ _   ___ (_)    / __|  ___  __ __ __  __| |  __ _ 
 | |\/| | / _` | | ' \  / _` | (_-< | |   | (_ | / _ \ \ V  V / / _` | / _` |
 |_|  |_| \__,_| |_||_| \__,_| /__/ |_|    \___| \___/  \_/\_/  \__,_| \__,_|)" << endl << endl << endl;
}