#include <iostream>
#include "GeomFigury.h"

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");
    // создаем обьекты фигур
    Circle c(Point(0, 0), 5);
    Rectangle r(10, 4);
    Triangle t(3, 4, 5);
    Ellipse e(Point(0, 0), 6, 3);

    // круг
    c.name();
    cout << "Площадь: " << c.calc_area() << endl;
    cout << "Периметр: " << c.calc_perimetr() << endl << endl;

    // прямоугольник
    r.name();
    cout << "Площадь: " << r.calc_area() << endl;
    cout << "Периметр: " << r.calc_perimetr() << endl << endl;

    // треугольник
    t.name();
    cout << "Площадь: " << t.calc_area() << endl;
    cout << "Периметр: " << t.calc_perimetr() << endl << endl;

    // эллипс
    e.name();
    cout << "Площадь: " << e.calc_area() << endl;
    cout << "Периметр: " << e.calc_perimetr() << endl << endl;

    return 0;
}