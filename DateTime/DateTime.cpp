#include <iostream>
#include <cmath>
#include "DataTime.h"

using namespace std;

// проверка на високосный год
bool DateTime::isLeapYear(int y) const {
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// количество дней в месяце
int DateTime::daysInMonth(int m, int y) const {
	int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (m == 2 && isLeapYear(y)) {
		return 29;
	}
	return days[m];
}

// вычисление абсолютного количества дней (для разницы дат)
long long DateTime::getAbsoluteDays() const {
	int y = year;
	int m = month;
	if (m <= 2) {
		y--;
	}
	long long totalDays = year * 365 + day;
	for (int i = 1; i < month; i++) {
		totalDays += daysInMonth(i, year);
	}
	totalDays += (y / 4 - y / 100 + y / 400);
	return totalDays;
}

// конструктор по умолчанию
DateTime::DateTime() {
	day = 1;
	month = 1;
	year = 2000;
}

// конструктор с параметрами
DateTime::DateTime(int d, int m, int y) {
	if (isValid(d, m, y)) {
		day = d; month = m; year = y;
	}
	else {
		cout << "Ошибка! Некорректная дата! Установлено 01.01.2000" << endl;
		day = 1; month = 1; year = 2000;
	}
}

// проверка корректности
bool DateTime::isValid(int d, int m, int y) const {
	if (y < 1 || m < 1 || m > 12 || d < 1) {
		return false;
	}
	return d <= daysInMonth(m, y);
}

// ввод с клавиатуры
void DateTime::input() {
	int d, m, y;
	cout << "Enter your date (day month year with space): ";

	if (!(cin >> d >> m >> y)) {
		cout << "Ошибка ввода чисел!\n";
		return;
	}

	if (isValid(d, m, y)) {
		day = d;
		month = m;
		year = y;
		cout << "Date was succesfully updated.\n";
	}
	else {
		cout << "Error: Invalid date!\n";
	}
}

// формат 1: 1.01.2001
void DateTime::printFormat1() const {
	cout << day << ".";
	if (month < 10) {
		cout << "0";
	}
	cout << month << "." << year << endl;
}

// формат 2: 1 января 2001
void DateTime::printFormat2() const {
	const char* months[] = { "", "Janyary", "February", "March", "April", "May", "June",
							 "July", "August", "September", "October", "November", "December" };
	cout << day << " " << months[month] << " " << year << endl;
}

// формат 3: 01.01.01
void DateTime::printFormat3() const {
	if (day < 10) cout << "0";
	cout << day << ".";

	if (month < 10) cout << "0";
	cout << month << ".";

	int shortYear = year % 100;
	if (shortYear < 10) cout << "0";
	cout << shortYear << endl;
}

// разница в днях
long long DateTime::getDifferenceInDays(const DateTime& other) const {
	return std::abs(this->getAbsoluteDays() - other.getAbsoluteDays());
}

// день недели
const char* DateTime::getDayOfWeek() const {
	int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	int y = year;
	if (month < 3) y -= 1;

	int dayOfWeek = (y + y / 4 - y / 100 + y / 400 + t[month - 1] + day) % 7;

	const char* days[] = { "Sunday", "Monday", "Tuesday", "Wednesday",
						   "Thursday", "Friday", "Saturday" };
	return days[dayOfWeek];
}