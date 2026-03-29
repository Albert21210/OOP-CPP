#include <iostream>
#include "rational.h"

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");

    // Тестируем конструкторы и вывода
    Rational a(1, 2), b(-1, 6);
    cout << "Тест конструкторов и вывода" << endl;
    cout << "a = " << a << ", b = " << b << endl;

    // Тестируем сложение и упрощение
    cout << "\nТест сложения (a + b)" << endl;
    cout << "a + b = " << a + b << endl;

    // Тестируем оператор += (через += и упрощение)
    cout << "\nТест присваивания (a += b)" << endl;
    a += b;
    cout << "Результат a += b: " << a << endl;

    // Тестируем преобразование в double 
    cout << "\nТест double" << endl;
    cout << "Число b в десятичном виде: " << (double)b << endl;

    // Тестируем преобразование из целого числа 
    Rational c = 3;
    cout << "\nТест преобразования из int" << endl;
    cout << "c = 3 -> " << c << endl;

    // Тестируем ввод и сравнение 
    Rational e(7, 8), f(5, 12);
    cout << "\nИнтерактивный тест" << endl;
    cout << "e = " << e << ", f = " << f << endl;
    cout << "Чему равно e + f? (Введите результат m n): " << endl;

    // Тестируем оператор >> 
    Rational g;
    cin >> g;

    // Тестируем оператор !=
    if (e + f != g) {
        cout << "Неправильно! e + f = " << e + f << endl;
    }
    else {
        cout << "Правильно!" << endl;
    }

    return 0;
}