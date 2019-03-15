/********************************************************************************
****************************** InventoryDatabase ********************************
*********************************************************************************
* The purpose of this class is to control all functions regarding the plaintext
* inventory file. As a module, this module is designed to solely handle all
* read/write operations to the inventory file, such as:
* - Adding a new book to the file
* - Delete a book from the file
* - Change any information in the database
*****************
***** USAGE *****
*****************
* NOTE: This class is mostly intended to have only one single instance at a time.
* Instead of calling multiple new instances of InventoryDatabase, only one instance
* should exist, and the reference of that one instance should be passed around.
*********************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include "InventoryDatabase.h"
#include "InventoryBook.h"

/***************************************************************************
*********** PRIVATE FUNCTIONS
****************************************************************************/

/****************************************
* HELPER FUNCTIONS
*****************************************/

/**
* parseString
*
* @brief Returns a substring of the passed string starting at the (skip + 1)th instance of "<delimiter>" and ending after the subsequent instance of "</delimiter>".
*	The angle brackets and delimiters are removed from the substring.
*	If skip is greater than the number of delimiters in the string, an empty string is returned.
*
* @detail Example: parseString("<txt>Foo</txt> <txt>Bar</txt>", "txt", 0) will return "Foo".
*
* @param str The string to parse. The string should contain "<delimiter>" and "</delimiter>" tags.
*
* @param delimiter The string to act as a delimiter. This function adds angle brackets around the delimiter, so they should not be included in the passed delimiter.
*
* @param skip The number of times to skip an instance of the delimiter.
*
* @return A substring of the passed string starting at the (skip + 1)th instance of "<delimiter>" and ending after the subsequent instance of "</delimiter>".
*	The angle brackets and delimiters are removed from the substring.
*	If skip is greater than the number of delimiters in the string, an empty string is returned.
*/

std::string InventoryDatabase::parseString(const std::string str, const std::string delimiter) const
{
	const std::string delimitBeg = "<" + delimiter + ">";
	const std::string delimitEnd = "</" + delimiter + ">";

	//Find the positions of the first instances of the beginning and ending delimiters
	const size_t delimitBegPos = str.find(delimitBeg);
	const size_t delimitEndPos = str.find(delimitEnd);

	if (delimitBegPos != std::string::npos)
	{
		return str.substr(delimitBegPos + delimitBeg.length(), delimitEndPos - delimitBegPos - delimitBeg.length());
	}
	else
	{
		//The delimiter doesn't exist in the string, return an empty string
		return std::string();
	}
}

std::string InventoryDatabase::parseString(const std::string str, const std::string delimiter, const int skip) const
{
	const std::string delimitBeg = "<" + delimiter + ">";
	const std::string delimitEnd = "</" + delimiter + ">";
	
	//Set the starting position to after the (skip)th delimiter
	size_t startingPos = 0;
	for (int i = 0; i < skip; i++)
	{
		size_t delimiterPos = str.find(delimitEnd, startingPos);
		if (delimiterPos != std::string::npos)
		{
			startingPos = str.find(delimitEnd, startingPos) + delimitEnd.length();
		}
		else
		{
			//The starting position is after the last delimiter, return an empty string
			return std::string();
		}
	}

	//From the starting position, find the positions of the first instances of the beginning and ending delimiters
	const size_t delimitBegPos = str.find(delimitBeg, startingPos);
	const size_t delimitEndPos = str.find(delimitEnd, startingPos);

	//Return the substring between the beginning and ending delimiters
	return str.substr(delimitBegPos + delimitBeg.length(), delimitEndPos - delimitBegPos - delimitBeg.length());
}

/**
* fileToString
*
* @brief Returns the contents of the file located at path as a string. If the file at path doesn't exist, returns an empty string.
*
* @param path The path of the file to convert contents to a string.
*
* @return The contents of the file from path as a string. If the file at path doesn't exist, returns an empty string.
*/

std::string InventoryDatabase::fileToString(std::string path) const
{
	std::ifstream in(path);

	if (in)
	{
		std::string str;

		//Reserve space in the string to store the entire file, not strictly required
		in.seekg(0, std::ios::end);
		str.reserve(in.tellg());
		in.seekg(0, std::ios::beg);

		//Store the entire file in the string by iterating from beginning to end
		str.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

		return str;
	}
	else
	{
		//If the file doesn't exist or isn't openable, return an empty string
		return std::string();
	}
}

/**
* bookToString
*
* @brief Turns a book into a string, formatted into the form used in the inventory file.
*
* @param book The book to turn into a string.
*
* @return The book as a formatted string.
*/

std::string InventoryDatabase::bookToString(InventoryBook book) const
{
	std::string bookString = std::string();

	std::string wholesaleString = std::to_string(book.wholesale);
	wholesaleString = wholesaleString.substr(0, wholesaleString.find(".") + 3);

	std::string retailString = std::to_string(book.retail);
	retailString = retailString.substr(0, retailString.find(".") + 3);

	bookString =
		"<" + DELIM_BOOK + ">" + "\n"
			+ "\t" + "<" + DELIM_ISBN + ">" + book.isbn + "</" + DELIM_ISBN + ">" + "\n"
			+ "\t" + "<" + DELIM_TITLE + ">" + book.title + "</" + DELIM_TITLE + ">" + "\n"
			+ "\t" + "<" + DELIM_AUTHOR + ">" + book.author + "</" + DELIM_AUTHOR + ">" + "\n"
			+ "\t" + "<" + DELIM_PUBLISHER + ">" + book.publisher + "</" + DELIM_PUBLISHER + ">" + "\n"
			+ "\t" + "<" + DELIM_DATE_ADDED + ">" + book.addDate + "</" + DELIM_DATE_ADDED + ">" + "\n"
			+ "\t" + "<" + DELIM_QUANTITY + ">" + std::to_string(book.quantity) + "</" + DELIM_QUANTITY + ">" + "\n"
			+ "\t" + "<" + DELIM_WHOLESALE + ">" + wholesaleString + "</" + DELIM_WHOLESALE + ">" + "\n"
			+ "\t" + "<" + DELIM_RETAIL + ">" + retailString + "</" + DELIM_RETAIL + ">" "\n"
		"</" + DELIM_BOOK + ">" + "\n";

	return bookString;
}

/**
* inventoryArrayToString
*
* @brief Uses inventoryArray and inventoryArraySize to create a full database file string.
*
* @return A string containing the entire database as is currently loaded in memory.
*/

std::string InventoryDatabase::inventoryArrayToString()
{
	std::string booksString = std::string();
	
	for (int i = 0; i < inventoryArraySize; i++)
	{
		booksString.append(bookToString(inventoryArray[i]));
	}

	return booksString;
}

/**
* getNumBooksInString
*
* @brief Returns the number of books in the string based on the book delimiter.
*
* @param str The string to search for books. In almost every case this should be the inventory string.
*
* @return Number of books in the string.
*/

int InventoryDatabase::getNumBooksInString(std::string str) const
{
	int count = 0;
	size_t pos = 0;
	std::string delimiter = "<" + DELIM_BOOK + ">";

	pos = str.find(delimiter, pos);
	while (pos != std::string::npos)
	{
		count++;
		pos = str.find(delimiter, pos + delimiter.length());
	}

	return count;
}

/***************************************************************************
*********** PUBLIC FUNCTIONS
****************************************************************************/

/****************************************
* DATABASE FUNCTIONS
*****************************************/

/**
* buildInventoryArray
*
* @brief Builds and populates inventoryArray. Any existing inventoryArray will be deleted.
*	This should be called once, and only once, before using InventoryDatabase.
*	Calling this multiple times may overwrite changes made to the array but not yet saved to file.
*
* @param path The file path where the inventory file is located. The file should be a plaintext file formatted using the correct specification.
*
* @return True if the file path isn't empty and the file exists, opens, and contains something.
*	False if the file path is empty, or the file doesn't exist, doesn't open, or doesn't contain anything.
*/

bool InventoryDatabase::buildInventoryArray(const std::string path)
{
	inventoryFilePath = path;
	
	//Abort if inventory file path is empty (hasn't been set)
	if (inventoryFilePath == std::string())
	{
		return false;
	}

	inventoryString = fileToString(inventoryFilePath);

	//Abort if inventory file doesn't exist, doesn't open, or doesn't contain anything.
	if (inventoryString == std::string())
	{
		return false;
	}

	//Delete existing inventory array
	inventoryArray.reset();

	//Create new inventory array and populate
	inventoryArraySize = getNumBooksInString(inventoryString);
	inventoryArray = std::make_unique<InventoryBook[]>(inventoryArraySize);

	for (int i = 0; i < inventoryArraySize; i++)
	{
		std::string bookStr = parseString(inventoryString, DELIM_BOOK, i);
		inventoryArray[i].isbn = parseString(bookStr, DELIM_ISBN);
		inventoryArray[i].title = parseString(bookStr, DELIM_TITLE);
		inventoryArray[i].author = parseString(bookStr, DELIM_AUTHOR);
		inventoryArray[i].publisher = parseString(bookStr, DELIM_PUBLISHER);
		inventoryArray[i].addDate = parseString(bookStr, DELIM_DATE_ADDED);
		inventoryArray[i].quantity = std::stoi(parseString(bookStr, DELIM_QUANTITY));
		inventoryArray[i].wholesale = std::stod(parseString(bookStr, DELIM_WHOLESALE));
		inventoryArray[i].retail = std::stod(parseString(bookStr, DELIM_RETAIL));
	}

	return true;
}

/**
* getInventoryArray
*
* @brief Makes a copy of the inventory array and passes the reference of the copy.
*
* @return A smart pointer to a copy of the inventory array.
*/

std::unique_ptr<InventoryBook[]> InventoryDatabase::getInventoryArray() const
{
	std::unique_ptr<InventoryBook[]> copyInventoryArray = std::make_unique<InventoryBook[]>(inventoryArraySize);

	for (int i = 0; i < inventoryArraySize; i++)
	{
		copyInventoryArray[i].isbn = inventoryArray[i].isbn;
		copyInventoryArray[i].title = inventoryArray[i].title;
		copyInventoryArray[i].author = inventoryArray[i].author;
		copyInventoryArray[i].publisher = inventoryArray[i].publisher;
		copyInventoryArray[i].addDate = inventoryArray[i].addDate;
		copyInventoryArray[i].quantity = inventoryArray[i].quantity;
		copyInventoryArray[i].wholesale = inventoryArray[i].wholesale;
		copyInventoryArray[i].retail = inventoryArray[i].retail;
	}

	return copyInventoryArray;
}

/**
* getInventoryArraySize
*
* @brief Returns inventoryArraySize.
*
* @return inventoryArraySize.
*/

int InventoryDatabase::getInventoryArraySize() const
{
	return inventoryArraySize;
}

/**
* setBookIsbnByIsbn
*
* @brief Sets the ISBN of a book in the database based on ISBN.
*
* @param isbn The ISBN of the book to set the ISBN of. If this ISBN doesn't exist for any book in the database,
*	this function will do nothing!
*
* @param edit The string to set the ISBN to.
*/

void InventoryDatabase::setBookIsbnByIsbn(const std::string isbn, const std::string edit)
{
	for (int i = 0; i < inventoryArraySize; i++)
	{
		if (inventoryArray[i].isbn == isbn)
		{
			inventoryArray[i].isbn = edit;
			return;
		}
	}

	return;
}

/**
* setBookTitleByIsbn
*
* @brief Sets the title of a book in the database based on ISBN.
*
* @param isbn The ISBN of the book to set the  of. If this ISBN doesn't exist for any book in the database,
*	this function will do nothing!
*
* @param edit The string to set the title to.
*/

void InventoryDatabase::setBookTitleByIsbn(const std::string isbn, const std::string edit)
{
	for (int i = 0; i < inventoryArraySize; i++)
	{
		if (inventoryArray[i].isbn == isbn)
		{
			inventoryArray[i].title = edit;
			return;
		}
	}

	return;
}

/**
* setBookAuthorByIsbn
*
* @brief Sets the author of a book in the database based on ISBN.
*
* @param isbn The ISBN of the book to set the author of. If this ISBN doesn't exist for any book in the database,
*	this function will do nothing!
*
* @param edit The string to set the author to.
*/

void InventoryDatabase::setBookAuthorByIsbn(const std::string isbn, const std::string edit)
{
	for (int i = 0; i < inventoryArraySize; i++)
	{
		if (inventoryArray[i].isbn == isbn)
		{
			inventoryArray[i].author = edit;
			return;
		}
	}

	return;
}

/**
* setBookPublisherByIsbn
*
* @brief Sets the publisher of a book in the database based on ISBN.
*
* @param isbn The ISBN of the book to set the publisher of. If this ISBN doesn't exist for any book in the database,
*	this function will do nothing!
*
* @param edit The string to set the publisher to.
*/

void InventoryDatabase::setBookPublisherByIsbn(const std::string isbn, const std::string edit)
{
	for (int i = 0; i < inventoryArraySize; i++)
	{
		if (inventoryArray[i].isbn == isbn)
		{
			inventoryArray[i].publisher = edit;
			return;
		}
	}

	return;
}

/**
* setBookAddDateByIsbn
*
* @brief Sets the add date of a book in the database based on ISBN.
*
* @param isbn The ISBN of the book to set the add date of. If this ISBN doesn't exist for any book in the database,
*	this function will do nothing!
*
* @param edit The string to set the add date to.
*/

void InventoryDatabase::setBookAddDateByIsbn(const std::string isbn, const std::string edit)
{
	for (int i = 0; i < inventoryArraySize; i++)
	{
		if (inventoryArray[i].isbn == isbn)
		{
			inventoryArray[i].addDate = edit;
			return;
		}
	}

	return;
}

/**
* setBookQuantityByIsbn
*
* @brief Sets the quantity-on-hand of a book in the database based on ISBN.
*	Note that this doesn't check if the quantity will go below 0 - this should be done
*	on the caller's side.
*
* @param isbn The ISBN of the book to set the quantity of. If this ISBN doesn't exist for any book in the database,
*	this function will do nothing!
*
* @param edit The amount to set the quantity to.
*/

void InventoryDatabase::setBookQuantityByIsbn(const std::string isbn, const int edit)
{
	for (int i = 0; i < inventoryArraySize; i++)
	{
		if (inventoryArray[i].isbn == isbn)
		{
			inventoryArray[i].quantity = edit;
			return;
		}
	}

	return;
}

/**
* setBookWholesaleByIsbn
*
* @brief Sets the wholesale of a book in the database based on ISBN.
*
* @param isbn The ISBN of the book to set the quantity of. If this ISBN doesn't exist for any book in the database,
*	this function will do nothing!
*
* @param edit The amount to set the wholesale to.
*/

void InventoryDatabase::setBookWholesaleByIsbn(const std::string isbn, const double edit)
{
	for (int i = 0; i < inventoryArraySize; i++)
	{
		if (inventoryArray[i].isbn == isbn)
		{
			inventoryArray[i].wholesale = edit;
			return;
		}
	}

	return;
}

/**
* setBookRetailByIsbn
*
* @brief Sets the wholesale of a book in the database based on ISBN.
*
* @param isbn The ISBN of the book to set the quantity of. If this ISBN doesn't exist for any book in the database,
*	this function will do nothing!
*
* @param edit The amount to set the wholesale to.
*/

void InventoryDatabase::setBookRetailByIsbn(const std::string isbn, const double edit)
{
	for (int i = 0; i < inventoryArraySize; i++)
	{
		if (inventoryArray[i].isbn == isbn)
		{
			inventoryArray[i].retail = edit;
			return;
		}
	}

	return;
}

/**
* addToBookQuantityByIsbn
*
* @brief Adds to the quantity-on-hand of a book in the database based on ISBN. Using a negative value will instead subtract from the quantity-on-hand.
*
* @param isbn The ISBN of the book to edit the quantity of. If this ISBN doesn't exist for any book in the database,
*	this function will do nothing!
*
* @param amount The amount to add to the quantity.
*	A positive number will add to the quantity. (The store buys books from a supplier)
*	A negative number will subract from the quantity. (The store sells books to a customer)
*/

void InventoryDatabase::addToBookQuantityByIsbn(const std::string isbn, const int edit)
{
	for (int i = 0; i < inventoryArraySize; i++)
	{
		if (inventoryArray[i].isbn == isbn)
		{
			inventoryArray[i].quantity += edit;
			return;
		}
	}

	return;
}

/**
* getBookByIsbn
*
* @brief Returns the book with the passed ISBN.
*
* @param isbn The ISBN of the book to search for.
*
* @return The InventoryBook matching the passed ISBN. If a book with the passed ISBN doesn't exist, passes a default constructed book.
*/

InventoryBook InventoryDatabase::getBookByIsbn(std::string isbn)
{
	for (int i = 0; i < inventoryArraySize; i++)
	{
		if (inventoryArray[i].isbn == isbn)
		{
			return inventoryArray[i];
		}
	}

	return InventoryBook();
}

/**
* getBookIndexByIsbn
*
* @brief Returns the index of the book with the passed ISBN.
*
* @param isbn The ISBN of the book to search for.
*
* @return The index of the book matching the passed ISBN. If a book with the passed ISBN doesn't exist, passes -1.
*/

int InventoryDatabase::getBookIndexByIsbn(std::string isbn)
{
	for (int i = 0; i < inventoryArraySize; i++)
	{
		if (inventoryArray[i].isbn == isbn)
		{
			return i;
		}
	}

	return -1;
}

/**
* addBookToArray
*
* @brief Adds a new book to the inventory array.
*
* @param book The new book to add to the inventory array.
*/

void InventoryDatabase::addBookToArray(InventoryBook book)
{
	//Make a new array to hold the new book plus the old books
	std::unique_ptr<InventoryBook[]> newInventoryArray = std::make_unique<InventoryBook[]>(inventoryArraySize + 1);

	//Copy the old books into the new array
	for (int i = 0; i < inventoryArraySize; i++)
	{
		newInventoryArray[i] = inventoryArray[i];
	}

	//Copy the new book into the new array
	newInventoryArray[inventoryArraySize] = book;

	//Swap the old array and the new array, then set the array size variable to the right value
	inventoryArray.swap(newInventoryArray);
	inventoryArraySize++;
	
	return;
}

/**
* removeBookFromArray
*
* @brief Removes a book from the inventory array.
*
* @param index The index of the book to remove from the inventory array.
*/

void InventoryDatabase::removeBookFromArray(int index)
{
	//Make a new array to hold the old books, minus the one we are removing
	std::unique_ptr<InventoryBook[]> newInventoryArray = std::make_unique<InventoryBook[]>(inventoryArraySize - 1);

	//Keep track of whether we have passed the book to remove or not
	bool passedIndex = false;

	//Copy the old books into the new array, except the one we are removing
	for (int i = 0; i < index; i++)
	{
		newInventoryArray[i] = inventoryArray[i];
	}
	for (int i = index + 1; i < inventoryArraySize; i++)
	{
		newInventoryArray[i - 1] = inventoryArray[i];
	}

	//Swap the old array and the new array, then set the array size variable to the right value
	inventoryArray.swap(newInventoryArray);
	inventoryArraySize--;

	return;
}

/****************************************
* CONSTRUCTORS / DESTRUCTORS
*****************************************/

/**
* InventoryDatabase
*
* @brief Creates a new object of type InventoryDatabase. Overloading sets the inventory file path to the passed string.
*	If called without overloading, setInventoryFilePath should be called later to properly prepare InventoryDatabase.
*
* @param path Path to set inventoryFilePath to, should be a plaintext file.
*/

InventoryDatabase::InventoryDatabase()
{
	inventoryFilePath = std::string();
	inventoryString = std::string();
}

InventoryDatabase::InventoryDatabase(std::string path)
{
	inventoryFilePath = path;
	inventoryString = fileToString(inventoryFilePath);
}

/**
* ~InventoryDatabase
*
* @brief Called when InventoryDatabase leaves scope.
*/

InventoryDatabase::~InventoryDatabase()
{
	
}