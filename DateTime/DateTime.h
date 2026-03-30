#pragma once

#include <iostream>

using namespace std;

class DateTime {
private:
	// дни, месяцы, годы
	int day;
	int month;
	int year;

	// дополнительные вспомогательные методы
	bool isLeapYear(int y) const;
	int daysInMonth(int m, int y) const;
	long long getAbsoluteDays() const;

public:
	// конструкторы
	DateTime();
	DateTime(int d, int m, int y);

	// основные методы
	bool isValid(int d, int m, int y) const;
	void input();

	// методы вывода
	void printFormat1() const;
	void printFormat2() const;
	void printFormat3() const;

	// вычисления
	long long getDifferenceInDays(const DateTime& other) const;
	const char* getDayOfWeek() const;

};