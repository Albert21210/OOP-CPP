#include <iostream>
#include "DataTime.h"

using namespace std;

int main() {
    // тестируем
    setlocale(LC_ALL, ".UTF8");

    cout << "Тест форматов вывода" << endl;
    cout << " " << endl;

    DateTime date1(5, 4, 2024);
    cout << "Формат 1\n";
    date1.printFormat1();
    cout << "Формат 2\n";
    date1.printFormat2();
    cout << "Формат 3\n";
    date1.printFormat3();

    cout << "\nДень недели: " << date1.getDayOfWeek() << "\n\n";

    cout << "Тест разницы дат\n";
    cout << " " << endl;
    DateTime date2(10, 4, 2024);

    cout << "Дата: " << 10 << "." << 0 << 4 << "." << 2024 << endl;
    cout << "Разница в днях: " << date1.getDifferenceInDays(date2) << "\n\n";

    cout << "Тест ввода" << endl;
    cout << " " << endl;
    DateTime date3;
    date3.input();
    cout << "Вы ввели: ";
    date3.printFormat2();

    return 0;
}