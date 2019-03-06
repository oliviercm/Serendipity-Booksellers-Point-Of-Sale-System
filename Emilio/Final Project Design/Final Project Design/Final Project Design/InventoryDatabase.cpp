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
* In order to use this class, first create a new InventoryDatabase.
* It is recommended to use the overloaded constructor on the first construction,
* otherwise, calling most functions will try to work with an inventory file
* at an empty path if you haven't set the file path yet (this will cause problems)
*********************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include "InventoryDatabase.h"

/****************************************
* STATIC MEMBERS
*****************************************/

std::string InventoryDatabase::inventoryFilePath = std::string();
std::string InventoryDatabase::inventoryString = std::string();
Book* InventoryDatabase::inventoryArray = nullptr;

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

std::string InventoryDatabase::parseString(const std::string str, const std::string delimiter)
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

std::string InventoryDatabase::parseString(const std::string str, const std::string delimiter, const int skip)
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

std::string InventoryDatabase::fileToString(std::string path)
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
* getBookCount
*
* @brief Returns the number of books in the inventory string based on the book delimiter.
*
* @return Number of books in the inventory string.
*/

int InventoryDatabase::getBookCount()
{
	std::string inventoryStr = inventoryString;
	int count = 0;
	size_t pos = 0;
	std::string delimiter = "<" + DELIM_BOOK + ">";

	pos = inventoryStr.find(delimiter, pos);
	while (pos != std::string::npos)
	{
		count++;
		pos = inventoryStr.find(delimiter, pos + delimiter.length());
	}

	return count;
}

/****************************************
* DATABASE FUNCTIONS
*****************************************/

/**
* deleteInventoryArray
*
* @brief Deletes the dynamically allocated inventoryArray, if it exists.
*/

void InventoryDatabase::deleteInventoryArray()
{
	if (inventoryArray != nullptr)
	{
		delete[] inventoryArray;
		inventoryArray = nullptr;
	}

	return;
}

/**
* buildInventoryArray
*
* @brief Builds and populates inventoryArray. Any existing inventoryArray will be deleted.
*
* @return True if the file path was not empty (never set/initialized). Note that an invalid path will act the same as a path to an empty file - it will return true and build an empty inventoryArray.
*	False if the file path is empty ("")
*/

bool InventoryDatabase::buildInventoryArray()
{
	//Abort if inventory file path isn't set
	if (inventoryFilePath == std::string())
	{
		return false;
	}

	inventoryString = fileToString(inventoryFilePath);

	//Delete existing inventory array for replacement
	if (inventoryArray != nullptr)
	{
		deleteInventoryArray();
	}

	//Create new inventory array and populate
	int bookCount = getBookCount();
	inventoryArray = new Book[bookCount];

	for (int i = 0; i < bookCount; i++)
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

bool InventoryDatabase::buildInventoryArray(const std::string path)
{
	inventoryFilePath = path;

	inventoryString = fileToString(inventoryFilePath);

	//Delete existing inventory array for replacement
	if (inventoryArray != nullptr)
	{
		deleteInventoryArray();
	}

	//Create new inventory array and populate
	int bookCount = getBookCount();
	inventoryArray = new Book[bookCount];

	for (int i = 0; i < bookCount; i++)
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
* getInventoryFilePath
*
* @brief Returns inventoryFilePath.
*
* @return inventoryFilePath
*/

const std::string InventoryDatabase::getInventoryFilePath()
{
	return inventoryFilePath;
}

/**
* setInventoryFilePath
*
* @brief Sets inventoryFilePath to path.
*
* @param path Path to set inventoryFilePath to, should be a plaintext file.
*/

void InventoryDatabase::setInventoryFilePath(std::string path)
{
	inventoryFilePath = path;
}

/****************************************
* CONSTRUCTORS / DESTRUCTORS
*****************************************/

/**
* InventoryDatabase
*
* @brief Creates a new object of type InventoryDatabase. Overloading sets the inventory file path to the passed string.
*
* @param path Path to set inventoryFilePath to, should be a plaintext file.
*/

InventoryDatabase::InventoryDatabase()
{

}

InventoryDatabase::InventoryDatabase(std::string path)
{
	InventoryDatabase::inventoryFilePath = path;
	buildInventoryArray();
}

/**
* ~InventoryDatabase
*
* @brief Called when InventoryDatabase leaves scope. Deletes the dynamically allocated bookArray if it exists.
*/

InventoryDatabase::~InventoryDatabase()
{
	deleteInventoryArray();
}

/****************************************
* DEBUG FUNCTION (REMOVE IN FINAL BUILD)
*****************************************/

/**
* debug
*
* @brief For debugging purposes only. Remove this function in the final build.
*/

void InventoryDatabase::debug()
{
	//std::cout << getBookCount() << std::endl;
	//std::string str1 = "abc <txt>Foo</txt> <txt>Bar</txt> <bar> </bar> <txt> <txt> mischief </txt> <txt> whoops";
	//std::string str2 = "abc <nop>Foo <nop> oops";
	//std::cout << parseString(str2, "nop") << std::endl;

	int bookCount = getBookCount();

	for (int i = 0; i < bookCount; i++)
	{
		std::cout << "Book " << i << ":" << std::endl;
		std::cout << "IBSN: " << inventoryArray[i].isbn << std::endl;
		std::cout << "Title: " << inventoryArray[i].title << std::endl;
		std::cout << "Author: " << inventoryArray[i].author << std::endl;
		std::cout << "Publisher: " << inventoryArray[i].publisher << std::endl;
		std::cout << "Add Date: " << inventoryArray[i].addDate << std::endl;
		std::cout << "Quantity: " << inventoryArray[i].quantity << std::endl;
		std::cout << "Wholesale: " << inventoryArray[i].wholesale << std::endl;
		std::cout << "Retail: " << inventoryArray[i].retail << std::endl;
		std::cout << std::endl;
	}
	return;
}