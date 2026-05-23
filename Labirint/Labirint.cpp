#include "Labirint.h"
#include <iostream>
#include <fstream>

using namespace std;

// метод загрузки лабиринта из BMP-файла
bool Labirint::loadFromBMP(const std::string& filename) {
    // открываем файл в бинарном режиме для чтения
    ifstream file(filename, ios::binary);
    if (!file.is_open()) return false;

    // выделяем память под стандартный заголовок BMP (54 байта) и считываем его
    headerBuffer.resize(54);
    file.read(reinterpret_cast<char*>(headerBuffer.data()), 54);

    // проверяем сигнатуру BMP-файла (магические байты должны быть 'B' и 'M')
    if (headerBuffer[0] != 'B' || headerBuffer[1] != 'M') {
        cerr << "Это не BMP файл!" << endl;
        return false;
    }

    // извлекаем метаданные изображения из заголовка по стандартным смещениям:

    // ширина картинки
    width = *reinterpret_cast<int*>(&headerBuffer[18]);
    // высота картинки. 
    height = std::abs(*reinterpret_cast<int*>(&headerBuffer[22]));
    // количество бит на пиксель 
    bytesPerPixel = *reinterpret_cast<short*>(&headerBuffer[28]) / 8;

    // формат BMP требует, чтобы длина каждой строки в байтах была кратна 4
   
    // формула округляет размер строки вверх до ближайшего числа, кратного 4
    int rowSize = (width * bytesPerPixel + 3) & ~3;
    // вычисляем количество мусорных байт (отступа), добавленных в конец строки для выравнивания
    int padding = rowSize - (width * bytesPerPixel);

    // изменяем размеры матриц под фактическое разрешение картинки
    pixels.resize(height, vector<Pixel>(width));
    grid.resize(height, vector<int>(width, 0)); // 0 означает свободный проход

    // указывает, с какого байта от начала файла начинаются сами пиксели
    int offsetData = *reinterpret_cast<int*>(&headerBuffer[10]);
    // перемещаем файловый указатель к началу блока пикселей
    file.seekg(offsetData, ios::beg);

    // попиксельно считываем матрицу изображения (снизу вверх, слева направо)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Pixel p;
            // BMP хранит цвета в обратном порядке: Blue, Green, Red
            file.read(reinterpret_cast<char*>(&p.b), 1);
            file.read(reinterpret_cast<char*>(&p.g), 1);
            file.read(reinterpret_cast<char*>(&p.r), 1);

            // если картинка 32-битная (BGRA), пропускаем 4-й байт прозрачности (альфа-канал)
            if (bytesPerPixel == 4) {
                file.seekg(1, ios::cur);
            }

            // записываем считанный пиксель в массив
            pixels[y][x] = p;

            // анализируем цвет пикселя для построения логической сетки (grid)
            if (isWall(p)) {
                grid[y][x] = -1; // -1 обозначает непроходимую стену
            }
            else {
                // если это проход, проверяем, не является ли он стартом или финишем
                if (isStart(p)) startPoint = { x, y };
                if (isEnd(p)) endPoint = { x, y };
            }
        }
        // если в конце строки есть байты выравнивания, перешагиваем через них
        if (padding > 0) file.seekg(padding, ios::cur);
    }
    file.close();

    // метод успешен, если были найдены обе критические точки — старт и финиш
    return (startPoint.x != -1 && endPoint.x != -1);
}

// метод поиска пути в лабиринте от startPoint до endPoint
bool Labirint::solve() {
    // массивы смещений для перемещения по 4 направлениям (вверх, вниз, влево, вправо)
    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

    // сохраняем всю историю обхода, что может пригодиться для отладки
    vector<Point> q;
    size_t head = 0; // индекс, эмулирующий извлечение (pop) элемента из начала очереди

    // добавляем точку старта в очередь
    q.push_back(startPoint);
    grid[startPoint.y][startPoint.x] = 1; // стартовая ячейка получает значение волны = 1

    bool found = false;

    // распространение волны (BFS)
    while (head < q.size()) {
        Point curr = q[head]; // достаем текущую точку из "головы" очереди
        head++; // сдвигаем указатель (имитируем удаление из очереди)

        // если дошли до финиша, останавливаем алгоритм
        if (curr.x == endPoint.x && curr.y == endPoint.y) {
            found = true;
            break;
        }

        // проверяем всех 4-х соседей текущей ячейки
        for (int i = 0; i < 4; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            // проверка на корректность координат (не вышли ли за границы картинки)
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                // если ячейка еще не посещена и не является стеной (значение в grid равно 0)
                if (grid[ny][nx] == 0) {
                    // записываем в ячейку длину пути: значение текущей ячейки + 1
                    grid[ny][nx] = grid[curr.y][curr.x] + 1;
                    q.push_back({ nx, ny }); // добавляем соседа в конец очереди
                }
            }
        }
    }

    // если волна не дошла до финиша, значит пути не существует
    if (!found) return false;

    // восстановление пути (обратный ход)
    Point curr = endPoint;
    // идем обратно от финиша к старту, ориентируясь на уменьшение значений в grid
    while (curr.x != startPoint.x || curr.y != startPoint.y) {

        // красим пройденный пиксель (за исключением самого финиша, чтобы сохранить его цвет)
        if (!(curr.x == endPoint.x && curr.y == endPoint.y)) {
            // {255, 0, 0} в формате BGR — это чистый синий цвет (B=255, G=0, R=0)
            pixels[curr.y][curr.x] = { 255, 0, 0 };
        }

        int currVal = grid[curr.y][curr.x];

        // ищем среди соседей ячейку, значение которой строго на 1 меньше текущей
        for (int i = 0; i < 4; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                if (grid[ny][nx] == currVal - 1) {
                    curr = { nx, ny }; // переходим в эту ячейку
                    break; // переходим к следующему шагу внешнего цикла while
                }
            }
        }
    }
    return true;
}

// метод сохранения решенного лабиринта обратно в BMP-файл
bool Labirint::saveToBMP(const std::string& filename) {
    // открываем файл для записи в бинарном режиме
    ofstream file(filename, ios::binary);
    if (!file.is_open()) return false;

    // записываем сохраненный при чтении заголовок, чтобы сохранить исходную структуру
    file.write(reinterpret_cast<char*>(headerBuffer.data()), headerBuffer.size());

    // пересчитываем выравнивание строк до кратности 4 байтам
    int rowSize = (width * bytesPerPixel + 3) & ~3;
    int padding = rowSize - (width * bytesPerPixel);

    unsigned char padByte = 0;   // байт-заполнитель для паддинга (обычно 0)
    unsigned char alphaByte = 255; // дефолтный байт непрозрачности (для 32-битных изображений)

    // построчно записываем измененную матрицу пикселей обратно в файл
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // пишем цветовые каналы в строго фиксированном порядке: B, G, R
            file.write(reinterpret_cast<char*>(&pixels[y][x].b), 1);
            file.write(reinterpret_cast<char*>(&pixels[y][x].g), 1);
            file.write(reinterpret_cast<char*>(&pixels[y][x].r), 1);

            // если исходный файл поддерживал альфа-канал, дописываем байт непрозрачности
            if (bytesPerPixel == 4) {
                file.write(reinterpret_cast<char*>(&alphaByte), 1);
            }
        }
        // в конце каждой строки дописываем необходимое количество пустых байт выравнивания
        for (int p = 0; p < padding; ++p) {
            file.write(reinterpret_cast<char*>(&padByte), 1);
        }
    }
    file.close();
    return true;
}
