#include <iostream>
#include "rational.h"
#include <cmath>

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");

    // Коэффициенты уравнения: 1x^2 - 5x + 6 = 0
    Rational a(1), b(-5), c(6);
    Rational four(4), two(2);

    cout << "Уравнение: (" << a << ")x^2 + (" << b << ")x + (" << c << ") = 0" << endl;

    // D = b^2 - 4ac
    Rational D = (b * b) - (four * a * c);

    cout << "Дискриминант D = " << D << endl;

    double d_val = (double)D;

    if (d_val < 0) {
        cout << "Корней нет (D < 0)" << endl;
    }
    else {
        double sqrt_d = sqrt(d_val);

        // Проверяем, является ли корень рациональным
        if (floor(sqrt_d) == sqrt_d) {
            Rational sqrtD_rat((int)sqrt_d);

            // x1 = (-b + sqrt(D)) / 2a
            Rational x1 = (-b + sqrtD_rat) / (two * a);
            // x2 = (-b - sqrt(D)) / 2a
            Rational x2 = (-b - sqrtD_rat) / (two * a);

            cout << "Корень x1 = " << x1 << endl;
            cout << "Корень x2 = " << x2 << endl;
        }
        else {
            cout << "Корень из дискриминанта иррационален (sqrt(" << d_val << ")). "
                << "Класс Rational не может представить такой результат точно." << endl;
        }
    }

    return 0;
}
