#define _CRT_SECURE_NO_WARNINGS

#include "InventoryDatabase.h"

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

int InventoryDatabase::getBookCount()
{
	std::string inventory = inventoryFileToString();
	int count = 0;
	size_t pos = 0;
	const std::string delimiter = "<book>";

	pos = inventory.find(delimiter, pos);
	while (pos != std::string::npos)
	{
		count++;
		pos = inventory.find(delimiter, pos + delimiter.length());
	}

	return count;
}

void InventoryDatabase::setInventoryFilePath(std::string path)
{
	inventoryFilePath = path;
	return;
}

void InventoryDatabase::createInventoryArray()
{
	inventoryArray = new Book[getBookCount()];

	for (int i = 0; i < getBookCount(); i++)
	{
		inventoryArray[i].quantity = i + 1;
	}

	return;
}

void InventoryDatabase::debug()
{
	//std::cout << getBookCount() << std::endl;
	createInventoryArray();
	return;
}

InventoryDatabase::InventoryDatabase()
{
	inventoryFilePath = "";
	inventoryArray = nullptr;
}

InventoryDatabase::~InventoryDatabase()
{
	if (inventoryArray != nullptr)
	{
		delete [] inventoryArray;
	}
}