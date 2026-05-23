#pragma once
#include <iostream>
#include <set>
#include <queue>
#include <vector>

using namespace std;

// предварительное обьявление класса графа
class Graph;

// узел
class Node {
    std::string name; // имя узла
    set<Node*> neighbours; // множество смежных узлов (соседи)	
public:
    // конструктор: создание узла заданным именем
    Node(const std::string& aname) : name(aname) {}
    // получение имени текущего узла
    const std::string& getName() const { return name; }
    // метод получения ссылки на множество соседей узла
    const set<Node*>& getNeighbours() const { return neighbours; }
    // разраешаем классу Graph доступ к приватным методам Node
    friend class Graph;
};

// граф
class Graph {
    vector<Node*> nodes; // динамический массив указателей на все вершины, существующие в графе
public:
    // конструктор: создает граф, считывая его структуру из текстового файла
    Graph(const std::string& file_name);
    // деструктор
    ~Graph();
    // метод для добавления ребра между двумя вершинами графа по их индексам
    void addEdge(int src_idx, int tgt_idx);
    // возвращает указатель на существующий узел по индексу, либо автоматически создает новый узел
    Node* getOrCreateNode(int idx);
    // Метод получения ссылки на вектор всех вершин графа
    const vector<Node*>& getNodes() const { return nodes; }
};

// класс для реализации алгоритма поиска в ширину (Breadth-First Search)
class BFS {
public:
    // метод для поиска компоненты связности.
    set<Node*> getComponent(Node* start);
};