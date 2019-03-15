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

#pragma once

#include <string>
#include <fstream>
#include "InventoryBook.h"

class InventoryDatabase
{
private:
	//Variable members
	std::string inventoryFilePath;
	std::string inventoryString;
	std::unique_ptr<InventoryBook[]> inventoryArray;
	int inventoryArraySize;

	//Constant members
	const std::string DELIM_BOOK = "book";
	const std::string DELIM_ISBN = "isbn";
	const std::string DELIM_TITLE = "title";
	const std::string DELIM_AUTHOR = "author";
	const std::string DELIM_PUBLISHER = "publisher";
	const std::string DELIM_DATE_ADDED = "adddate";
	const std::string DELIM_QUANTITY = "quantity";
	const std::string DELIM_WHOLESALE = "wholesale";
	const std::string DELIM_RETAIL = "retail";

	//Helper functions
	std::string parseString(const std::string str, const std::string delimiter) const;
	std::string parseString(const std::string str, const std::string delimiter, const int skip) const;
	std::string fileToString(const std::string path) const;
	int getNumBooksInString(const std::string str) const;

public:
	//Database functions
	bool buildInventoryArray(const std::string path);
	std::unique_ptr<InventoryBook[]> getInventoryArray() const;
	int getInventoryArraySize() const;
	void editBookQuantityByIsbn(std::string isbn, int amount);
	InventoryBook getBookByIsbn(std::string isbn);

	//Constuctors / Destructors
	InventoryDatabase();
	InventoryDatabase(const std::string path);
	~InventoryDatabase();

	//Delete copy constructor and copy assignment
	InventoryDatabase(const InventoryDatabase&) = delete;
	InventoryDatabase& operator=(const InventoryDatabase) = delete;
};