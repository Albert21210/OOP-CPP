#include <iostream>
#include <ctime>
#include "Array.h"

int solveJosephus(int n, int k) {
    Array circle(n);

    for (int i = 1; i <= n; i++) {
        circle.insert(i);
    }

    int currentIndex = 0;
    while (circle.getSize() > 1) {
        currentIndex = (currentIndex + k - 1) % circle.getSize();
        circle.remove(currentIndex);
    }

    return circle[0];
}

int main() {
    setlocale(LC_ALL, "Russian");
    int N_values[] = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };
    int k = 2;

    cout << "N\t\tОтвет\t\tВремя (Сек)" << endl;
    cout << "--------------------------------------------" << endl;

    for (int n : N_values) {
        clock_t start = clock();
        int result = solveJosephus(n, k);
        clock_t end = clock();

        double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        cout << n << "\t\t" << result << "\t\t" << duration << endl;
    }

    return 0;
}