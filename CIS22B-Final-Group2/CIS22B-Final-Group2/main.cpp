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
#include <memory>
#include "InventoryBook.h"
#include "InventoryDatabase.h"
#include "Report.h"
#include "Cashier.h"

using namespace std;


void initialize();
void displayMainMenu();

void displayCashierModule();
void cashierSellBooks(InventoryDatabase* pD);
void addBooksToCart(InventoryDatabase *book);
void removedFromCart(Cashier *pD);

void displayInventoryModule();
void inventoryFindBookById(InventoryDatabase* inventoryDatabase);
void inventoryFindBookByIsbn(InventoryDatabase* inventoryDatabase);
void inventoryAddBookToDatabase(InventoryDatabase* inventoryDatabase);
void inventoryRemoveBookFromDatabase(InventoryDatabase* inventoryDatabase);
void inventoryEditBookByIsbn(InventoryDatabase* inventoryDatabase);

void displayReportModule();
void displayReportInventoryList(unique_ptr<InventoryBook[]> books, int numBooks);
void displayReportInventoryWholesaleValue(unique_ptr<InventoryBook[]> books, int numBooks);
void displayReportInventoryRetailValue(unique_ptr<InventoryBook[]> books, int numBooks);
void displayReportListByQuantity(unique_ptr<InventoryBook[]> books, int numBooks);
void displayReportListByCost(unique_ptr<InventoryBook[]> books, int numBooks);
void displayReportListByAge(unique_ptr<InventoryBook[]> books, int numBooks);

int getUserInputInt(const int& min = INT_MIN, const int& max = INT_MAX);
double getUserInputDouble(const double& min = DBL_MIN, const double& max = DBL_MAX);
string getUserInputString();

string generateBars(int number);
void clearScreen(bool displayHeader = false);
void pause();
void printHeader();
void displayGoodbye();

namespace UI
{
	const int TERMINAL_WIDTH = 130;
	const int TERMINAL_HEIGHT = 60;

	const string BARS_CHARACTER = "=";

	const string PROMPT_OPTION = "Choose an option: ";

	const string ERR_EXCEPTION_GENERIC = "ERROR: An exception occured.";
	const string ERR_EXCEPTION_INVALID_ARGUMENT = "ERROR: Invalid option, option is not a valid argument. Are you correctly typing a number or a string?";
	const string ERR_EXCEPTION_OUT_OF_RANGE = "ERROR: Invalid option, option is out of range.";
	const string ERR_INVALID_OPTION_RANGE = "ERROR: Invalid option, option must be between ";

	enum MAIN_MENU_OPTIONS { MAIN_NONE, MAIN_CASHIER, MAIN_INVENTORY, MAIN_REPORT, MAIN_EXIT };
	enum CASHIER_OPTIONS { CASHIER_NONE, CASHIER_SELL_BOOKS, CASHIER_BACK };
	enum SELL_OPTIONS { SELL_NONE, SELL_ADD_BOOK, SELL_REMOVE_BOOKS, SELL_CHECKOUT, SELL_CANCEL};
	enum INVENTORY_OPTIONS { INVENTORY_NONE, INVENTORY_FIND_ID, INVENTORY_FIND_ISBN, INVENTORY_ADD_BOOK, INVENTORY_REMOVE_BOOK, INVENTORY_EDIT_BOOK, INVENTORY_BACK };
	enum REPORT_OPTIONS { REPORT_NONE, REPORT_INVENTORY_LIST, REPORT_INVENTORY_WHOLESALE, REPORT_INVENTORY_RETAIL, REPORT_LIST_QUANTITY, REPORT_LIST_COST, REPORT_LIST_AGE, REPORT_BACK };
}

int main()
{
	//Resize terminal, format cout
	initialize();

	//Setup InventoryDatabase
	const string filePath = "books.txt";
	InventoryDatabase inventoryDatabase;
	inventoryDatabase.buildInventoryArray(filePath);

	//Cashier
	Cashier cashier(&inventoryDatabase);

	//Display main menu, get user inputs
	int inputMainMenu;

	do
	{
		displayMainMenu();

		inputMainMenu = getUserInputInt(UI::MAIN_MENU_OPTIONS::MAIN_CASHIER, UI::MAIN_MENU_OPTIONS::MAIN_EXIT);

		switch (inputMainMenu)
		{
			int inputSubMenu, inputMenuSub2;

		case UI::MAIN_MENU_OPTIONS::MAIN_CASHIER:
			do
			{
				displayCashierModule();

				inputSubMenu = getUserInputInt(UI::CASHIER_OPTIONS::CASHIER_SELL_BOOKS, UI::CASHIER_OPTIONS::CASHIER_BACK);

				switch (inputSubMenu)
				{
				case UI::CASHIER_OPTIONS::CASHIER_SELL_BOOKS:

					cashierSellBooks(&inventoryDatabase);

					inputMenuSub2 = getUserInputInt(UI::SELL_OPTIONS::SELL_ADD_BOOK, UI::SELL_OPTIONS::SELL_CANCEL);

					switch (inputMenuSub2)
					{
					case UI::SELL_OPTIONS::SELL_ADD_BOOK:
						addBooksToCart(&inventoryDatabase);
						break;
					case UI::SELL_OPTIONS::SELL_REMOVE_BOOKS:
						removedFromCart(&cashier);
						break;
					case UI::SELL_OPTIONS::SELL_CHECKOUT:
						break;
					case UI::SELL_OPTIONS::SELL_CANCEL:
						break;
					default:
						break;
					}
					break;
				case UI::CASHIER_OPTIONS::CASHIER_BACK:
					break;
				default:
					break;
				}
			} while (inputSubMenu != UI::CASHIER_OPTIONS::CASHIER_BACK);
			break;
		case UI::MAIN_MENU_OPTIONS::MAIN_INVENTORY:
			do
			{
				displayInventoryModule();

				inputSubMenu = getUserInputInt(UI::INVENTORY_OPTIONS::INVENTORY_FIND_ID, UI::INVENTORY_OPTIONS::INVENTORY_BACK);

				switch (inputSubMenu)
				{
				case UI::INVENTORY_OPTIONS::INVENTORY_FIND_ID:
					inventoryFindBookById(&inventoryDatabase);
					break;
				case UI::INVENTORY_OPTIONS::INVENTORY_FIND_ISBN:
					inventoryFindBookByIsbn(&inventoryDatabase);
					break;
				case UI::INVENTORY_OPTIONS::INVENTORY_ADD_BOOK:
					inventoryAddBookToDatabase(&inventoryDatabase);
					break;
				case UI::INVENTORY_OPTIONS::INVENTORY_REMOVE_BOOK:
					inventoryRemoveBookFromDatabase(&inventoryDatabase);
					break;
				case UI::INVENTORY_OPTIONS::INVENTORY_EDIT_BOOK:
					inventoryEditBookByIsbn(&inventoryDatabase);
					break;
				case UI::INVENTORY_OPTIONS::INVENTORY_BACK:
					break;
				default:
					break;
				}
			} while (inputSubMenu != UI::INVENTORY_OPTIONS::INVENTORY_BACK);
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

	cout << "Press ENTER to exit.";
	cin.get();
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

	cout << setw(optionMargin + purchaseText.length()) << purchaseText << endl << endl
		<< setw(optionMargin + backText.length()) << backText << endl << endl
		<< bars << endl << endl;

	return;
}

void cashierSellBooks(InventoryDatabase* pD)
{
	Cashier cashier(pD);
	//bool stop = false;

	//while (!stop)
	//{
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
	//}

	return;
}

void addBooksToCart(InventoryDatabase *book) {

	clearScreen(true);

	Cashier cashier(book);
	string userIsbn = string();
	int again;
	unique_ptr<InventoryBook[]> books = book->getInventoryArray();
	int numBooks = book->getInventoryArraySize();

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string addBooksText = "[ ADD BOOKS TO CART ]";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + addBooksText.length()) / 2;
	const size_t optionMargin = titleMargin - addBooksText.length();

	cout << setw(titleMargin) << addBooksText << endl << endl << endl << bars << endl << endl;

	do
	{
		cout << endl;
		cout << "Please, enter the ISBN of the book you want to add to the cart: ";
		userIsbn = getUserInputString();
		cout << endl;

		while (userIsbn.length() != 13) {

			cout << "ERROR: enter the 13 digits of the book's ISBN:";
			userIsbn = getUserInputString();
			cout << endl;

		}

		InventoryBook addBook;
		addBook = book->getBookByIsbn(userIsbn);

		for (int i = 0; i < numBooks; i++) {
			if (userIsbn == books[i].isbn) {
				cashier.addBookToCart(addBook.isbn);
				cout << "Book added to your cart." << endl << endl;
				break; 
			}
			else if(i = numBooks - 1) {
				cout << "ERROR: ISBN does not exist." << endl; 
				userIsbn = string();
			}
		}
		cout << "Would you like to add another book? [ 1 ] YES  [ 2 ] NO : ";
		again = getUserInputInt();
		while (again != 1 && again != 2) {
			cout << endl;
			cout << "ERROR: enter 1 or 2 : ";
			again = getUserInputInt();
		}

	} while (again == 1);

	return;
}


void removedFromCart(Cashier *pD) {

	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string removeText = "[ REMOVED BOOKS FROM CART ]";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + removeText.length()) / 2;
	const size_t optionMargin = titleMargin - removeText.length();

	cout << setw(titleMargin) << removeText << endl << endl << endl << bars << endl << endl;

	string userIsbn;
	int another;

	do
	{
		cout << endl;
		cout << "Please enter the book ISBN that you want to remove: ";
		userIsbn = getUserInputString();
			while (userIsbn.length() != 13)
			{
				cout << endl;
				cout << "ERROR: ERROR: enter the 13 digits of the book's ISBN: ";
				userIsbn = getUserInputString();
			}
			
			int checkBook;
			InventoryBook removeBook;
			checkBook = pD->findBook(userIsbn);
			if (checkBook == -1) {
				cout << endl;
				cout << "ERROR: Book was not found on the cart.";
			}
			else
				//pD->getCart();

		cout << "Would you like to remove another book? [ 1 ] YES  [ 2 ] NO : ";
		another = getUserInputInt();
		while (another != 1 && another != 2) {
			cout << endl;
			cout << "ERROR: enter 1 or 2 : ";
			another = getUserInputInt();
		}
	} while (another == 1);

	return;
}

void checkoutBook(InventoryDatabase *pD) 
{
	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string checkoutText = "[ CHECKOUT ]";
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

	const size_t titleMargin = (UI::TERMINAL_WIDTH + checkoutText.length()) / 2;
	const size_t optionMargin = titleMargin - checkoutText.length();

	const size_t titleColumnLength = UI::TERMINAL_WIDTH - isbnColumnLength - quantityColumnLength - wholesaleColumnLength - totalWholesaleColumnLength;

	cout << right;

	cout << setw(titleMargin) << checkoutText << endl << endl << bars << endl << endl;

	cout << left;

	cout << setw(isbnColumnLength) << bookIsbnText
		<< setw(titleColumnLength) << bookTitleText
		<< setw(quantityColumnLength) << bookQuantityText
		<< setw(wholesaleColumnLength) << bookWholesaleText
		<< setw(totalWholesaleColumnLength) << bookTotalWholesaleText
		<< endl << endl;

	Cashier cashier(pD);



	cout << endl;
	std::unique_ptr<InventoryBook[]> copyCartArray = cashier.getCart();
	int cartSize = 0;
	//std::unique_ptr<InventoryBook[]> copyCartArray = std::make_unique<InventoryBook[]>(cartSize);


	cout << "";

	return;
}
/***************************************************************************
*********** INVENTORY MODULE
****************************************************************************/

void displayInventoryModule()
{
	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string inventoryModeText = "[ INVENTORY MODE ]";
	const string findBookByIdText = "[ 1 ] FIND BOOK BY ID";
	const string findBookByIsbnText = "[ 2 ] FIND BOOK BY ISBN";
	const string addBookText = "[ 3 ] ADD BOOK TO DATABASE";
	const string removeBookText = "[ 4 ] REMOVE BOOK FROM DATABASE";
	const string editBookText = "[ 5 ] EDIT BOOK IN DATABASE";
	const string backText = "[ 6 ] BACK";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + inventoryModeText.length()) / 2;
	const size_t optionMargin = titleMargin - inventoryModeText.length();

	cout << setw(titleMargin) << inventoryModeText << endl << endl << bars << endl << endl;

	cout << setw(optionMargin + findBookByIdText.length()) << findBookByIdText << endl << endl
		<< setw(optionMargin + findBookByIsbnText.length()) << findBookByIsbnText << endl << endl
		<< setw(optionMargin + addBookText.length()) << addBookText << endl << endl
		<< setw(optionMargin + removeBookText.length()) << removeBookText << endl << endl
		<< setw(optionMargin + editBookText.length()) << editBookText << endl << endl
		<< setw(optionMargin + backText.length()) << backText << endl << endl
		<< bars << endl << endl;

	return;
}

void inventoryFindBookById(InventoryDatabase* inventoryDatabase)
{
	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string titleText = "[ FIND BOOK BY ID ]";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + titleText.length()) / 2;
	cout << setw(titleMargin) << titleText << endl << endl << bars << endl << endl;

	unique_ptr<InventoryBook[]> books = inventoryDatabase->getInventoryArray();
	int numBooks = inventoryDatabase->getInventoryArraySize();

	if (numBooks == 0)
	{
		cout << "ERROR: Database is empty." << endl;
		pause();
		return;
	}

	cout << "Enter ID to look up: ";
	int id = getUserInputInt();

	if (id < 0 || id >= numBooks)
	{
		cout << "ERROR: ID does not exist in database." << endl;
		cout << endl << bars << endl << endl;
		pause();
		return;
	}

	const string bookIndexText = "ID:";
	const string bookIsbnText = "ISBN:";
	const string bookTitleText = "TITLE:";
	const string bookAuthorText = "AUTHOR:";
	const string bookPublisherText = "PUBLISHER:";
	const string bookDateText = "DATE ADDED:";
	const string bookQuantityText = "ON-HAND:";
	const string bookWholesaleText = "WHOLESALE:";
	const string bookRetailText = "RETAIL:";

	const size_t columnSpacing = 3;

	const size_t idColumnLength = 3 + columnSpacing;
	const size_t isbnColumnLength = 13 + columnSpacing;
	const size_t dateColumnLength = 10 + columnSpacing;
	const size_t quantityColumnLength = bookQuantityText.length() + columnSpacing;
	const size_t wholesaleColumnLength = bookWholesaleText.length() + columnSpacing;
	const size_t retailColumnLength = bookRetailText.length() + columnSpacing;

	const size_t titleColumnLength = (UI::TERMINAL_WIDTH - idColumnLength - isbnColumnLength - dateColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 2;
	const size_t authorColumnLength = (UI::TERMINAL_WIDTH - idColumnLength - isbnColumnLength - dateColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 4;
	const size_t publisherColumnLength = (UI::TERMINAL_WIDTH - idColumnLength - isbnColumnLength - dateColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 4;

	cout << left;

	cout << endl << bars << endl << endl;

	cout << setw(idColumnLength) << bookIndexText
		<< setw(isbnColumnLength) << bookIsbnText
		<< setw(titleColumnLength) << bookTitleText
		<< setw(authorColumnLength) << bookAuthorText
		<< setw(publisherColumnLength) << bookPublisherText
		<< setw(dateColumnLength) << bookDateText
		<< setw(quantityColumnLength) << bookQuantityText
		<< setw(wholesaleColumnLength) << bookWholesaleText
		<< setw(retailColumnLength) << bookRetailText
		<< endl << endl;

	cout << setw(idColumnLength) << id
		<< setw(isbnColumnLength) << books[id].isbn
		<< setw(titleColumnLength) << books[id].title
		<< setw(authorColumnLength) << books[id].author
		<< setw(publisherColumnLength) << books[id].publisher
		<< setw(dateColumnLength) << books[id].addDate
		<< setw(quantityColumnLength) << books[id].quantity
		<< setw(wholesaleColumnLength) << books[id].wholesale
		<< setw(retailColumnLength) << books[id].retail
		<< endl;

	cout << endl << bars << endl << endl;

	pause();

	return;
}

void inventoryFindBookByIsbn(InventoryDatabase* inventoryDatabase)
{
	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string titleText = "[ FIND BOOK BY ISBN ]";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + titleText.length()) / 2;
	cout << setw(titleMargin) << titleText << endl << endl << bars << endl << endl;

	unique_ptr<InventoryBook[]> books = inventoryDatabase->getInventoryArray();
	int numBooks = inventoryDatabase->getInventoryArraySize();

	if (numBooks == 0)
	{
		cout << "ERROR: Database is empty." << endl;
		cout << endl << bars << endl << endl;
		pause();
		return;
	}

	cout << "Enter ISBN to look up: ";
	string isbn = getUserInputString();
	int foundBookIndex;
	bool bookExists = false;

	for (int i = 0; i < numBooks; i++)
	{
		if (isbn == books[i].isbn)
		{
			foundBookIndex = i;
			bookExists = true;
		}
	}

	if (!bookExists)
	{
		cout << "ERROR: Book ISBN does not exist in database." << endl;
		cout << endl << bars << endl << endl;
		pause();
		return;
	}

	const string bookIndexText = "ID:";
	const string bookIsbnText = "ISBN:";
	const string bookTitleText = "TITLE:";
	const string bookAuthorText = "AUTHOR:";
	const string bookPublisherText = "PUBLISHER:";
	const string bookDateText = "DATE ADDED:";
	const string bookQuantityText = "ON-HAND:";
	const string bookWholesaleText = "WHOLESALE:";
	const string bookRetailText = "RETAIL:";

	const size_t columnSpacing = 3;

	const size_t idColumnLength = 3 + columnSpacing;
	const size_t isbnColumnLength = 13 + columnSpacing;
	const size_t dateColumnLength = 10 + columnSpacing;
	const size_t quantityColumnLength = bookQuantityText.length() + columnSpacing;
	const size_t wholesaleColumnLength = bookWholesaleText.length() + columnSpacing;
	const size_t retailColumnLength = bookRetailText.length() + columnSpacing;

	const size_t titleColumnLength = (UI::TERMINAL_WIDTH - idColumnLength - isbnColumnLength - dateColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 2;
	const size_t authorColumnLength = (UI::TERMINAL_WIDTH - idColumnLength - isbnColumnLength - dateColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 4;
	const size_t publisherColumnLength = (UI::TERMINAL_WIDTH - idColumnLength - isbnColumnLength - dateColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 4;

	cout << left;

	cout << endl << bars << endl << endl;

	cout << setw(idColumnLength) << bookIndexText
		<< setw(isbnColumnLength) << bookIsbnText
		<< setw(titleColumnLength) << bookTitleText
		<< setw(authorColumnLength) << bookAuthorText
		<< setw(publisherColumnLength) << bookPublisherText
		<< setw(dateColumnLength) << bookDateText
		<< setw(quantityColumnLength) << bookQuantityText
		<< setw(wholesaleColumnLength) << bookWholesaleText
		<< setw(retailColumnLength) << bookRetailText
		<< endl << endl;

	cout << setw(idColumnLength) << foundBookIndex
		<< setw(isbnColumnLength) << books[foundBookIndex].isbn
		<< setw(titleColumnLength) << books[foundBookIndex].title
		<< setw(authorColumnLength) << books[foundBookIndex].author
		<< setw(publisherColumnLength) << books[foundBookIndex].publisher
		<< setw(dateColumnLength) << books[foundBookIndex].addDate
		<< setw(quantityColumnLength) << books[foundBookIndex].quantity
		<< setw(wholesaleColumnLength) << books[foundBookIndex].wholesale
		<< setw(retailColumnLength) << books[foundBookIndex].retail
		<< endl;

	cout << endl << bars << endl << endl;

	pause();

	return;
}

void inventoryAddBookToDatabase(InventoryDatabase* inventoryDatabase)
{
	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string titleText = "[ ADD BOOK TO DATABASE ]";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + titleText.length()) / 2;
	cout << setw(titleMargin) << titleText << endl << endl << bars << endl << endl;

	string isbn = string();
	string title;
	string author;
	string publisher;
	string addDate = string();
	int quantity;
	double wholesale;
	double retail;

	unique_ptr<InventoryBook[]> books = inventoryDatabase->getInventoryArray();
	int numBooks = inventoryDatabase->getInventoryArraySize();

	cout << "Creating new book." << endl;

	while (isbn == string())
	{
		cout << "Enter book ISBN: ";
		isbn = getUserInputString();

		if (isbn.length() != 13)
		{
			cout << "ERROR: ISBN must be 13 digits." << endl;
			isbn = string();
		}
		else
		{
			try
			{
				double temp = stod(isbn);
			}
			catch (...)
			{
				cout << "ERROR: ISBN must be a number." << endl;
				isbn = string();
			}
			for (int i = 0; i < numBooks; i++)
			{
				if (isbn == books[i].isbn)
				{
					cout << "ERROR: ISBN already exists in database." << endl;
					isbn = string();
				}
			}
		}
	}

	cout << "Enter book title: ";
	title = getUserInputString();

	cout << "Enter book author: ";
	author = getUserInputString();

	cout << "Enter book publisher: ";
	publisher = getUserInputString();

	while (addDate == string())
	{
		cout << "Enter book add date: ";
		addDate = getUserInputString();
		int month, day, year;
		bool error = false;

		if (addDate.length() != 10)
		{
			error = true;
		}
		else
		{
			if (addDate.substr(2, 1) != "/" || addDate.substr(5, 1) != "/")
			{
				error = true;
			}
			else
			{
				try
				{
					month = stoi(addDate.substr(0, 2));
					day = stoi(addDate.substr(3, 2));
					year = stoi(addDate.substr(6, 4));
				}
				catch (...)
				{
					error = true;
				}
			}
			if (month < 1 || month > 12 || day < 1 || day > 31 || year < 0 || year > 9999)
			{
				error = true;
			}
		}
		if (error)
		{
			cout << "ERROR: Date must be of form \"MM/DD/YYYY\"" << endl;
			addDate = string();
		}
	}

	cout << "Enter book quantity: ";
	quantity = getUserInputInt(0);

	cout << "Enter book wholesale price: ";
	wholesale = getUserInputDouble(0);

	cout << "Enter book retail price: ";
	retail = getUserInputDouble(0);

	InventoryBook newBook = InventoryBook(isbn, title, author, publisher, addDate, quantity, wholesale, retail);
	inventoryDatabase->addBookToArray(newBook);

	cout << "Successfully added book to database." << endl;
	cout << endl << bars << endl << endl;
	pause();

	return;
}

void inventoryRemoveBookFromDatabase(InventoryDatabase* inventoryDatabase)
{
	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string titleText = "[ REMOVE BOOK FROM DATABASE ]";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + titleText.length()) / 2;
	cout << setw(titleMargin) << titleText << endl << endl << bars << endl << endl;

	unique_ptr<InventoryBook[]> books = inventoryDatabase->getInventoryArray();
	int numBooks = inventoryDatabase->getInventoryArraySize();

	if (numBooks == 0)
	{
		cout << "ERROR: Database is empty." << endl;
		cout << endl << bars << endl << endl;
		pause();
		return;
	}

	cout << "Enter book ISBN: ";
	string isbn = getUserInputString();
	bool bookExists = false;

	for (int i = 0; i < numBooks; i++)
	{
		if (isbn == books[i].isbn)
		{
			inventoryDatabase->removeBookFromArray(i);
			bookExists = true;
		}
	}

	if (bookExists)
	{
		cout << "Successfully removed book from database." << endl;
	}
	else
	{
		cout << "ERROR: Book does not exist in database." << endl;
	}

	cout << endl << bars << endl << endl;
	pause();

	return;
}

void inventoryEditBookByIsbn(InventoryDatabase* inventoryDatabase)
{
	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string titleText = "[ EDIT BOOK BY ISBN ]";

	const size_t titleMargin = (UI::TERMINAL_WIDTH + titleText.length()) / 2;
	cout << setw(titleMargin) << titleText << endl << endl << bars << endl << endl;

	unique_ptr<InventoryBook[]> books = inventoryDatabase->getInventoryArray();
	int numBooks = inventoryDatabase->getInventoryArraySize();

	if (numBooks == 0)
	{
		cout << "ERROR: Database is empty." << endl << endl;
		cout << endl << bars << endl << endl;
		pause();
		return;
	}

	cout << "Enter book ISBN: ";
	string isbn = getUserInputString();
	bool bookExists = false;
	int foundIndex;
	InventoryBook foundBook;

	for (int i = 0; i < numBooks; i++)
	{
		if (isbn == books[i].isbn)
		{
			bookExists = true;
			foundIndex = i;
			foundBook = books[i];
		}
	}

	if (!bookExists)
	{
		cout << "ERROR: Book does not exist in database." << endl;
		cout << endl << bars << endl << endl;
		pause();
		return;
	}

	const string bookIsbnText = "[1] ISBN:";
	const string bookTitleText = "[2] TITLE:";
	const string bookAuthorText = "[3] AUTHOR:";
	const string bookPublisherText = "[4] PUBLISHER:";
	const string bookDateText = "[5] DATE ADDED:";
	const string bookQuantityText = "[6] ON-HAND:";
	const string bookWholesaleText = "[7] WHOLESALE:";
	const string bookRetailText = "[8] RETAIL:";

	const size_t columnSpacing = 3;

	const size_t isbnColumnLength = 13 + columnSpacing;
	const size_t dateColumnLength = bookDateText.length() + columnSpacing;
	const size_t quantityColumnLength = bookQuantityText.length() + columnSpacing;
	const size_t wholesaleColumnLength = bookWholesaleText.length() + columnSpacing;
	const size_t retailColumnLength = bookRetailText.length() + columnSpacing;

	const size_t titleColumnLength = (UI::TERMINAL_WIDTH - isbnColumnLength - dateColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 2;
	const size_t authorColumnLength = (UI::TERMINAL_WIDTH - isbnColumnLength - dateColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 4;
	const size_t publisherColumnLength = (UI::TERMINAL_WIDTH - isbnColumnLength - dateColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 4;

	cout << left;

	cout << endl << bars << endl << endl;

	cout << setw(isbnColumnLength) << bookIsbnText
		<< setw(titleColumnLength) << bookTitleText
		<< setw(authorColumnLength) << bookAuthorText
		<< setw(publisherColumnLength) << bookPublisherText
		<< setw(dateColumnLength) << bookDateText
		<< setw(quantityColumnLength) << bookQuantityText
		<< setw(wholesaleColumnLength) << bookWholesaleText
		<< setw(retailColumnLength) << bookRetailText
		<< endl;

	cout << setw(isbnColumnLength) << books[foundIndex].isbn
		<< setw(titleColumnLength) << books[foundIndex].title
		<< setw(authorColumnLength) << books[foundIndex].author
		<< setw(publisherColumnLength) << books[foundIndex].publisher
		<< setw(dateColumnLength) << books[foundIndex].addDate
		<< setw(quantityColumnLength) << books[foundIndex].quantity
		<< setw(wholesaleColumnLength) << books[foundIndex].wholesale
		<< setw(retailColumnLength) << books[foundIndex].retail
		<< endl << endl << bars << endl << endl;

	enum BOOK_ATTRIBUTES { NONE, BOOK_ISBN, BOOK_TITLE, BOOK_AUTHOR, BOOK_PUBLISHER, BOOK_DATE, BOOK_QUANTITY, BOOK_WHOLESALE, BOOK_RETAIL };

	cout << "Enter book attribute to edit (1-8): ";
	int edit = getUserInputInt(BOOK_ISBN, BOOK_RETAIL);
	string newString = string();
	int newInt;
	double newDouble;

	switch (edit)
	{
	case BOOK_ISBN:
		cout << "Editing book ISBN." << endl;
		while (newString == string())
		{
			cout << "Enter new book ISBN: ";
			newString = getUserInputString();

			if (newString.length() != 13)
			{
				cout << "ERROR: ISBN must be 13 digits." << endl;
				newString = string();
			}
			else
			{
				try
				{
					double temp = stod(newString);
				}
				catch (...)
				{
					cout << "ERROR: ISBN must be a number." << endl;
					newString = string();
				}
				for (int i = 0; i < numBooks; i++)
				{
					if (newString == books[i].isbn)
					{
						cout << "ERROR: ISBN already exists in database." << endl;
						newString = string();
					}
				}
			}
		}
		inventoryDatabase->setBookIsbnByIsbn(foundBook.isbn, newString);
		cout << "Book ISBN successfully edited." << endl;
		cout << endl << bars << endl << endl;
		pause();
		break;
	case BOOK_TITLE:
		cout << "Editing book title." << endl;
		cout << "Enter new book title: ";
		newString = getUserInputString();
		inventoryDatabase->setBookTitleByIsbn(foundBook.isbn, newString);
		cout << "Book title successfully edited." << endl;
		cout << endl << bars << endl << endl;
		pause();
		break;
	case BOOK_AUTHOR:
		cout << "Editing book author." << endl;
		cout << "Enter new book author: ";
		newString = getUserInputString();
		inventoryDatabase->setBookAuthorByIsbn(foundBook.isbn, newString);
		cout << "Book author successfully edited." << endl;
		cout << endl << bars << endl << endl;
		pause();
		break;
	case BOOK_PUBLISHER:
		cout << "Editing book publisher." << endl;
		cout << "Enter new book publisher: ";
		newString = getUserInputString();
		inventoryDatabase->setBookPublisherByIsbn(foundBook.isbn, newString);
		cout << "Book publisher successfully edited." << endl;
		cout << endl << bars << endl << endl;
		pause();
		break;
	case BOOK_DATE:
		cout << "Editing book add date." << endl;
		while (newString == string())
		{
			cout << "Enter new book add date: ";
			newString = getUserInputString();
			int month, day, year;
			bool error = false;

			if (newString.length() != 10)
			{
				error = true;
			}
			else
			{
				if (newString.substr(2, 1) != "/" || newString.substr(5, 1) != "/")
				{
					error = true;
				}
				else
				{
					try
					{
						month = stoi(newString.substr(0, 2));
						day = stoi(newString.substr(3, 2));
						year = stoi(newString.substr(6, 4));
					}
					catch (...)
					{
						error = true;
					}
				}
				if (month < 1 || month > 12 || day < 1 || day > 31 || year < 0 || year > 9999)
				{
					error = true;
				}
			}
			if (error)
			{
				cout << "ERROR: Date must be of form \"MM/DD/YYYY\"" << endl;
				newString = string();
			}
		}
		inventoryDatabase->setBookAddDateByIsbn(foundBook.isbn, newString);
		cout << "Book add date successfully edited." << endl;
		cout << endl << bars << endl << endl;
		pause();
		break;
	case BOOK_QUANTITY:
		cout << "Editing book quantity." << endl;
		cout << "Enter new book quantity: ";
		newInt = getUserInputInt(0);
		inventoryDatabase->setBookQuantityByIsbn(foundBook.isbn, newInt);
		cout << "Book quantity successfully edited." << endl;
		cout << endl << bars << endl << endl;
		pause();
		break;
	case BOOK_WHOLESALE:
		cout << "Editing book wholesale price." << endl;
		cout << "Enter new book wholesale price: ";
		newDouble = getUserInputDouble(0);
		inventoryDatabase->setBookWholesaleByIsbn(foundBook.isbn, newDouble);
		cout << "Book wholesale price successfully edited." << endl;
		cout << endl << bars << endl << endl;
		pause();
		break;
	case BOOK_RETAIL:
		cout << "Editing book retail price." << endl;
		cout << "Enter new book retail price: ";
		newDouble = getUserInputDouble(0);
		inventoryDatabase->setBookRetailByIsbn(foundBook.isbn, newDouble);
		cout << "Book retail price successfully edited." << endl;
		cout << endl << bars << endl << endl;
		pause();
		break;
	default:
		break;
	}

	return;
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

void displayReportInventoryList(unique_ptr<InventoryBook[]> books, int numBooks) {

	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string titleText = "[ INVENTORY LIST ]";
	const string bookIndexText = "ID:";
	const string bookIsbnText = "ISBN:";
	const string bookTitleText = "TITLE:";
	const string bookAuthorText = "AUTHOR:";
	const string bookPublisherText = "PUBLISHER:";
	const string bookDateText = "DATE ADDED:";
	const string bookQuantityText = "ON-HAND:";
	const string bookWholesaleText = "WHOLESALE:";
	const string bookRetailText = "RETAIL:";

	const size_t columnSpacing = 3;

	const size_t idColumnLength = 3 + columnSpacing;
	const size_t isbnColumnLength = 13 + columnSpacing;
	const size_t dateColumnLength = 10 + columnSpacing;
	const size_t quantityColumnLength = bookQuantityText.length() + columnSpacing;
	const size_t wholesaleColumnLength = bookWholesaleText.length() + columnSpacing;
	const size_t retailColumnLength = bookRetailText.length() + columnSpacing;

	const size_t titleColumnLength = (UI::TERMINAL_WIDTH - idColumnLength - isbnColumnLength - dateColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 2;
	const size_t authorColumnLength = (UI::TERMINAL_WIDTH - idColumnLength - isbnColumnLength - dateColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 4;
	const size_t publisherColumnLength = (UI::TERMINAL_WIDTH - idColumnLength - isbnColumnLength - dateColumnLength - quantityColumnLength - wholesaleColumnLength - retailColumnLength) / 4;

	const size_t titleMargin = (UI::TERMINAL_WIDTH + titleText.length()) / 2;

	cout << right;

	cout << setw(titleMargin) << titleText << endl << endl << bars << endl << endl;

	cout << left;

	cout << setw(idColumnLength) << bookIndexText
		<< setw(isbnColumnLength) << bookIsbnText
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

		cout << setw(idColumnLength) << i
			<< setw(isbnColumnLength) << books[i].isbn
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

void displayReportInventoryWholesaleValue(unique_ptr<InventoryBook[]> books, int numBooks) {

	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string titleText = "[ INVENTORY WHOLESALE VALUE ]";
	const string bookIndexText = "ID:";
	const string bookIsbnText = "ISBN:";
	const string bookTitleText = "TITLE:";
	const string bookQuantityText = "ON-HAND:";
	const string bookWholesaleText = "INDIVIDUAL WHOLESALE:";
	const string bookTotalWholesaleText = "COMBINED WHOLESALE:";
	const string inventoryTotalWholesaleText = "INVENTORY TOTAL WHOLESALE VALUE: $";

	const size_t columnSpacing = 3;

	const size_t idColumnLength = 3 + columnSpacing;
	const size_t isbnColumnLength = 13 + columnSpacing;
	const size_t quantityColumnLength = bookQuantityText.length() + columnSpacing;
	const size_t wholesaleColumnLength = bookWholesaleText.length() + columnSpacing;
	const size_t totalWholesaleColumnLength = bookTotalWholesaleText.length() + columnSpacing;

	const size_t titleColumnLength = UI::TERMINAL_WIDTH - idColumnLength - isbnColumnLength - quantityColumnLength - wholesaleColumnLength - totalWholesaleColumnLength;

	const size_t titleMargin = (UI::TERMINAL_WIDTH + titleText.length()) / 2;

	cout << right;

	cout << setw(titleMargin) << titleText << endl << endl << bars << endl << endl;

	cout << left;

	cout << setw(idColumnLength) << bookIndexText
		<< setw(isbnColumnLength) << bookIsbnText
		<< setw(titleColumnLength) << bookTitleText
		<< setw(quantityColumnLength) << bookQuantityText
		<< setw(wholesaleColumnLength) << bookWholesaleText
		<< setw(totalWholesaleColumnLength) << bookTotalWholesaleText
		<< endl << endl;

	Report report = Report();
	double inventoryTotalWholesale = report.getInventoryTotalWholesale(books.get(), numBooks);

	for (int i = 0; i < numBooks; i++)
	{
		double bookTotalWholesale = report.getBookTotalWholesale(books.get()[i]);;

		cout << left;

		cout << setw(idColumnLength) << i
			<< setw(isbnColumnLength) << books[i].isbn
			<< setw(titleColumnLength) << books[i].title
			<< setw(quantityColumnLength) << books[i].quantity
			<< setw(wholesaleColumnLength) << books[i].wholesale
			<< setw(totalWholesaleColumnLength) << bookTotalWholesale
			<< endl;
	}

	cout << right;

	cout << endl << bars << endl << endl << setw((UI::TERMINAL_WIDTH + inventoryTotalWholesaleText.length()) / 2) << inventoryTotalWholesaleText << inventoryTotalWholesale << endl << endl << bars << endl << endl;

	return;
}

void displayReportInventoryRetailValue(unique_ptr<InventoryBook[]> books, int numBooks) {

	clearScreen(true);

	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string titleText = "[ INVENTORY RETAIL VALUE ]";
	const string bookIndexText = "ID:";
	const string bookIsbnText = "ISBN:";
	const string bookTitleText = "TITLE:";
	const string bookQuantityText = "ON-HAND:";
	const string bookRetailText = "INDIVIDUAL RETAIL:";
	const string bookTotalRetailText = "COMBINED RETAIL:";
	const string inventoryTotalRetailText = "INVENTORY TOTAL RETAIL VALUE: $";

	const size_t columnSpacing = 3;

	const size_t idColumnLength = 3 + columnSpacing;
	const size_t isbnColumnLength = 13 + columnSpacing;
	const size_t quantityColumnLength = bookQuantityText.length() + columnSpacing;
	const size_t retailColumnLength = bookRetailText.length() + columnSpacing;
	const size_t totalRetailColumnLength = bookTotalRetailText.length() + columnSpacing;

	const size_t titleColumnLength = UI::TERMINAL_WIDTH - idColumnLength - isbnColumnLength - quantityColumnLength - retailColumnLength - totalRetailColumnLength;

	const size_t titleMargin = (UI::TERMINAL_WIDTH + titleText.length()) / 2;

	cout << right;

	cout << setw(titleMargin) << titleText << endl << endl << bars << endl << endl;

	cout << left;

	cout << setw(idColumnLength) << bookIndexText
		<< setw(isbnColumnLength) << bookIsbnText
		<< setw(titleColumnLength) << bookTitleText
		<< setw(quantityColumnLength) << bookQuantityText
		<< setw(retailColumnLength) << bookRetailText
		<< setw(totalRetailColumnLength) << bookTotalRetailText
		<< endl << endl;

	Report report = Report();
	double inventoryTotalRetail = report.getInventoryTotalRetail(books.get(), numBooks);

	for (int i = 0; i < numBooks; i++)
	{
		double bookTotalRetail = report.getBookTotalRetail(books.get()[i]);;

		cout << left;

		cout << setw(idColumnLength) << i
			<< setw(isbnColumnLength) << books[i].isbn
			<< setw(titleColumnLength) << books[i].title
			<< setw(quantityColumnLength) << books[i].quantity
			<< setw(retailColumnLength) << books[i].retail
			<< setw(totalRetailColumnLength) << bookTotalRetail
			<< endl;
	}

	cout << right;

	cout << endl << bars << endl << endl << setw((UI::TERMINAL_WIDTH + inventoryTotalRetailText.length()) / 2) << inventoryTotalRetailText << inventoryTotalRetail << endl << endl << bars << endl << endl;

	return;
}

void displayReportListByQuantity(unique_ptr<InventoryBook[]> books, int numBooks) {

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

	unique_ptr<InventoryBook[]> copyBooks = make_unique<InventoryBook[]>(numBooks);

	for (int i = 0; i < numBooks; i++)
	{
		copyBooks[i].isbn = books[i].isbn;
		copyBooks[i].title = books[i].title;
		copyBooks[i].quantity = books[i].quantity;
	}

	Report report = Report();
	report.selectionSortQuantity(copyBooks.get(), numBooks);

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

void displayReportListByCost(unique_ptr<InventoryBook[]> books, int numBooks) {

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

	unique_ptr<InventoryBook[]> copyBooks = make_unique<InventoryBook[]>(numBooks);

	for (int i = 0; i < numBooks; i++)
	{
		copyBooks[i].isbn = books[i].isbn;
		copyBooks[i].title = books[i].title;
		copyBooks[i].wholesale = books[i].wholesale;
	}

	Report report = Report();
	report.selectionSortCost(copyBooks.get(), numBooks);

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

void displayReportListByAge(unique_ptr<InventoryBook[]> books, int numBooks) {

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

	unique_ptr<InventoryBook[]> copyBooks = make_unique<InventoryBook[]>(numBooks);

	for (int i = 0; i < numBooks; i++)
	{
		copyBooks[i].isbn = books[i].isbn;
		copyBooks[i].title = books[i].title;
		copyBooks[i].addDate = books[i].addDate;
	}

	Report report = Report();
	report.selectionSortAge(copyBooks.get(), numBooks);

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

/***************************************************************************
*********** HELPER FUNCTIONS
****************************************************************************/

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

void initialize()
{
	//Resize the terminal window
	string systemResizeStr = "mode " + to_string(UI::TERMINAL_WIDTH) + ", " + to_string(UI::TERMINAL_HEIGHT);
	system(systemResizeStr.c_str());

	//Rename the window
	system("title Serendipity Booksellers by Olivier Chan, Luis Guerrero, Samuel Ruiz Cervantes, and Manasi Gowda");

	//Format cout
	cout << fixed << setprecision(2);
}

/***************************************************************************
*********** DISPLAY ART
****************************************************************************/

void printHeader()
{
	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string header1 = R"(   _____                         _ _       _ _           ____              _             _ _               )";
	const string header2 = R"(  / ____|                       | (_)     (_) |         |  _ \            | |           | | |              )";
	const string header3 = R"( | (___   ___ _ __ ___ _ __   __| |_ _ __  _| |_ _   _  | |_) | ___   ___ | | _____  ___| | | ___ _ __ ___ )";
	const string header4 = R"(  \___ \ / _ \ '__/ _ \ '_ \ / _` | | '_ \| | __| | | | |  _ < / _ \ / _ \| |/ / __|/ _ \ | |/ _ \ '__/ __|)";
	const string header5 = R"(  ____) |  __/ | |  __/ | | | (_| | | |_) | | |_| |_| | | |_) | (_) | (_) |   <\__ \  __/ | |  __/ |  \__ \)";
	const string header6 = R"( |_____/ \___|_|  \___|_| |_|\__,_|_| .__/|_|\__|\__, | |____/ \___/ \___/|_|\_\___/\___|_|_|\___|_|  |___/)";
	const string header7 = R"(                                    | |           __/ |                                                    )";
	const string header8 = R"(                                    |_|          |___/                                                     )";

	cout << right;

	cout << setw((UI::TERMINAL_WIDTH + header1.length()) / 2) << header1 << endl
		<< setw((UI::TERMINAL_WIDTH + header2.length()) / 2) << header2 << endl
		<< setw((UI::TERMINAL_WIDTH + header3.length()) / 2) << header3 << endl
		<< setw((UI::TERMINAL_WIDTH + header4.length()) / 2) << header4 << endl
		<< setw((UI::TERMINAL_WIDTH + header5.length()) / 2) << header5 << endl
		<< setw((UI::TERMINAL_WIDTH + header6.length()) / 2) << header6 << endl
		<< setw((UI::TERMINAL_WIDTH + header7.length()) / 2) << header7 << endl
		<< setw((UI::TERMINAL_WIDTH + header8.length()) / 2) << header8 << endl << endl;

	cout << bars << endl << endl;

	return;
}

void displayGoodbye()
{
	clearScreen();

	cout << left;

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