#pragma once
#include <iostream>

using namespace std;

class LineListException {};

// Элемент списка
template <class T> class LineListElem 
{
    T data;
    LineListElem* next;
public:
    LineListElem(const T& adata, 
        LineListElem* anext) {
        data = adata;
        next = anext;
    }
    const T& getData() const {
        return data; 
    }
    LineListElem* getNext() { 
        return next; 
    }

    template <class T> friend class LineList;
};

// Список
template <class T> class LineList {
    LineListElem<T>* start;

    // Копирование
    LineList(const LineList& list);
    LineList& operator =(const LineList& list);

public:
    LineList() {
        start = 0;
    }

    ~LineList() {
        while (start) {
            deleteFirst();
        }
    }

    LineListElem<T>* getStart() {
        return start;
    }

    void deleteFirst() {
        if (start) {
            LineListElem<T>* temp = start->next;
            delete start;
            start = temp;
        }
        else throw LineListException();
    }

    void deleteAfter(LineListElem<T>* ptr) {
        if (ptr && ptr->next) {
            LineListElem<T>* temp = ptr->next;
            ptr->next = ptr->next->next;
            delete temp;
        }
        else throw LineListException();
    }

    void insertFirst(const T& data) {
        LineListElem<T>* second = start;
        start = new LineListElem<T>(data, second);
    }

    void insertAfter(LineListElem<T>* ptr, const T& data) {
        if (ptr) {
            LineListElem<T>* temp = ptr->next;
            ptr->next = new LineListElem<T>(data, temp);
        }
    }

    // Оператор вывода
    template <class T> friend ostream& operator<<(ostream& out, const LineList<T>& list) {
        LineListElem<T>* ptr = list.start;
        if (!ptr)
            out << "EMPTY ";
        else {
            while (ptr) {
                out << ptr->getData() << " ";
                ptr = ptr->getNext();
            }
        }
        return out; 
    }
};
