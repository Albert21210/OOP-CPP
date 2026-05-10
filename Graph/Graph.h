#pragma once
#include <iostream>
#include <set>
#include <queue>

// предварительное обьявление класса узла
class Node;
// определение типа итератора для удобного обхода множества указателей на узлы
typedef std::set<Node*>::const_iterator
node_iterator;

// граф
class Graph {
	std::set<Node*> nodes; // множество всех узлов
public:
	// добавление нового узла
	void addNode(Node* node);
	// удаление узла
	void removeNode(Node* node);
	// создание ребра
	void addEdge(Node* begin, Node* end);
	// итератор на первый узел
	node_iterator begin() const {
		return nodes.begin();
	}

	// получение итератора, указывающего на конец множества узлов
	node_iterator end() const { return nodes.end(); }
};

// узел		
class Node {
	std::string name; // имя узла
	std::set<Node*> neighbours; // множество смежных узлов (соседи)	
	// добавление связи с другим узлом
	void addNeighbour(Node* neighbour);
	// удаление узла из списока соседей
	void removeNeighbour(Node* neighbour);
public:
	// конструктор: создание узла заданным именем
	Node(const std::string& aname) : name(aname) {}
	// получение имени текущего узла
	const std::string& getName() const { return name; }
	// итератор, указывающий на первого соседа в списке смежности
	node_iterator nb_begin() const {
		return neighbours.begin();
	}
	// итератор, указывающий на элемент за последним соседом
	node_iterator nb_end() const { return neighbours.end(); }
	// разраешаем классу Graph доступ к приватным методам Node
	friend class Graph;
};

// класс для реализации алгоритма поиска в ширину (Breadth-First Search)
class BFS {
	const Graph& graph; // ссылка на граф, в котором будет производиться поиск
public:
	// конструктор: связывает объект BFS с конкретным графом
	BFS(const Graph& agraph) : graph(agraph) {}
	// метод проверки связности двух узлов
	bool connected(Node* begin, Node* end);
};

// класс для реализации алгоритма поиска в глубину (Depth-First Search)
class DFS {
	const Graph& graph; // ссылка на исследуемый граф
	std::set<Node*> visited; // вспомогательное множество для хранения уже посещенных узлов
	// внутренний рекурсивный метод поиска с учетом текущей глубины рекурсии
	bool connected(Node* begin, Node* end, int depth);
public:
	// конструктор: связывает объект DFS с конкретным графом
	DFS(const Graph& agraph) : graph(agraph) {}
	// метод для запуска проверки наличия пути между узлами
	bool connected(Node* begin, Node* end);
};