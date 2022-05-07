#pragma once
#include <iostream>
#include <vector>
#include <list>
using namespace std;

template<typename VertexType, typename EdgeType>
class Graph {
protected:
	vector<VertexType*> vertexVector;
	bool directed; // Ориентированный или неориентированный
	bool listGraph; // List-Граф или Matrix-Граф
	int amountOfEdges; // Количество рёбер

public:
	virtual VertexType* insertVertex(int index) = 0;
	VertexType* getVertexByIndex(int index);
	template<typename VertexNameType> VertexType* getVertexByName(VertexNameType name);
	int getVertexIndex(VertexType* vertex);
	virtual bool deleteVertex(int index) = 0;

	virtual bool insertEdge(int v1, int v2, EdgeType* t) = 0;
	virtual EdgeType* getEdge(int v1, int v2) = 0;
	virtual bool hasEdge(int v1, int v2) = 0;
	virtual bool deleteEdge(int v1, int v2) = 0;

	virtual void print(bool printWithNames) = 0;

	double saturationCoefficient();
	bool isDirected();
	bool isListGraph();
	int getAmountOfVertices();
	int getAmountOfEdges();
};

template<typename VertexType, typename EdgeType>
inline VertexType* Graph<VertexType, EdgeType>::getVertexByIndex(int index) {
	if (index < 0 || index >= vertexVector.size())
		throw "Выход индекса за пределы вектора";

	return vertexVector[index];
}

template<typename VertexType, typename EdgeType>
template<typename VertexNameType>
inline VertexType* Graph<VertexType, EdgeType>::getVertexByName(VertexNameType name) {
	VertexType* vertexToFind = nullptr;

	for (auto vertex : vertexVector) {
		if (vertex->getName() == name) {
			vertexToFind = vertex;
			break;
		}
	}

	if (vertexToFind == nullptr)
		throw "Вершины не существует";

	return vertexToFind;
}

template<typename VertexType, typename EdgeType>
inline int Graph<VertexType, EdgeType>::getVertexIndex(VertexType* vertex) {
	int index = -1;

	for (int i = 0; i < vertexVector.size(); i++) {
		if (vertexVector[i] == vertex) {
			index = i;
			break;
		}
	}

	return index;
}

template<typename VertexType, typename EdgeType>
inline double Graph<VertexType, EdgeType>::saturationCoefficient() {
	if (amountOfEdges == 0 || getAmountOfVertices() == 0)
		return 0;

	double max = vertexVector.size() * (vertexVector.size() - 1);

	if (!directed)
		max /= 2;

	return (double)amountOfEdges / max;
}

template<typename VertexType, typename EdgeType>
inline bool Graph<VertexType, EdgeType>::isDirected() {
	return directed;
}

template<typename VertexType, typename EdgeType>
inline bool Graph<VertexType, EdgeType>::isListGraph() {
	return listGraph;
}

template<typename VertexType, typename EdgeType>
inline int Graph<VertexType, EdgeType>::getAmountOfVertices() {
	return vertexVector.size();
}

template<typename VertexType, typename EdgeType>
inline int Graph<VertexType, EdgeType>::getAmountOfEdges() {
	return amountOfEdges;
}



template<typename VertexType, typename EdgeType>
class ListGraph : public Graph<VertexType, EdgeType> {
private:
	vector<list<EdgeType*>> adjacencyList; // Списки смежности

public:
	ListGraph(bool directed);

	VertexType* insertVertex(int index);
	bool deleteVertex(int index);

	bool insertEdge(int v1, int v2, EdgeType* newEdge);
	EdgeType* getEdge(int v1, int v2);
	bool hasEdge(int v1, int v2);
	bool deleteEdge(int v1, int v2);

	void print(bool printWithNames);

	class EdgeIterator {
	private:
		ListGraph<VertexType, EdgeType>* graph;
		typename list<EdgeType*>::iterator it;
		int listIndex;
		bool onEnd;

	public:
		EdgeIterator() {}

		EdgeIterator(ListGraph* graph) {
			this->graph = graph;
			begin();
		}

		bool begin() {
			if (graph->getAmountOfEdges() != 0) {
				for (listIndex = 0; listIndex < graph->adjacencyList.size(); listIndex++) {
					// Ищем первое попавшееся ребро
					for (it = graph->adjacencyList[listIndex].begin();
						 it != graph->adjacencyList[listIndex].end();
						 it++) {
						if (*it) {
							onEnd = false;
							return true;
						}
					}
				}
			}
			else
				throw "В графе отсутствуют ребра";

			onEnd = true;
			return false;
		}

		bool operator++(int) {
			if (onEnd)
				return false;

			for (it++; listIndex < graph->adjacencyList.size(); listIndex++) {
				for (; it != graph->adjacencyList[listIndex].end(); it++) {
					if (*it) {
						onEnd = false;
						return true;
					}
				}

				if (listIndex + 1 < graph->adjacencyList.size())
					it = graph->adjacencyList[listIndex + 1].begin();
			}

			onEnd = true;
			return false;
		}

		EdgeType* operator*() {
			if (onEnd) 
				throw "Указатель за пределами графа";
				
			return *it;
		}

		bool end() {
			return false;
		};
	};
};

template<typename VertexType, typename EdgeType>
inline ListGraph<VertexType, EdgeType>::ListGraph(bool directed) {
	this->directed = directed;
	this->listGraph = true;
	this->amountOfEdges = 0;
}

template<typename VertexType, typename EdgeType>
inline VertexType* ListGraph<VertexType, EdgeType>::insertVertex(int index) {
	if (index < 0 || index > adjacencyList.size())
		throw "Выход индекса за пределы списка";

	VertexType* newVertex = new VertexType;

	this->vertexVector.insert(this->vertexVector.begin() + index, newVertex);
	adjacencyList.insert(adjacencyList.begin() + index, list<EdgeType*>());

	return newVertex;
}

template<typename VertexType, typename EdgeType>
inline bool ListGraph<VertexType, EdgeType>::deleteVertex(int index) {
	if (index < 0 || index > adjacencyList.size())
		throw "Выход индекса за пределы списка";

	// Удаляем все ребра вершины
	for (int i = 0; i < adjacencyList.size(); i++) {
		for (auto it = adjacencyList[i].begin(); it != adjacencyList[i].end(); it++) {
			if (this->getVertexIndex((*it)->getV2()) == index) {
				adjacencyList[i].erase(it);
				this->amountOfEdges--;
				break;
			}
		}
	}

	// Удаляем список смежности вершины
	this->amountOfEdges -= adjacencyList[index].size();
	adjacencyList.erase(adjacencyList.begin() + index);

	// Удаляем вершину из списка вершин
	this->vertexVector.erase(this->vertexVector.begin() + index);

	return true;
}

template<typename VertexType, typename EdgeType>
inline bool ListGraph<VertexType, EdgeType>::insertEdge(int v1, int v2, EdgeType* newEdge) {
	if (v1 < 0 || v1 >= adjacencyList.size() || v2 < 0 || v2 >= adjacencyList.size())
		throw "Выход индекса за пределы списка";

	if (v1 == v2)
		throw "Петля недопустима";

	if (hasEdge(v1, v2))
		throw "Данное ребро уже существует";

	adjacencyList[v1].push_back(newEdge);
	this->amountOfEdges++;

	if (!this->directed) {
		adjacencyList[v2].push_back(new EdgeType(newEdge->getV2(), newEdge->getV1()));
		this->amountOfEdges++;
	}

	return true;
}

template<typename VertexType, typename EdgeType>
inline EdgeType* ListGraph<VertexType, EdgeType>::getEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= adjacencyList.size() || v2 < 0 || v2 >= adjacencyList.size())
		throw "Выход индекса за пределы списка";

	if (v1 == v2)
		throw "Петля недопустима";

	EdgeType* edgeToFind = nullptr;

	for (auto edge : adjacencyList[v1]) {
		if (this->getVertexIndex(edge->getV2()) == v2) {
			edgeToFind = edge;
			break;
		}
	}

	if (edgeToFind == nullptr)
		throw "Ребра не существует";

	return edgeToFind;
}

template<typename VertexType, typename EdgeType>
inline bool ListGraph<VertexType, EdgeType>::hasEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= adjacencyList.size() || v2 < 0 || v2 >= adjacencyList.size())
		throw "Выход индекса за пределы списка";

	if (v1 == v2)
		throw "Петля недопустима";

	for (auto edge : adjacencyList[v1]) {
		if (this->getVertexIndex(edge->getV2()) == v2)
			return true;
	}

	return false;
}

template<typename VertexType, typename EdgeType>
inline bool ListGraph<VertexType, EdgeType>::deleteEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= adjacencyList.size() || v2 < 0 || v2 >= adjacencyList.size())
		throw "Выход индекса за пределы списка";

	if (v1 == v2)
		throw "Петля недопустима";

	if (!hasEdge(v1, v2))
		throw "Данное ребро не существует";

	for (auto it = adjacencyList[v1].begin(); it != adjacencyList[v1].end(); it++) {
		if (this->getVertexIndex((*it)->getV2()) == v2) {
			adjacencyList[v1].erase(it);
			this->amountOfEdges--;
			return true;
		}
	}

	return false;
}

template<typename VertexType, typename EdgeType>
inline void ListGraph<VertexType, EdgeType>::print(bool printWithNames) {
	if (this->amountOfEdges != 0) {
		if (printWithNames)
			cout << "Список смежности графа с именами:" << endl;
		else
			cout << "Список смежности графа с индексами:" << endl;

		for (int i = 0; i < adjacencyList.size(); i++) {
			if (!adjacencyList[i].empty()) {
				if (printWithNames)
					cout << (*adjacencyList[i].begin())->getV1()->getName() << " -> ";
				else
					cout << i << " -> ";

				for (auto it = adjacencyList[i].begin(); it != adjacencyList[i].end(); it++) {
					if (printWithNames)
						cout << (*it)->getV2()->getName() << ", ";
					else
						cout << this->getVertexIndex((*it)->getV2()) << ", ";
				}
				cout << "\b\b ";

				cout << endl;
			}
		}
	}
	else 
		cout << "Визуализация невозможна" << endl;
}