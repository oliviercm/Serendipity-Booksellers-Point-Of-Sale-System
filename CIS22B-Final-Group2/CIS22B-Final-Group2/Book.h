#pragma once

#include <string>

struct Book
{
public:
	//Book information
	std::string isbn;
	std::string title;
	std::string author;
	std::string publisher;
	std::string addDate;
	int quantity;
	double wholesale;
	double retail;

	//Constructors
	Book();
	Book(std::string is, std::string ti, std::string au, std::string pu, std::string ad, int qu, double wh, double re);

	//Destructors
	~Book();
};