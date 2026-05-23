#include <iostream>
#include <fstream>
#include <string>
#include "DateTime.h"

using namespace std;

// упрощенное форматирование времени ЧЧММСС - ЧЧ:ММ:СС
string formatTime(const string& hms) {
    string t = string(6 - hms.length(), '0') + hms; // добавляем нули слева, если строка короткая
    return t.substr(0, 2) + ":" + t.substr(2, 2) + ":" + t.substr(4, 2);
}

// основная функция обработки астрономических данных Луны для заданной даты
void processMoonData(const DateTime& date) {
    // получаем год в виде строки и конвертируем в число для проверки диапазона
    int yearCheck = stoi(date.getYYYY());

    // проверка границ доступных данных (1998 - 2023)
    if (yearCheck < 1998 || yearCheck > 2023) {
        return;
    }

    // формируем путь к файлу данных (например, "Moon/moon2018.dat")
    string folder = "Moon/";
    string fileName = folder + "moon" + date.getYYYY() + ".dat";

    // открываем файл для чтения
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Ошибка: Файл " << fileName << " не найден!\n";
        return;
    }

    string header;
    getline(file, header); // считываем и пропускаем первую строку файла

    // целевая дата в формате "ГГГГММДД"
    string targetDate = date.getYYYYMMDD();

    // переменные для чтения столбцов из файла
    string ymd, hms;
    double t, r, el, az, fi, lg;

    // результирующие переменные с базовыми значениями на случай, если события не произойдут
    string culminationTime = "No data", riseTime = "Not observed", setTime = "Not observed";
    double maxEl = -999.0;
    double prevEl = -999.0;
    bool dayFound = false;

    // читаем файл построчно
    while (file >> ymd >> hms >> t >> r >> el >> az >> fi >> lg) {
        // проверяем, относится ли строка к выбранному пользователем дню
        if (ymd == targetDate) {
            dayFound = true; // наткнулись на нужный день

            // поиск кульминации (максимальная высота за этот день)
            if (el > maxEl) {
                maxEl = el;
                culminationTime = formatTime(hms);
            }

            // поиск восхода и захода внутри этого дня
            if (prevEl != -999.0) {
                if (prevEl <= 0 && el > 0)  riseTime = formatTime(hms); // восход
                if (prevEl >= 0 && el < 0)  setTime = formatTime(hms);  // заход
            }
        }
        else if (dayFound) {
            // если мы уже обрабатывали нужный день, а сейчас пошел следующий выходим из цикла
            break;
        }

        // сохраняем высоту для следующей итерации
        prevEl = el;
    }
    file.close();

    // если цикл завершился, но флаг dayFound остался false, значит такой даты в файле физически не было
    if (!dayFound) {
        cout << "Данные за указанный день не найдены в файле!\n";
        return;
    }

    // выводим результаты на экран
    date.printMoonResult(riseTime, culminationTime, setTime);
}

int main() {
    setlocale(LC_ALL, ".UTF8");

    // вводим дату
    DateTime userDate;
    userDate.input();

    cout << endl;
    // запускаем расчет лунных эфемерид для введенной даты
    processMoonData(userDate);

    return 0;
}