#include <iostream>
#include "rational.h"

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");

    // тестируем конструкторы и вывод
    Rational a(1, 2), b(-1, 6);
    cout << "Тест конструкторов и вывода" << endl;
    cout << "a = " << a << ", b = " << b << endl;

    // тестируем сложение и упрощение
    cout << "\nТест сложения (a + b)" << endl;
    cout << "a + b = " << a + b << endl;

    // тестируем оператор += (через += и упрощение)
    cout << "\nТест присваивания (a += b)" << endl;
    a += b;
    cout << "Результат a += b: " << a << endl;

    // тестируем преобразование в double 
    cout << "\nТест double" << endl;
    cout << "Число b в десятичном виде: " << (double)b << endl;

    // тестируем преобразование из целого числа 
    Rational c = 3;
    cout << "\nТест преобразования из int" << endl;
    cout << "c = 3 -> " << c << endl;

    // тестируем ввод и сравнение 
    Rational e(7, 8), f(5, 12);
    cout << "\nТест" << endl;
    cout << "e = " << e << ", f = " << f << endl;
    cout << "Чему равно e + f? (Введите результат m n): " << endl;

    // тестируем оператор >> 
    Rational g;
    cin >> g;

    // тестируем оператор !=
    if (e + f != g) {
        cout << "Неправильно! e + f = " << e + f << endl;
    }
    else {
        cout << "Правильно!" << endl;
    }

    return 0;
}
