#pragma once
#include <iostream>

using namespace std;

class Rational {
private:
    int numer;
    int denom;

    void simplify();

public:
    // Конструкторы
    Rational();
    Rational(int number);
    Rational(int n, int d);

    // Арифметические операции
    Rational& operator +=(const Rational& r);
    Rational operator +(const Rational& r) const;
    Rational operator -() const;
    Rational operator -(const Rational& r) const;
    Rational& operator -=(const Rational& r);

    // Инкремент
    Rational& operator ++();
    Rational operator ++(int);

    // Сравнение
    bool operator ==(const Rational& r) const;
    bool operator !=(const Rational& r) const;

    // Преобразование типов
    operator int() const;
    operator double() const;

    // Ввод-вывод 
    friend istream& operator >>(istream& in, Rational& r);
    friend ostream& operator <<(ostream& out, const Rational& r);
};
