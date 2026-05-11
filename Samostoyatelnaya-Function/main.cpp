#include <iostream>
#include <vector>
#include "Function.h"

using namespace std;

int main() {
    // cоздаем список функций 
    vector<Function*> list;
    list.push_back(new Hiperbola(10, 2));      // y = 10/x + 2
    list.push_back(new Parabola(1, -2, 1));    // y = 1 * x ^ 2 - 2 * x + 1
    list.push_back(new Exponenta(1, 0.5));     // y = 1 * e ^ (0.5x)

    // тестируем каждую функцию в цикле
    for (Function* f : list) {
        f->printResult(1.5);
        cout << "Min [0, 2]: " << f->findMin(0, 2) << endl;
        cout << "Max [0, 2]: " << f->findMax(0, 2) << endl;
        cout << "Int [0, 2]: " << f->integrate(0, 2) << endl;
        cout << "Diff (1.5): " << f->differentiate(1.5) << endl << endl;
    }

    // очистка памяти
    for (Function* f : list) delete f;

    return 0;
}