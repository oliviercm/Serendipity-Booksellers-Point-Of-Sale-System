# Serendipity Booksellers POS (Point-Of-Sale) System 

This is a point-of-sale software package that functions as a cash register and keeps an inventory file.

The software can perform the following tasks:

* Calculate the total of a sale, including sales tax
* When a book is purchased, subtract it from the inventory file
* Add, change, delete, and look up books in the inventory file
* Display various sales reports

## Modules

The program is organized into the following three modules:

### 1. Cashier Module

The Cashier Module allows the computer to act as a cash register. The user enters information for the books being purchased and the program calculates the sales tax and total price. In addition, the books being purchased are automatically subtracted from the Inventory Database.

### 2. Inventory Database Module

The Inventory Database is a text file containing a list of all the books in Serendipity's inventory. The following information for each book is stored in the file:

* ISBN
* Title
* Author
* Publisher
* Date Added
* Quantity-On-Hand
* Wholesale Cost
* Retail Price

The Inventory Database module allows the user to look up information on any book in the file, add new books to the file, delete books, and change any information in the database.

### 3. Report Module

The Report Module analyzes the information in the Inventory Database to produce any of the following reports:

* Inventory List
* Inventory Wholesale Value
* Inventory Retail Value
* List by Quantity
* List by Cost
* List by Age

## Authors

All authors are students at De Anza College, Cupertino, California.
This program was written as a final group project for De Anza W19 CIS D022B 03Y, 61Y Intermediate Programming Methods in C++, Professor Manish Goel, Fall Quarter 2019.

* **Olivier Chan Sion Moy**
* **Luis Guerrero**
* **Natalia Coelho Mendonca**
* **Samuel Ruiz Cervantes**
* **Manasi Gowda**
