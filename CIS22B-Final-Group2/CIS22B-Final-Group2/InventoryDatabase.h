#pragma once

//Debugging
#include <iostream>
//Debugging

#include <string>
#include <fstream>
#include <streambuf>
#include "Book.h"

class InventoryDatabase
{
private:
	std::string inventoryFilePath;
	Book* bookArray;

	void createBookArray();
	void deleteBookArray();
	std::string inventoryFileToString();
	int getBookCount();
public:
	void setInventoryFilePath(std::string path);
	void debug();

	InventoryDatabase();

	~InventoryDatabase();
};