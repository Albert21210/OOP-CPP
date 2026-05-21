#include <iostream>
#include "GeomFigury.h"

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");

    // создаем список фигур через указатели на базовый класс Shape
    vector<Shape*> list;
    list.push_back(new Circle(Point(0, 0), 5));
    list.push_back(new Rectangle(10, 4));
    list.push_back(new Triangle(3, 4, 5));
    list.push_back(new Ellipse(Point(0, 0), 6, 3));

    // тестируем каждую фигуру в цикле
    for (Shape* s : list) {
        s->name();
        cout << "Площадь: " << s->calc_area() << endl;
        cout << "Периметр: " << s->calc_perimetr() << endl << endl;
    }

    // чистим память
    for (Shape* s : list) {
        delete s;
    }

    return 0;
}
