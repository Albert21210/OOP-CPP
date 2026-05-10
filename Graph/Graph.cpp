#include <iostream>
#include "Graph.h"

// добавление нового узла
void Graph::addNode(Node* node) {
	nodes.insert(node);
}

// добавление связи с другим узлом
void Node::addNeighbour(Node* neighbour) {
	neighbours.insert(neighbour);
}

// удаление узла из списока соседей
void Node::removeNeighbour(Node* neighbour) {
	neighbours.erase(neighbour);
}

// удаление узла
void Graph::removeNode(Node* node) {
	nodes.erase(node);
	// Remove also from all neighbours list
	for (std::set<Node*>::iterator it = nodes.begin();
		it != nodes.end(); it++) {
		(*it)->removeNeighbour(node);
	}
}

// создание ребра
void Graph::addEdge(Node* begin, Node* end) {
	if (nodes.find(begin) == nodes.end()) // существует ли начальный узел в графе
		return;
	if (nodes.find(end) == nodes.end()) // существует ли конечный узел в графе
		return;
	begin->addNeighbour(end); // добавляем конечный узел в список соседей начального
	end->addNeighbour(begin); // добавляем начальный узел в список соседей конечного
}

// проверка связности через алгоритм поиска в ширину(BFS)
bool BFS::connected(Node* begin, Node* end) {
	// создание очереди для хранения узлов, подлежащих проверке
	std::queue<Node*> nodes; nodes.push(begin);
	std::set<Node*> visited; // создание множества для учета уже посещенных узлов
	// пока очередь не пуста, продолжаем поиск
	while (!nodes.empty()) {
		// берем первый элемент из очереди и удаляем из очереди
		Node* next = nodes.front(); nodes.pop();
		if (end == next) return true;
		visited.insert(next); // помечаем текущий узел как посещенный
		// перебираем всех соседей текущего узла
		for (node_iterator it = next->nb_begin();
			it != next->nb_end(); it++)
			// если сосед еще не был посещен
			if (visited.find(*it) == visited.end())
				nodes.push(*it); // добавляем соседа в очередь на проверку
	}
	return false;
}

// запуск поиска в глубину (DFS)
bool DFS::connected(Node* begin, Node* end) {
	visited.clear(); return connected(begin, end, 0);
}

// рекурсивный поиск в глубину
bool DFS::connected(Node* begin, Node* end, int depth) {
	if (begin == end) return true;
	visited.insert(begin);
	// перебираем всех соседей текущего узла
	for (node_iterator it = begin->nb_begin();
		it != begin->nb_end(); it++) {
		// если сосед еще не был посещен
		if (visited.find(*it) == visited.end()) {
			// рекурсивно переходим к соседу и проверяем путь от него
			if (connected(*it, end, depth + 1)) return true;
		}
	}
	return false;
}