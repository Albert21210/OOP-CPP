#include <iostream>
#include <cmath>
#include "Function.h"

using namespace std;

// вывод результата
void Function::printResult(double x) const {
    cout << getName() << " f(" << x << ") = " << calculate(x) << endl;
}

// поиск максимума
double Function::findMax(double a, double b, double step) const {
    double res = calculate(a);
    // идем от a до b с шагом step
    for (double x = a + step; x <= b; x += step) {
        double val = calculate(x);
        if (val > res) // если нашли значение больше — запоминаем
            res = val;
    }
    return res;
}

// поиск минимума
double Function::findMin(double a, double b, double step) const {
    double res = calculate(a);
    // идем от a до b с шагом step
    for (double x = a + step; x <= b; x += step) {
        double val = calculate(x);
        if (val < res) // если нашли значение меньше — запоминаем
            res = val;
    }
    return res;
}

// интегрирование
double Function::integrate(double a, double b, int n) const {
    double h = (b - a) / n; // ширина одного шага
    double sum = 0.5 * (calculate(a) + calculate(b)); // среднее между первой и последней точкой
    for (int i = 1; i < n; i++)
        sum += calculate(a + i * h);
    return sum * h;
}

// дифференцирование
double Function::differentiate(double x, double h) const {
    return (calculate(x + h) - calculate(x - h)) / (2 * h); // формула центральной разности
}

// реализация математических формул

// гипербола
double Hiperbola::calculate(double x) const {
    return (x != 0) ? k / x + b : 0;
}

// парабола
double Parabola::calculate(double x) const {
    return a * x * x + b * x + c;
}

// экспонента
double Exponenta::calculate(double x) const {
    return a * exp(b * x);
}