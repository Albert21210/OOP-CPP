#include "Graph.h"
#include <sstream>
#include <fstream>

using namespace std;

// получение узла по его числовому индексу (автоматически расширяем вектор)
Node* Graph::getOrCreateNode(int idx) {
    // если переданный индекс выходит за границы текущего размера вектора
    if (idx >= nodes.size()) {
        nodes.resize(idx + 1, nullptr); // увеличиваем размер вектора так, чтобы индекс idx стал валидным.
    }
    // если в ячейке с данным индексом еще нет созданного объекта Node
    if (nodes[idx] == nullptr) {
        nodes[idx] = new Node(std::to_string(idx)); // выделяем память под новый узел
    }
    return nodes[idx]; // Возвращаем указатель на узел
}

// Создание ребра между двумя узлами по их индексам
void Graph::addEdge(int src_idx, int tgt_idx) {
    // получаем или создаем указатели на исходный и целевой узлы
    Node* u = getOrCreateNode(src_idx);
    Node* v = getOrCreateNode(tgt_idx);
    // добавляем узел v в список соседей узла u, а узел u — в список соседей узла v.
    u->neighbours.insert(v);
    v->neighbours.insert(u);
}

// чистим динамическую память
Graph::~Graph() {
    for (Node* node : nodes) {
        if (node != nullptr) delete node;
    }
}

// конструктор класса Graph: считывает структуру графа из текстового файла
Graph::Graph(const std::string& file_name) {
    // открываем файл для чтения
    ifstream file(file_name);
    if (!file.is_open()) return;

    std::string line;
    // построчно читаем весь файл до конца
    while (getline(file, line)) {
        // пропускаем пустые строки, а также строки заголовков, содержащие "Source" или "source"
        if (line.empty() || line.find("Source") != std::string::npos || line.find("source") != std::string::npos) {
            continue;
        }

        // Заменяем любые запятые на пробелы для удобства чтения чисел
        for (char& ch : line) if (ch == ',') ch = ' ';

        // создаем строковый поток для парсинга чисел из текущей обработанной строки
        stringstream ss(line);
        int src, tgt;
        // если успешно считали два целых числа
        if (ss >> src >> tgt) {
            addEdge(src, tgt); // создаем ребро между ними
        }
    }
}

// метод поиска компоненты связности с помощью алгоритма обхода в ширину (BFS)
set<Node*> BFS::getComponent(Node* start) {
    set<Node*> component{ start };
    // очередь q используется для управления порядком обхода вершин в ширину
    queue<Node*> q;
    q.push(start);

    // работаем, пока в очереди есть вершины для обработки
    while (!q.empty()) {
        Node* curr = q.front(); // достаем текущую вершину из начала очереди
        q.pop();

        // проходим по всем соседям текущей вершины curr
        for (Node* neighbour : curr->getNeighbours()) {
            // если соседний узел еще НЕ был посещен
            if (!component.count(neighbour)) {
                component.insert(neighbour); // отмечаем его как посещенный (добавляем в компоненту)
                q.push(neighbour);
            }
        }
    }
    // возвращаем множество всех вершин, входящих в данную компоненту связности
    return component;
}