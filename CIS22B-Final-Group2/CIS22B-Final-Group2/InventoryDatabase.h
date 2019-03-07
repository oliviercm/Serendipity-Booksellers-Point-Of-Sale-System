#pragma once

//Debugging, remove in final build
#include <iostream>

#include <string>
#include <fstream>
#include "InventoryBook.h"

class InventoryDatabase
{
private:
	//Variable members
	std::string inventoryFilePath;
	std::string inventoryString;
	InventoryBook* inventoryArray;
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

	//Database-related functions
	void deleteInventoryArray();

public:
	//Database-related functions
	bool buildInventoryArray();
	std::string getInventoryFilePath() const;
	void setInventoryFilePath(const std::string path);

	//Constuctors
	InventoryDatabase();
	InventoryDatabase(const std::string path);
	InventoryDatabase(const InventoryDatabase&) = delete; //Delete copy constructor

	//Destructors
	~InventoryDatabase();

	//Operator overloads
	InventoryDatabase& operator=(const InventoryDatabase) = delete; //Delete assignment operator

	//Debugging function, remove in final build
	void debug();
};