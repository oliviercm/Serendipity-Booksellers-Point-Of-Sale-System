// Luis, Oliver and Natalia

#include <iostream>
#include<string.h>
#include<iomanip>

using namespace std;	

void displayMainMenu();
void displayCashierModule();
void displayInventory();
void displayReport();
void displayInventoryList();


int main() {
	int input, input3;

	displayMainMenu();
	cout << "Choose an option : ";
	cin >> input;

	if (input == 1) {
		displayCashierModule();
	}
	else if (input == 2) {
		displayInventory();
	}
	else if (input == 3) {
		displayReport();
		cout << "Choose an option: ";
		cin >> input3;
		if (input3 == 1) {
			displayInventoryList();
		}
	}
	else
		cout << "ERROR: Exit";


	system("pause");
	return 0;
}

void displayMainMenu() {

	cout << endl;
	cout << setw(45) << "Welcome to Serendipity Booksellers." << endl;
	cout << endl;
	cout << "===================================================" << endl;
	cout << endl;
	cout << setw(31) << "[ MAIN MENU ] " << endl;
	cout << endl;
	cout << setw(32) << "[ 1 ] CASHIER MODE " << endl;
	cout << endl;
	cout << setw(34) << "[ 2 ] INVENTORY MODE " << endl;
	cout << endl;
	cout << setw(31) << "[ 3 ] REPORT MODE " << endl;
	cout << endl;
	cout << setw(24) << "[ 4 ] EXIT " << endl;
	cout << endl;
	cout << "===================================================" << endl;
	cout << endl;

	return;
}

void displayCashierModule() {

	cout << endl;
	cout << "===================================================" << endl;
	cout << endl;
	cout << setw(31) << "[ CASHIER MODE ] " << endl;
	cout << endl;
	cout << setw(33) << "[ 1 ] PURCHASE A BOOK " << endl;
	cout << endl;
	cout << setw(29) << "[ 2 ] RENT A BOOK " << endl;
	cout << endl;
	cout << setw(22) << "[ 3 ] EXIT " << endl;
	cout << endl;
	cout << "===================================================" << endl;
	cout << endl;

	return;
}

void displayInventory() {

	cout << endl;
	cout << "===================================================" << endl;
	cout << endl;
	cout << right << setw(31) << "[ INVENTORY ] " << endl;
	cout << endl;
	cout << setw(5) << "TITLE: " << " Physics for Scientist and Engineers (9th edition)" << endl << endl
		<< setw(5) << "AUTHOR: " << "Jewett Serway" << endl << endl
		<< setw(5) << "PUBLISHER: " <<"Cengage Learning" << endl << endl
		<< setw(5) << "DATE: " << "02/21/2019" << endl << endl
		<< setw(5) << "ON-HAND: " << "5" << endl << endl
		<< setw(5) << "WHOLESALE-PRICE: " << "155.93" << endl << endl
		<< setw(5) << "RETAIL-PRICE: " << "164.99" << endl << endl
		<< setw(5) << "ISBN: " << "9781305116405"  << endl;
	cout << endl;
	cout << "===================================================" << endl;
	cout << endl;

	return;
}

void displayReport() {
	cout << endl;
	cout << "===================================================" << endl;
	cout << endl;
	cout << setw(31) << "[ REPORT MODE ] " << endl;
	cout << endl;
	cout << setw(32) << "[ 1 ] INVENTORY LIST " << endl;
	cout << endl;
	cout << setw(37) << "[ 2 ] WHOLESALE INVENTORY " << endl;
	cout << endl;
	cout << setw(34) << "[ 3 ] RETAIL INVENTORY " << endl;
	cout << endl;
	cout << setw(34) << "[ 4 ] LIST BY QUANTITY " << endl;
	cout << endl;
	cout << setw(30) << "[ 5 ] LIST BY COST " << endl;
	cout << endl;
	cout << setw(29) << "[ 6 ] LIST BY AGE " << endl;
	cout << endl;
	cout << "===================================================" << endl;
	cout << endl;

	return;
}

void displayInventoryList() {

	cout << "===================================================" << endl;
	cout << endl;
	cout << setw(31) << "[ INVENTORY LIST ] " << endl;
	cout << endl;
	cout << setw(5) << "TITLE: " << " Physics for Scientist and Engineers (9th edition)" << endl << endl
		<< setw(5) << "AUTHOR: " << "Jewett Serway" << endl << endl
		<< setw(5) << "PUBLISHER: " << "Cengage Learning" << endl << endl
		<< setw(5) << "DATE: " << "02/21/2019" << endl << endl
		<< setw(5) << "ON-HAND: " << "5" << endl << endl
		<< setw(5) << "WHOLESALE-PRICE: " << "155.93" << endl << endl
		<< setw(5) << "RETAIL-PRICE: " << "164.99" << endl << endl
		<< setw(5) << "ISBN: " << "9781305116405" << endl;
	cout << endl;


	cout << "===================================================" << endl;
	cout << endl;

	return;
}

/*
void displayInventory() {
	
	cout << "===================================================" << endl;
	cout << endl;
	cout << right << setw(31) << "[ INVENTORY ] " << endl;
	cout << endl;
	cout << left << setw(5) << "TITLE " << right << setw(10) << " AUTHOR " 
		<< right << setw(10) << " PUBLISHER " << right << setw(10) << " DATE "
		<< right << setw(10) << " ON-HAND "
		<< right << setw(10) << " WHOLESALE-PRICE "
		<< right << setw(10) << " RETAIL-PRICE "
		<< right << setw(10) << " ISBN " << endl;

	cout << left << setw(5) << "Physics for Scientist and Engineers (9th edition) " << right << setw(10) << " Jewett Serway "
		<< right << setw(10) << " Cengage Learning " << right << setw(10) << " 02/21/2019 "
		<< right << setw(10) << " 5 "
		<< right << setw(10) << " 155.93 "
		<< right << setw(10) << " 164.99 " 
		<< right << setw(10) << " 9781305116405 " << endl;
	
	cout << "===================================================" << endl;
	cout << endl;

	return;
}
*/