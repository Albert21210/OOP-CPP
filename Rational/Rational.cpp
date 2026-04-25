#include <iostream>
#include "Rational.h"

using namespace std;

// конструктор по умолчанию
Rational::Rational()
{
    numer = 0;
    denom = 1;
}

// конструктор из целого (преобразующий)
Rational::Rational(int number)
{
    numer = number;
    denom = 1;
}

// конструктор с двумя аргументами
Rational::Rational(int n, int d) 
{
    numer = n;
    denom = d;
}

// оператор присваивания
Rational& Rational::operator =(const Rational& r)
{
    this->numer = r.numer;
    this->denom = r.denom;

    return *this;
}


// оператор добавления
Rational& Rational::operator +=(const Rational& r) 
{
    numer = (numer * r.denom + denom * r.numer);
    denom *= r.denom;
    simplify();
    return *this;
}

// оператор умножения
Rational& Rational::operator *=(const Rational& r)
{
    numer = numer * r.numer;
    denom = denom * r.denom;
    simplify();
    return *this;
}

// функция упрощения
void Rational::simplify()
{
    if (denom < 0)
    {
        numer = -numer;
        denom = -denom;
    }
    if (denom == 0)
    {
        return;
    }
    for (int i = 2; i <= abs(denom) && i <= abs(numer); i++)
        if (numer % i == 0 && denom % i == 0)
        {
            numer /= i;
            denom /= i;
            i--;
        }
}

// оператор сложения
Rational Rational::operator +(const Rational& r) const
{
    Rational res(*this);
    // используем готовую операцию добавления
    return res += r;
}

// оператор отрицания (унарный минус)
Rational Rational::operator -() const
{
    Rational r(-numer, denom);
    return r;
}

// оператор вычитания
Rational Rational::operator -(const Rational& r) const
{
    return (*this + (-r));
}

// оператор уменьшения
Rational& Rational::operator -=(const Rational& r)
{
    return (*this += (-r));
}

// префикс
Rational& Rational::operator ++()
{
    numer += denom;
    return *this;
}

// постфикс
Rational Rational::operator ++(int)
{
    Rational r(*this);
    numer += denom;
    return r;
}

// операторы сравнения
bool Rational::operator ==(const Rational& r) const
{
    return (numer == r.numer) && (denom == r.denom);
}

bool Rational::operator !=(const Rational& r) const
{
    return !(*this == r);
}

bool Rational::operator >(const Rational& r) const
{
    return (numer * r.denom) > (r.numer * denom);
}

bool Rational::operator <(const Rational& r) const
{
    return (numer * r.denom) < (r.numer * denom);
}

bool Rational::operator >=(const Rational& r) const
{
    return !(*this > r);
}

bool Rational::operator <=(const Rational& r) const
{
    return !(*this < r);
}

// преобразования типов
Rational::operator int() const
{
    return numer / denom;
}

Rational::operator double() const
{
    return ((double)numer) / denom;
}

// операторы ввода-вывода
istream& operator >>(istream& in, Rational& r)
{
    in >> r.numer >> r.denom;
    return in;
}

ostream& operator <<(ostream& out, const Rational& r)
{
    out << r.numer << "/" << r.denom;
    return out;
}
