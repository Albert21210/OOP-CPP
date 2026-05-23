#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include "Graph.h"

using namespace std;

// сохранение одной компоненты в файл
void saveComponent(const set<Node*>& component, const string& filename) {
    // открываем файл для записи результатов
    ofstream out(filename);
    if (!out.is_open()) return; // если файл не создался, выходим

    // записываем заголовок столбцов для формата таблицы ребер
    out << "Source,Target\n";
    set<pair<int, int>> saved_edges; // множество пар для отслеживания уже сохраненных ребер.

    // проходим по всем вершинам, входящим в данную компоненту связности
    for (Node* node : component) {
        int u = stoi(node->getName()); // конвертируем имя текущей вершины из строки в числовой индекс
        // перебираем всех соседей текущей вершины
        for (Node* nb : node->getNeighbours()) {
            int v = stoi(nb->getName()); // конвертируем имя соседней вершины в число

            // упорядочиваем индексы вершин
            int low = std::min(u, v);
            int high = std::max(u, v);

            // проверяем, записывали ли мы это ребро ранее
            if (!saved_edges.count({ low, high })) {
                out << u << "," << v << "\n";
                saved_edges.insert({ low, high }); // добавляем ребро в список сохраненных
            }
        }
    }
}

// основная функция обработки
void processGraph(const string& input, const string& output_prefix) {
    Graph graph(input);

    // считаем реальное количество загруженных вершин (пропускаем nullptr)
    int valid_nodes_count = 0;
    for (Node* n : graph.getNodes()) if (n != nullptr) valid_nodes_count++;

    // если в графе нет ни одной валидной вершины — файл пуст или не существует
    if (valid_nodes_count == 0) {
        cout << "Файл " << input << " не найден или пуст.\n";
        return;
    }

    BFS bfs;
    set<Node*> visited;
    int count = 0;

    // проходим по всем ячейкам вектора вершин графа
    for (Node* node : graph.getNodes()) {
        // пропускаем пустые ячейки в векторе и уже посещенные вершины
        if (node == nullptr || visited.count(node)) continue;

        count++;
        // запускаем BFS от этой вершины и получаем множество всех связанных с ней узлов
        set<Node*> comp = bfs.getComponent(node);
        visited.insert(comp.begin(), comp.end());

        // формируем уникальное имя файла и сохраняем туда компоненту
        saveComponent(comp, output_prefix + "_res_comp_" + to_string(count) + ".txt");
        cout << "[" << input << "] Компонента #" << count << ": " << comp.size() << " узлов.\n";
    }
    cout << "Итого  " << input << ": Компонентов: " << count << "\n\n";
}

int main() {
    setlocale(LC_ALL, ".UTF8");
    // обрабатываем последовательно два файла графов
    processGraph("testgraph.txt", "testgraph"); // маленький тестовый граф
    processGraph("1000.csv", "1000"); // большой граф на 1000+ элементов

    cout << "Готово! Нажмите Enter для выхода...";
    cin.get();
    return 0;
}