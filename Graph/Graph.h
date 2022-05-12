#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
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
	virtual bool insertVertex(int index, VertexType* vertex) = 0;
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
	vector<VertexType*> getVertexVector();
	bool isDirected();
	bool isListGraph();
	int getAmountOfVertices();
	int getAmountOfEdges();

	class VertexIterator {
	private:
		Graph<VertexType, EdgeType>* graph;
		typename vector<VertexType*>::iterator it;
		bool onEnd;

	public:
		VertexIterator() {}

		VertexIterator(Graph<VertexType, EdgeType>& graph) {
			this->graph = &graph;
			try {
				begin();
			}
			catch (const char* exception) {
				throw exception;
			}
		}

		bool begin() {
			if (graph->vertexVector.empty())
				throw "В графе отсутствуют вершины";

			it = graph->vertexVector.begin();

			if (it == graph->vertexVector.begin() && it != graph->vertexVector.end()) {
				onEnd = false;
				return true;
			}

			onEnd = true;
			return false;
		}

		bool operator++(int) {
			if (onEnd)
				return false;

			if (it != graph->vertexVector.end()) {
				it++;
				if (it == graph->vertexVector.end())
					onEnd = true;
				else
					onEnd = false;

				return true;
			}

			onEnd = true;
			return false;
		}

		VertexType* operator*() {
			if (onEnd)
				throw "Указатель за пределами графа";

			return *it;
		}

		bool end() {
			if (onEnd)
				return true;

			it = graph->vertexVector.end();

			if (it == graph->vertexVector.end())
				return true;

			return false;
		}
	};

	class EdgeIterator {
	public:
		virtual bool begin() = 0;

		virtual bool operator++(int) = 0;

		virtual EdgeType* operator*() = 0;

		virtual bool end() = 0;

		virtual bool isOnEnd() = 0;
	};

	class OutputEdgeIterator {
	public:
		virtual bool begin() = 0;

		virtual bool operator++(int) = 0;

		virtual EdgeType* operator*() = 0;

		virtual bool end() = 0;
	};
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
inline vector<VertexType*> Graph<VertexType, EdgeType>::getVertexVector() {
	return this->vertexVector;
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
	bool insertVertex(int index, VertexType* vertex);
	bool deleteVertex(int index);

	bool insertEdge(int v1, int v2, EdgeType* newEdge);
	EdgeType* getEdge(int v1, int v2);
	bool hasEdge(int v1, int v2);
	bool deleteEdge(int v1, int v2);

	void print(bool printWithNames);

	class EdgeIterator : public Graph<VertexType, EdgeType>::EdgeIterator {
	private:
		ListGraph<VertexType, EdgeType>* graph;
		typename list<EdgeType*>::iterator it;
		int listIndex;
		bool onEnd;

	public:
		EdgeIterator() {}

		EdgeIterator(ListGraph* graph) {
			this->graph = graph;
			try {
				begin();
			}
			catch (const char* exception) {
				throw exception;
			}
		}

		bool begin() {
			if (graph->amountOfEdges != 0) {
				for (listIndex = 0; listIndex < graph->adjacencyList.size(); listIndex++) {
					// Ищем первое попавшееся ребро
					for (it = graph->adjacencyList[listIndex].begin();
						 it != graph->adjacencyList[listIndex].end();
						 it++) {
						if (graph->directed) {
							if (*it) {
								onEnd = false;
								return true;
							}
						}
						else {
							if (*it && graph->getVertexIndex((*it)->getV1()) == listIndex) {
								onEnd = false;
								return true;
							}
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
					if (graph->directed) {
						if (*it) {
							onEnd = false;
							return true;
						}
					}
					else {
						if (*it && graph->getVertexIndex((*it)->getV1()) == listIndex) {
							onEnd = false;
							return true;
						}
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
			if (onEnd)
				return true;

			it = graph->adjacencyList[graph->adjacencyList.size() - 1].end();

			if (it == graph->adjacencyList[graph->adjacencyList.size() - 1].end()) {
				onEnd = true;
				return true;
			}

			return false;
		};

		bool isOnEnd() {
			return onEnd;
		}
	};

	class OutputEdgeIterator : public Graph<VertexType, EdgeType>::OutputEdgeIterator {
	private:
		ListGraph<VertexType, EdgeType>* graph;
		typename list<EdgeType*>::iterator it;
		int listIndex;
		bool onEnd;

	public:
		OutputEdgeIterator() {}

		OutputEdgeIterator(ListGraph* graph, int vertexIndex) {
			this->graph = graph;
			this->listIndex = vertexIndex;

			try {
				begin();
			}
			catch (const char* exception) {
				throw exception;
			}
		}

		bool begin() {
			if (listIndex < 0 || listIndex > graph->adjacencyList.size())
				throw "Выход индекса за пределы списка";

			if (graph->getAmountOfEdges() != 0) {
				if (graph->adjacencyList[listIndex].size() == 0)
					throw "У вершины отсутствуют рёбра";

				it = graph->adjacencyList[listIndex].begin();

				while (it != graph->adjacencyList[listIndex].end()) {
					if (graph->isDirected()) {
						if (*it) {
							onEnd = false;
							return true;
						}
					}
					else {
						if (*it && graph->getVertexIndex((*it)->getV1()) == listIndex) {
							onEnd = false;
							return true;
						}
					}
					it++;
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

			while (++it != graph->adjacencyList[listIndex].end()) {
				if (graph->isDirected()) {
					if (*it) {
						onEnd = false;
						return true;
					}
				}
				else {
					if (*it && graph->getVertexIndex((*it)->getV1()) == listIndex) {
						onEnd = false;
						return true;
					}
				}
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
			if (onEnd)
				return true;

			it = graph->adjacencyList[listIndex].end();

			if (it == graph->adjacencyList[listIndex].end()) {
				onEnd = true;
				return true;
			}

			return false;
		};

		bool isOnEnd() {
			return onEnd;
		}
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
inline bool ListGraph<VertexType, EdgeType>::insertVertex(int index, VertexType* vertex) {
	if (index < 0 || index > adjacencyList.size()) {
		throw "Выход индекса за пределы списка";
		return false;
	}

	this->vertexVector.insert(this->vertexVector.begin() + index, vertex);
	adjacencyList.insert(adjacencyList.begin() + index, list<EdgeType*>());

	return true;
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
	try {
		if (hasEdge(v1, v2))
			throw "Данное ребро уже существует";
	}
	catch (const char* exception) {
		throw exception;
	}

	adjacencyList[v1].push_back(newEdge);

	if (!this->directed) 
		adjacencyList[v2].push_back(newEdge);

	this->amountOfEdges++;

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
		if (this->directed && this->getVertexIndex(edge->getV2()) == v2) {
			edgeToFind = edge;
			break;
		}

		if (!this->directed &&
			(
				this->getVertexIndex(edge->getV2()) == v2 ||
				(
					this->getVertexIndex(edge->getV2()) == v1 && 
					this->getVertexIndex(edge->getV1()) == v2)
				)
			) 
		{
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
		if (this->directed && this->getVertexIndex(edge->getV2()) == v2)
			return true;

		if (!this->directed &&
			(
				this->getVertexIndex(edge->getV2()) == v2 ||
				(
					this->getVertexIndex(edge->getV2()) == v1 &&
					this->getVertexIndex(edge->getV1()) == v2)
				)
			)
			return true;
	}

	return false;
}

template<typename VertexType, typename EdgeType>
inline bool ListGraph<VertexType, EdgeType>::deleteEdge(int v1, int v2) {
	try {
		if (!hasEdge(v1, v2))
			throw "Данное ребро не существует";
	}
	catch (const char* exception) {
		throw exception;
	}

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
				if (this->directed) {
					if (printWithNames)
						cout << this->vertexVector[i]->getName() << " -> ";
					else
						cout << i << " -> ";

					for (auto edge : adjacencyList[i]) {
						if (printWithNames)
							cout << edge->getV2()->getName() << ", ";
						else
							cout << this->getVertexIndex(edge->getV2()) << ", ";
					}
					cout << "\b\b " << endl;
				}
				else {
					if (printWithNames)
						cout << this->vertexVector[i]->getName() << " -> ";
					else
						cout << i << " -> ";
					
					for (auto edge : adjacencyList[i]) {
						if (this->getVertexIndex(edge->getV1()) == i) {
							if (printWithNames)
								cout << edge->getV2()->getName() << ", ";
							else
								cout << this->getVertexIndex(edge->getV2()) << ", ";
						}
						else {
							if (printWithNames)
								cout << edge->getV1()->getName() << ", ";
							else
								cout << this->getVertexIndex(edge->getV1()) << ", ";
						}
					}
					cout << "\b\b " << endl;
				}
			}
		}
	}
	else 
		cout << "Визуализация невозможна" << endl;
}



template<typename VertexType, typename EdgeType>
class MatrixGraph : public Graph<VertexType, EdgeType> {
private:
	vector<vector<EdgeType*>> adjacencyMatrix; // Матрица смежности

public:
	MatrixGraph(bool directed);

	VertexType* insertVertex(int index);
	bool insertVertex(int index, VertexType* vertex);
	bool deleteVertex(int index);

	bool insertEdge(int v1, int v2, EdgeType* newEdge);
	EdgeType* getEdge(int v1, int v2);
	bool hasEdge(int v1, int v2);
	bool deleteEdge(int v1, int v2);

	void print(bool printWithNames);

	class EdgeIterator : public Graph<VertexType, EdgeType>::EdgeIterator {
	private:
		MatrixGraph<VertexType, EdgeType>* graph;
		typename vector<EdgeType*>::iterator it;
		int vectorIndex;
		bool onEnd;

	public:
		EdgeIterator() {}

		EdgeIterator(MatrixGraph* graph) {
			this->graph = graph;
			try {
				begin();
			}
			catch (const char* exception) {
				throw exception;
			}
		}

		bool begin() {
			if (graph->amountOfEdges != 0) {
				for (vectorIndex = 0; vectorIndex < graph->adjacencyMatrix.size(); vectorIndex++) {
					// Ищем первое попавшееся ребро
					for (it = graph->adjacencyMatrix[vectorIndex].begin();
						it != graph->adjacencyMatrix[vectorIndex].end();
						it++) {
						if (graph->directed) {
							if (*it != NULL) {
								onEnd = false;
								return true;
							}
						}
						else {
							if (*it != NULL && graph->getVertexIndex((*it)->getV1()) == vectorIndex) {
								onEnd = false;
								return true;
							}
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

			for (it++; vectorIndex < graph->adjacencyMatrix.size(); vectorIndex++) {
				for (; it != graph->adjacencyMatrix[vectorIndex].end(); it++) {
					if (graph->directed) {
						if (*it != NULL) {
							onEnd = false;
							return true;
						}
					}
					else {
						if (*it != NULL && graph->getVertexIndex((*it)->getV1()) == vectorIndex) {
							onEnd = false;
							return true;
						}
					}
				}

				if (vectorIndex + 1 < graph->adjacencyMatrix.size())
					it = graph->adjacencyMatrix[vectorIndex + 1].begin();
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
			if (onEnd)
				return true;

			it = graph->adjacencyMatrix[graph->adjacencyMatrix.size() - 1].end();

			if (it == graph->adjacencyMatrix[graph->adjacencyMatrix.size() - 1].end()) {
				onEnd = true;
				return true;
			}

			return false;
		};

		bool isOnEnd() {
			return onEnd;
		}
	};

	class OutputEdgeIterator : public Graph<VertexType, EdgeType>::OutputEdgeIterator {
	private:
		MatrixGraph<VertexType, EdgeType>* graph;
		typename vector<EdgeType*>::iterator it;
		int vectorIndex;
		bool onEnd;

	public:
		OutputEdgeIterator() {}

		OutputEdgeIterator(MatrixGraph* graph, int vertexIndex) {
			this->graph = graph;
			this->vectorIndex = vertexIndex;

			try {
				begin();
			}
			catch (const char* exception) {
				throw exception;
			}
		}

		bool begin() {
			if (vectorIndex < 0 || vectorIndex > graph->adjacencyMatrix.size())
				throw "Выход индекса за пределы вектора";

			if (graph->getAmountOfEdges() != 0) {
				if (graph->adjacencyMatrix[vectorIndex].size() == 0)
					throw "У вершины отсутствуют рёбра";

				it = graph->adjacencyMatrix[vectorIndex].begin();

				while (it != graph->adjacencyMatrix[vectorIndex].end()) {
					if (graph->isDirected()) {
						if (*it != NULL) {
							onEnd = false;
							return true;
						}
					}
					else {
						if (*it != NULL && graph->getVertexIndex((*it)->getV1()) == vectorIndex) {
							onEnd = false;
							return true;
						}
					}
					it++;
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

			for (it++; it != graph->adjacencyMatrix[vectorIndex].end(); it++) {
				if (graph->directed) {
					if (*it != NULL) {
						onEnd = false;
						return true;
					}
				}
				else {
					if (*it != NULL && graph->getVertexIndex((*it)->getV1()) == vectorIndex) {
						onEnd = false;
						return true;
					}
				}
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
			/*if (onEnd)
				return true;

			it = graph->adjacencyMatrix[graph->adjacencyMatrix.size() - 1].end();

			if (it == graph->adjacencyMatrix[graph->adjacencyMatrix.size() - 1].end()) {
				onEnd = true;
				return true;
			}

			return false;*/
			if (onEnd)
				return true;

			it = graph->adjacencyMatrix[vectorIndex].end();

			if (it == graph->adjacencyMatrix[vectorIndex].end()) {
				onEnd = true;
				return true;
			}

			return false;
		};
	};
};

template<typename VertexType, typename EdgeType>
inline MatrixGraph<VertexType, EdgeType>::MatrixGraph(bool directed) {
	this->directed = directed;
	this->listGraph = false;
	this->amountOfEdges = 0;
}


template<typename VertexType, typename EdgeType>
inline VertexType* MatrixGraph<VertexType, EdgeType>::insertVertex(int index) {
	if (index < 0 || index > adjacencyMatrix.size())
		throw "Выход индекса за пределы списка";

	VertexType* newVertex = new VertexType;

	this->vertexVector.insert(this->vertexVector.begin() + index, newVertex);

	// Вставка новой строки
	vector<EdgeType*> newLine;
	newLine.assign(adjacencyMatrix.size(), NULL);
	adjacencyMatrix.insert(adjacencyMatrix.begin() + index, newLine);

	for (int i = 0; i < adjacencyMatrix.size(); i++)
		adjacencyMatrix[i].insert(adjacencyMatrix[i].begin() + index, NULL);

	return newVertex;
}

template<typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::insertVertex(int index, VertexType* vertex) {
	if (index < 0 || index > adjacencyMatrix.size()) {
		throw "Выход индекса за пределы списка";
		return false;
	}

	this->vertexVector.insert(this->vertexVector.begin() + index, vertex);

	// Вставка новой строки
	vector<EdgeType*> newLine;
	newLine.assign(adjacencyMatrix.size(), NULL);
	adjacencyMatrix.insert(adjacencyMatrix.begin() + index, newLine);

	for (int i = 0; i < adjacencyMatrix.size(); i++)
		adjacencyMatrix[i].insert(adjacencyMatrix[i].begin() + index, NULL);

	return true;
}

template<typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::deleteVertex(int index) {
	if (index < 0 || index > adjacencyMatrix.size())
		throw "Выход индекса за пределы списка";

	// Удаляем строку и стоблец
	adjacencyMatrix.erase(adjacencyMatrix.begin() + index);
	for (int i = 0; i < adjacencyMatrix.size(); i++)
		adjacencyMatrix[i].erase(adjacencyMatrix[i].begin() + index);

	// Удаляем вершину из списка вершин
	this->vertexVector.erase(this->vertexVector.begin() + index);

	return true;
}


template<typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::insertEdge(int v1, int v2, EdgeType* newEdge) {
	try {
		if (hasEdge(v1, v2))
			throw "Данное ребро уже существует";
	}
	catch (const char* exception) {
		throw exception;
	}

	adjacencyMatrix[v1][v2] = newEdge;
	if (!this->directed)
		adjacencyMatrix[v2][v1] = newEdge;

	this->amountOfEdges++;

	return false;
}

template<typename VertexType, typename EdgeType>
inline EdgeType* MatrixGraph<VertexType, EdgeType>::getEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= adjacencyMatrix.size() || v2 < 0 || v2 >= adjacencyMatrix.size())
		throw "Выход индекса за пределы списка";

	if (v1 == v2)
		throw "Петля недопустима";

	EdgeType* edgeToFind = nullptr;

	if (adjacencyMatrix[v1][v2] != NULL)
		edgeToFind = adjacencyMatrix[v1][v2];

	if (!this->directed && adjacencyMatrix[v2][v1] != NULL)
		edgeToFind = adjacencyMatrix[v2][v1];

	if (edgeToFind == nullptr)
		throw "Ребра не существует";

	return edgeToFind;
}

template<typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::hasEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= adjacencyMatrix.size() || v2 < 0 || v2 >= adjacencyMatrix.size())
		throw "Выход индекса за пределы списка";

	if (v1 == v2)
		throw "Петля недопустима";

	if (this->directed && adjacencyMatrix[v1][v2] != NULL)
		return true;

	if (!this->directed && (adjacencyMatrix[v1][v2] != NULL || adjacencyMatrix[v2][v1] != NULL))
		return true;

	return false;
}

template<typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::deleteEdge(int v1, int v2) {
	try {
		if (!hasEdge(v1, v2))
			throw "Данное ребро не существует";
	}
	catch (const char* exception) {
		throw exception;
	}

	adjacencyMatrix[v1][v2] = NULL;

	return true;
}


template<typename VertexType, typename EdgeType>
inline void MatrixGraph<VertexType, EdgeType>::print(bool printWithNames) {
	if (this->getAmountOfVertices() != 0) {
		cout << "Матрица смежности графа с именами:" << endl;

		for (int i = 0; i < this->getVertexByIndex(0)->getName().size(); i++)
			cout << ' ';
		cout << '|';
		// Имена по горизонтали
		for (int i = 0; i < this->getAmountOfVertices(); i++) {
			if (i == 0)
				cout << "  " << this->getVertexByIndex(i)->getName();
			else
				cout << setw((this->getVertexByIndex(i)->getName().size()) * 2) << this->getVertexByIndex(i)->getName();
		}

		cout << endl;
		for (int i = 0; i < this->getVertexByIndex(0)->getName().size(); i++)
			cout << '-';
		cout << "| -";
		for (int i = 0; i < this->getAmountOfVertices() * this->getVertexByIndex(0)->getName().size(); i++)
			cout << "--";
		cout << endl;
		// Имена по вертикали со значениями
		for (int i = 0; i < this->getAmountOfVertices(); i++) {
			cout << setw(2) << this->getVertexByIndex(i)->getName() << setw(0) << "|";
			for (int j = 0; j < this->getAmountOfVertices(); j++) {
				try {
					if (j == 0) {
						if (hasEdge(i, j))
							cout << setw((this->getVertexByIndex(j)->getName().size()) + 2) << "1";
						else
							cout << setw((this->getVertexByIndex(j)->getName().size()) + 2) << "0";
					}
					else {
						if (hasEdge(i, j))
							cout << setw((this->getVertexByIndex(j)->getName().size()) * 2) << "1";
						else
							cout << setw((this->getVertexByIndex(j)->getName().size()) * 2) << "0";
					}
				}
				catch (const char* exception) {
					if (j == 0)
						cout << setw((this->getVertexByIndex(j)->getName().size()) + 2) << "0";
					else
						cout << setw((this->getVertexByIndex(j)->getName().size()) * 2) << "0";
				}
			}
			cout << endl;
		}
	}
	else
		cout << "Визуализация невозможна" << endl;
}