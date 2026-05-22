#pragma once
#include <vector>
#include <string>

using namespace std;

// структура для хранения координат точки на двумерной сетке (X — столбец, Y — строка)
struct Point {
    int x, y;
};

// структура для представления одного пикселя в формате BGR
struct Pixel {
    unsigned char b, g, r; // Байты синего, зеленого и красного каналов
}

// класс для решения и сохранения лабиринта из BMP
class Labirint {
private:
    int width{ 0 };            // ширина изображения в пикселях
    int height{ 0 };           // высота изображения в пикселях
    int bytesPerPixel{ 3 };    // количество байт на один пиксель

    // буфер для хранения сырых байт заголовков BMP
    vector<unsigned char> headerBuffer;

    // двумерный массив пикселей, представляющий исходную картинку
    vector<vector<Pixel>> pixels;

    // двумерный числовой массив для логического представления лабиринта (0 - проход, 1 - стена)
    vector<vector<int>> grid;

    Point startPoint{ -1, -1 }; // координаты точки старта (зеленый пиксель)
    Point endPoint{ -1, -1 };   // координаты точки финиша (красный пиксель)

    // проверяет, является ли пиксель стеной
    bool isWall(Pixel p) { return (p.r < 50 && p.g < 50 && p.b < 50); }

    // проверяет, является ли пиксель стартом 
    bool isStart(Pixel p) { return (p.g > 150 && p.r < 100 && p.b < 100); }

    // проверяет, является ли пиксель финишем
    bool isEnd(Pixel p) { return (p.r > 150 && p.g < 100 && p.b < 100); }

public:
    // метод загрузки лабиринта из BMP-файла
    bool loadFromBMP(const std::string& filename);

    // метод поиска пути в лабиринте от startPoint до endPoint
    bool solve();

    // метод сохранения решенного лабиринта обратно в BMP-файл
    bool saveToBMP(const std::string& filename);
};