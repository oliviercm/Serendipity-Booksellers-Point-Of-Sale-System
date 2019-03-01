#pragma once

//Debugging, remove in final build
#include <iostream>

#include <string>
#include <fstream>
#include "Book.h"

class InventoryDatabase
{
private:
	//Static members
	static std::string inventoryFilePath;
	static std::string inventoryString;
	static Book* inventoryArray;

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
	std::string parseString(const std::string str, const std::string delimiter);
	std::string parseString(const std::string str, const std::string delimiter, const int skip);
	std::string fileToString(std::string path);
	int getBookCount();

	//Database-related functions
	void deleteInventoryArray();

public:
	//Database-related functions
	bool buildInventoryArray();
	bool buildInventoryArray(const std::string path);
	const std::string getInventoryFilePath();
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