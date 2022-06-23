#pragma once
#include <iostream>
using namespace std;

class Date
{
	int day;
	int month;
	int year;

public:
	Date();
	Date(int _day, int _month, int _year);
	~Date();

	void setDay(int _day);
	void setMonth(int _month);
	void setYear(int _year);
	void setDate(); // + сэттэр. почему бы и нет? доработал.

	int getDay()const;
	int getMonth()const;
	int getYear()const;

	void showDate()const;
	void getNowDate(); // Доработка
	char* toString(); // Доработка
	bool isLeapYear(); // Доработка
};

