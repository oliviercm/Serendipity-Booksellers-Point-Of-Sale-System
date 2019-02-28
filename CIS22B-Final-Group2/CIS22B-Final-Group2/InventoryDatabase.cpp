#define _CRT_SECURE_NO_WARNINGS

#include "InventoryDatabase.h"

/****************************************
 * INITALIZE STATIC MEMBERS
 ****************************************/

std::string InventoryDatabase::inventoryFilePath = std::string();
Book* InventoryDatabase::bookArray = nullptr;

/****************************************
 * HELPER FUNCTIONS
 ****************************************/

/**
 * parseString
 *
 * @brief Returns a substring of the passed string starting at the first instance of "<delimiter>" and ending at the first instance of "</delimiter>". The angle brackets and delimiter are removed from the substring.
 *
 * @detail Example: parseString("<txt>Foo</txt> <txt>Bar</txt>", "txt") will return "Foo".
 *
 * @param str The string to parse. The string should contain "<delimiter>" and "</delimiter>" tags.
 *
 * @param delimiter The string to act as a delimiter. This function adds angle brackets around the delimiter, so they should not be included in the passed delimiter.
 *
 * @return A substring of str starting from the first "<delimiter>" and ending at the first "</delimiter>", not including the delimiters and angle brackets.
 */

std::string InventoryDatabase::parseString(std::string str, std::string delimiter)
{
	return std::string();
}

/**
 * inventoryFileToString
 *
 * @brief Returns the contents of the file located at inventoryFilePath as a string. If the file at inventoryFilePath doesn't exist, returns an empty string.
 *
 * @return The contents of the file from inventoryFilePath as a string. If the file at inventoryFilePath doesn't exist, returns an empty string.
 */

std::string InventoryDatabase::inventoryFileToString()
{
	std::ifstream in(inventoryFilePath);

	if (in)
	{
		std::string books;

		//Reserve space in the string to store the entire file
		in.seekg(0, std::ios::end);
		books.reserve(in.tellg());
		in.seekg(0, std::ios::beg);

		//Store the entire file in the string by iterating from beginning to end
		books.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

		return books;
	}
	else
	{
		return std::string();
	}
}

/**
 * getBookCount
 *
 * @brief Returns the number of books in the inventory file.
 *
 * @return Number of "<book>"s in the inventory file.
 */

int InventoryDatabase::getBookCount()
{
	std::string inventory = inventoryFileToString();
	int count = 0;
	size_t pos = 0;
	const std::string DELIMITER = "<book>";

	pos = inventory.find(DELIMITER, pos);
	while (pos != std::string::npos)
	{
		count++;
		pos = inventory.find(DELIMITER, pos + DELIMITER.length());
	}

	return count;
}

/****************************************
 * DATABASE FUNCTIONS
 ****************************************/

 /**
  * createBookArray
  *
  * @brief Deletes bookArray if it exists, then creates a new bookArray the size of the number of books in the inventory file.
  */

void InventoryDatabase::createBookArray()
{
	if (bookArray != nullptr)
	{
		deleteBookArray();
	}

	bookArray = new Book[getBookCount()];

	return;
}

/**
 * deleteBookArray
 *
 * @brief Deletes the dynamically allocated bookArray, if it exists.
 */

void InventoryDatabase::deleteBookArray()
{
	if (bookArray != nullptr)
	{
		delete[] bookArray;
		bookArray = nullptr;
	}

	return;
}

/**
 * setInventoryFilePath
 *
 * @brief Sets inventoryFilePath to the passed path.
 *
 * @param path The path to the database file. This should be a path to a .txt file. Partial paths are executed relative to the executable.
 */

void InventoryDatabase::setInventoryFilePath(std::string path)
{
	inventoryFilePath = path;
	return;
}

/****************************************
 * CONSTRUCTORS / DESTRUCTORS
 ****************************************/

 /**
  * InventoryDatabase
  *
  * @brief Creates a new object of type InventoryDatabase. NOTE: setInventoryFilePath() and createBookArray() should be called before using InventoryDatabase for the first time!
  */

InventoryDatabase::InventoryDatabase()
{
	
}

/**
 * ~InventoryDatabase
 *
 * @brief Called when InventoryDatabase leaves scope. Deletes the dynamically allocated bookArray if it exists.
 */

InventoryDatabase::~InventoryDatabase()
{
	deleteBookArray();
}

/****************************************
 * DEBUG FUNCTION (REMOVE IN FINAL BUILD)
 ****************************************/

 /**
  * debug
  *
  * @brief For debugging purposes only. Remove this function in the final build.
  */

void InventoryDatabase::debug()
{
	//std::cout << getBookCount() << std::endl;
	//createBookArray();
	std::cout << InventoryDatabase::inventoryFilePath << std::endl;
	return;
}