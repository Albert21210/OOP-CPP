#pragma once
#include <vector>
#include <string>

using namespace std;

// базовый класс для всех функций
class Function {
public:
    virtual ~Function() {} // виртуальный деструктор

    // абстрактные методы
    virtual double calculate(double x) const = 0; // значение f(x)
    virtual std::string getName() const = 0;      // имя функции

    // общие методы
    void printResult(double x) const;
    double findMax(double a, double b, double step = 0.01) const;
    double findMin(double a, double b, double step = 0.01) const;
    double integrate(double a, double b, int n = 1000) const;
    double differentiate(double x, double h = 1e-5) const;
};

// гипербола: k/x + b
class Hiperbola : public Function {
private:
    double k, b;
public:
    Hiperbola(double k, double b) : k(k), b(b) {}
    double calculate(double x) const;
    std::string getName() const { return "Hiperbola"; }
};

// парабола: ax^2 + bx + c
class Parabola : public Function {
private:
    double a, b, c;
public:
    Parabola(double a, double b, double c) : a(a), b(b), c(c) {}
    double calculate(double x) const;
    std::string getName() const { return "Parabola"; }
};

// экспонента: a * e^(bx)
class Exponenta : public Function {
private:
    double a, b;
public:
    Exponenta(double a, double b) : a(a), b(b) {}
    double calculate(double x) const;
    std::string getName() const { return "Exponenta"; }
};