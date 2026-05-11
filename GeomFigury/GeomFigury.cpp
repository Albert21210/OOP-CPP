#include <iostream>
#include <cmath>
#include "GeomFigury.h"

using namespace std;

const double PI = 3.1415926535;

// точка
Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// круг
Circle::Circle(Point c, double r) {
    this->c = c;
    this->r = r;
}

double Circle::calc_area() {
    return PI * r * r;
}

double Circle::calc_perimetr() {
    return 2 * PI * r;
}

void Circle::name() {
    cout << "Circle\n";
}

// эллипс
Ellipse::Ellipse(Point c, double a, double b) {
    this->c = c;
    this->a = a;
    this->b = b;
}

double Ellipse::calc_area() {
    return PI * a * b;
}

double Ellipse::calc_perimetr() {
    return PI * (a + b);
}

void Ellipse::name() {
    cout << "Ellipse\n";
}

// треугольник
Triangle::Triangle(double a, double b, double c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

double Triangle::calc_area() {
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

double Triangle::calc_perimetr() {
    return a + b + c;
}

void Triangle::name() {
    cout << "Triangle\n";
}

// прямоугольник
Rectangle::Rectangle(double w, double h) {
    this->w = w;
    this->h = h;
}

double Rectangle::calc_area() {
    return w * h;
}

double Rectangle::calc_perimetr() {
    return 2 * (w + h);
}

void Rectangle::name() {
    cout << "Rectangle\n";
}
