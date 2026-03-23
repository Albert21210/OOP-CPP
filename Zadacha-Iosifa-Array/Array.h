#pragma once

class Array {
private:
    int* data;
    int size;
    int capacity;

public:
    Array(int startCapacity = 5);
    ~Array();

    void add(int value);
    void removeAt(int index);
    int& operator[](int index);
    int getSize() const;
};

int Josephus(int n, int k);