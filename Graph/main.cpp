#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    Graph g;
    Node* n1 = new Node("A");
    Node* n2 = new Node("B");
    Node* n3 = new Node("C");

    g.addNode(n1);
    g.addNode(n2);
    g.addNode(n3);

    g.addEdge(n1, n2);
    g.addEdge(n2, n3);

    BFS bfs(g);
    DFS dfs(g);

    cout << "BFS (A to C): " << (bfs.connected(n1, n3) ? "Yes" : "No") << endl;
    cout << "DFS (A to C): " << (dfs.connected(n1, n3) ? "Yes" : "No") << endl;

    delete n1; delete n2; delete n3;
    return 0;
}