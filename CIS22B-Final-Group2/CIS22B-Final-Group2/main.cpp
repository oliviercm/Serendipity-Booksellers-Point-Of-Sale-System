/*
CIS 22B
Final: Serendipity Booksellers POS System
Group 2:
	Olivier Chan Sion Moy
	Luis Guerrero
	Natalia Coelho Mendonca
	Samuel Ruiz Cervantes
	Manasi Gowda
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include "InventoryDatabase.h"

int main()
{
	const bool debug = true;
	if (debug)
	{
		InventoryDatabase inventoryDatabase;
		inventoryDatabase = InventoryDatabase("books.txt");

		inventoryDatabase.debug();
		InventoryDatabase::buildInventory();
	}
	
	std::cin.get();
	return 0;
}