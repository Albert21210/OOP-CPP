#include <iostream>
#include <ctime>
#include "Array.h"

using namespace std;

int main() {
    int values[] = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };
    int k = 2;

    cout << "N\t\tOtvet\t\tVremya (sec)" << endl;
    cout << "--------------------------------------------" << endl;

    for (int n : values) {
        clock_t start = clock();
        int result = Josephus(n, k);
        clock_t end = clock();

        double duration = (double)(end - start) / CLOCKS_PER_SEC;
        cout << n << "\t\t" << result << "\t\t" << duration << endl;
    }

    return 0;
}