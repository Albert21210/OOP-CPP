#include <iostream>
#include "LineList.h"

using namespace std;

int main(void) {
    // Тестируем
    setlocale(LC_ALL, ".UTF8");

    // Использование класса
    LineList<int> list;

    cout << "Начало: " << list << endl;

    // Вставка элементов
    list.insertFirst(10);
    LineListElem<int>* ptr = list.getStart();

    list.insertAfter(ptr, 15);
    list.insertAfter(ptr->getNext(), 12);
    list.insertFirst(7);

    cout << "Шаг 1: " << list << endl;

    // Нахождение суммы
    int sum = 0;
    // Используем переменную-итератор
    for (LineListElem<int>* it = list.getStart(); it; it = it->getNext()) {
        sum += it->getData();
    }

    cout << "Сумма = " << sum << endl;

    return 0;
}