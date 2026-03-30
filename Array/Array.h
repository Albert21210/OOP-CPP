#pragma once

#include <iostream>

using namespace std;

// Исключение для обработки ошибок индексации 
class ArrayException {};

const int DEFAULT_CAPACITY = 10;

class Array {
private:
    int* ptr;
    int size;
    int capacity;
 
    void increaseCapacity(int newCapacity);

public:
    // Конструктор с аргументом по умолчанию
    explicit Array(int startCapacity = DEFAULT_CAPACITY);

    // Деструктор 
    ~Array();

    // Конструктор копирования
    Array(const Array& arr);

    // Оператор присваивания 
    Array& operator =(const Array& arr);

    // Операторы индексации 
    int operator [](int index) const;
    int& operator [](int index);

    // Функции вставки
    void insert(int elem, int index);
    void insert(int elem);

    // Функция удаления 
    void remove(int index);

    // Вспомогательные функции 
    int getSize() const;
    friend ostream& operator <<(ostream& out, const Array& arr);
};
