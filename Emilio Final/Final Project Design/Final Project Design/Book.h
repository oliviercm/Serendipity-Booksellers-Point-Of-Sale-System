#pragma once
#include <iostream>

class Book {

public:
	std::string bookTitle;
	std::string bookAuthor;
	std::string bookPublisher;
	std::string date;
	int quantity;
	double wholePrice;
	double retailPrice;
	int isbn;

	//Accessors
	std::string getTitle() const { return bookTitle; }
	std::string getAuthor() const { return bookAuthor; }
	std::string getPublisher() const { return bookPublisher; }
	std::string getDate() const { return date; }
	int getOnHand() const { return quantity; }


	//Mutators

};
