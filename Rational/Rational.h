#pragma once
#include <iostream>

using namespace std;

class Rational {
private:
    // числитель
    int numer; 
    // знаменатель
    int denom; 
    // функция упрощения
    void simplify(); 

public:
    // конструктор по умолчанию
    Rational();       
    // конструктор из целого (преобразующий)
    Rational(int number); 
    // конструктор с двумя аргументами
    Rational(int n, int d);           

    // арифметические операции
    Rational& operator =(const Rational& r);
    Rational& operator +=(const Rational& r); 
    Rational operator +(const Rational& r) const; 
    Rational operator -() const;   
    Rational operator -(const Rational& r) const;
    Rational& operator -=(const Rational& r); 
    Rational& operator *=(const Rational& r);

    // операторы инкремента
    Rational& operator ++(); // префикс
    Rational operator ++(int); // постфикс

    // операторы сравнения
    bool operator ==(const Rational& r) const; 
    bool operator !=(const Rational& r) const; 
    bool operator >(const Rational& r) const;
    bool operator <(const Rational& r) const;
    bool operator >=(const Rational& r) const;
    bool operator <=(const Rational& r) const;

    // Преобразование типов
    operator int() const;  
    operator double() const;

    // Ввод-вывод 
    friend istream& operator >>(istream& in, Rational& r);     
    friend ostream& operator <<(ostream& out, const Rational& r); 
};
