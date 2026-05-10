#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    // тестируем
    setlocale(LC_ALL, "Russian");
    // создаем объект класса Graph
    Graph g;
    // динамическое выделение памяти для создания трех узлов
    Node* n1 = new Node("A");
    Node* n2 = new Node("B");
    Node* n3 = new Node("C");

    // регистрируем созданные узлы в объекте графа
    g.addNode(n1);
    g.addNode(n2);
    g.addNode(n3);

    // создаем связи между узлами: A соединяем с B, B соединяем с C
    g.addEdge(n1, n2);
    g.addEdge(n2, n3);

    // создаем объекты для выполнения алгоритмов поиска, привязанных к графу g
    BFS bfs(g);
    DFS dfs(g);

    // проверяем связность узлов A и C с помощью поиска в ширину и вывод результата (Yes/No)
    cout << "BFS (A to C): " << (bfs.connected(n1, n3) ? "Yes" : "No") << endl;
    // проверяем связность узлов A и C с помощью поиска в глубину и вывод результата (Yes/No)
    cout << "DFS (A to C): " << (dfs.connected(n1, n3) ? "Yes" : "No") << endl;

    // освобождаем динамическую память, выделенную под узлы
    delete n1; delete n2; delete n3;
    return 0;
}