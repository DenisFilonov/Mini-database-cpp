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
	void setDate(); // + ������. ������ �� � ���? ���������.

	int getDay()const;
	int getMonth()const;
	int getYear()const;

	void showDate()const;
	void getNowDate(); // ���������
	char* toString(); // ���������
	bool isLeapYear(); // ���������
};

