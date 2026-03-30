#include "rational.h"
#include <cmath> 

// Конструктор по умолчанию
Rational::Rational() {
    numer = 0;
    denom = 1;
}

// Преобразующий конструктор
Rational::Rational(int number) {
    numer = number;
    denom = 1;
}

// Конструктор с параметрами 
Rational::Rational(int n, int d) {
    numer = n;
    denom = d;
}

// Оператор += 
Rational& Rational::operator +=(const Rational& r) {
    numer = (numer * r.denom + denom * r.numer);
    denom *= r.denom;
    simplify();
    return *this;
}

// Функция упрощения дроби
void Rational::simplify() {
    if (denom < 0) {
        numer = -numer;
        denom = -denom;
    }
    for (int i = 2; i <= abs(denom) && i <= abs(numer); i++) {
        if (numer % i == 0 && denom % i == 0) {
            numer /= i;
            denom /= i;
            i--;
        }
    }
}

// Оператор + (бинарный) 
Rational Rational::operator +(const Rational& r) const {
    Rational res(*this);
    return res += r;
}

// Унарный минус
Rational Rational::operator -() const {
    Rational r(-numer, denom);
    return r;
}

Rational Rational::operator -(const Rational& r) const {
    Rational res(*this);
    return res += (-r);
}

// Оператор -= 
Rational& Rational::operator -=(const Rational& r) {
    return (*this += (-r));
}

// Оператор *
Rational Rational::operator *(const Rational& r) const {
    return Rational(numer * r.numer, denom * r.denom);
}

// Оператор /
Rational Rational::operator /(const Rational& r) const {
    return Rational(numer * r.denom, denom * r.numer);
}

// Префиксный инкремент 
Rational& Rational::operator ++() {
    numer += denom;
    return *this;
}

// Постфиксный инкремент 
Rational Rational::operator ++(int) {
    Rational r(*this);
    numer += denom;
    return r;
}

// Сравнение на равенство 
bool Rational::operator ==(const Rational& r) const {
    return (numer == r.numer) && (denom == r.denom);
}

// Сравнение на неравенство 
bool Rational::operator !=(const Rational& r) const {
    return !(*this == r);
}

// Преобразование в int 
Rational::operator int() const {
    return numer / denom;
}

// Преобразование в double 
Rational::operator double() const {
    return ((double)numer) / denom;
}

// Оператор ввода 
istream& operator >>(istream& in, Rational& r) {
    in >> r.numer >> r.denom;
    r.simplify();
    return in;
}

// Оператор вывода
ostream& operator <<(ostream& out, const Rational& r) {
    out << r.numer << "/" << r.denom;
    return out;
}