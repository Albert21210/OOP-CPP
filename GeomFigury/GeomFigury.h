#pragma once
#include <iostream>

// точка
class Point {
public:
    double x, y;
    Point(double x = 0, double y = 0);
};

double dist(Point a, Point b);

// базовый класс фигуры
class Shape {
public:
    virtual double calc_area() = 0;
    virtual double calc_perimetr() = 0;
    virtual void name() = 0;
};

// круг
class Circle : public Shape {
private:
    Point c;
    double r;
public:
    Circle(Point c, double r);
    double calc_area();
    double calc_perimetr();
    void name();
};

// эллипс
class Ellipse : public Shape {
private:
    Point c;
    double a, b;
public:
    Ellipse(Point c, double a, double b);
    double calc_area();
    double calc_perimetr();
    void name();
};

// треугольник
class Triangle : public Shape {
private:
    double a, b, c;
public:
    Triangle(double a, double b, double c);
    double calc_area();
    double calc_perimetr();
    void name();
};

// прямоугольник
class Rectangle : public Shape {
private:
    double w, h;
public:
    Rectangle(double w, double h);
    double calc_area();
    double calc_perimetr();
    void name();
};