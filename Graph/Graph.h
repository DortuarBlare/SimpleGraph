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
	bool directed; // ��������������� ��� �����������������
	bool listGraph; // List-���� ��� Matrix-����
	int amountOfEdges; // ���������� ����

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
				throw "� ����� ����������� �������";

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
				throw "��������� �� ��������� �����";

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
};

template<typename VertexType, typename EdgeType>
inline VertexType* Graph<VertexType, EdgeType>::getVertexByIndex(int index) {
	if (index < 0 || index >= vertexVector.size())
		throw "����� ������� �� ������� �������";

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
		throw "������� �� ����������";

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
	vector<list<EdgeType*>> adjacencyList; // ������ ���������

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
					// ���� ������ ���������� �����
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
				throw "� ����� ����������� �����";

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
				throw "��������� �� ��������� �����";
				
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
	};

	class OutputEdgeIterator {
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
				throw "����� ������� �� ������� ������";

			if (graph->getAmountOfEdges() != 0) {
				if (graph->adjacencyList[listIndex].size() == 0)
					throw "� ������� ����������� ����";

				it = graph->adjacencyList[listIndex].begin();

				if (*it) {
					onEnd = false;
					return true;
				}
			}
			else
				throw "� ����� ����������� �����";

			onEnd = true;
			return false;
		}

		bool operator++(int) {
			if (onEnd)
				return false;

			if (++it != graph->adjacencyList[listIndex].end()) {
				if (*it) {
					onEnd = false;
					return true;
				}
			}

			onEnd = true;
			return false;
		}

		EdgeType* operator*() {
			if (onEnd)
				throw "��������� �� ��������� �����";

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
		throw "����� ������� �� ������� ������";

	VertexType* newVertex = new VertexType;

	this->vertexVector.insert(this->vertexVector.begin() + index, newVertex);
	adjacencyList.insert(adjacencyList.begin() + index, list<EdgeType*>());

	return newVertex;
}

template<typename VertexType, typename EdgeType>
inline bool ListGraph<VertexType, EdgeType>::deleteVertex(int index) {
	if (index < 0 || index > adjacencyList.size())
		throw "����� ������� �� ������� ������";

	// ������� ��� ����� �������
	for (int i = 0; i < adjacencyList.size(); i++) {
		for (auto it = adjacencyList[i].begin(); it != adjacencyList[i].end(); it++) {
			if (this->getVertexIndex((*it)->getV2()) == index) {
				adjacencyList[i].erase(it);
				this->amountOfEdges--;
				break;
			}
		}
	}

	// ������� ������ ��������� �������
	this->amountOfEdges -= adjacencyList[index].size();
	adjacencyList.erase(adjacencyList.begin() + index);

	// ������� ������� �� ������ ������
	this->vertexVector.erase(this->vertexVector.begin() + index);

	return true;
}


template<typename VertexType, typename EdgeType>
inline bool ListGraph<VertexType, EdgeType>::insertEdge(int v1, int v2, EdgeType* newEdge) {
	try {
		if (hasEdge(v1, v2))
			throw "������ ����� ��� ����������";
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
		throw "����� ������� �� ������� ������";

	if (v1 == v2)
		throw "����� �����������";

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
		throw "����� �� ����������";

	return edgeToFind;
}

template<typename VertexType, typename EdgeType>
inline bool ListGraph<VertexType, EdgeType>::hasEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= adjacencyList.size() || v2 < 0 || v2 >= adjacencyList.size())
		throw "����� ������� �� ������� ������";

	if (v1 == v2)
		throw "����� �����������";

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
			throw "������ ����� �� ����������";
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
			cout << "������ ��������� ����� � �������:" << endl;
		else
			cout << "������ ��������� ����� � ���������:" << endl;

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
		cout << "������������ ����������" << endl;
}


template<typename VertexType, typename EdgeType>
class MatrixGraph : public Graph<VertexType, EdgeType> {
private:
	vector<vector<EdgeType*>> adjacencyMatrix; // ������� ���������

public:
	MatrixGraph(bool directed);

	VertexType* insertVertex(int index);
	bool deleteVertex(int index);

	bool insertEdge(int v1, int v2, EdgeType* newEdge);
	EdgeType* getEdge(int v1, int v2);
	bool hasEdge(int v1, int v2);
	bool deleteEdge(int v1, int v2);

	void print(bool printWithNames);
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
		throw "����� ������� �� ������� ������";

	VertexType* newVertex = new VertexType;

	this->vertexVector.insert(this->vertexVector.begin() + index, newVertex);

	// ������� ����� ������
	vector<EdgeType*> newLine;
	newLine.assign(adjacencyMatrix.size(), NULL);
	adjacencyMatrix.insert(adjacencyMatrix.begin() + index, newLine);

	for (int i = 0; i < adjacencyMatrix.size(); i++)
		adjacencyMatrix[i].insert(adjacencyMatrix[i].begin() + index, NULL);

	return newVertex;
}

template<typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::deleteVertex(int index) {
	if (index < 0 || index > adjacencyMatrix.size())
		throw "����� ������� �� ������� ������";

	// ������� ������ � �������
	adjacencyMatrix.erase(adjacencyMatrix.begin() + index);
	for (int i = 0; i < adjacencyMatrix.size(); i++)
		adjacencyMatrix[i].erase(adjacencyMatrix[i].begin() + index);

	// ������� ������� �� ������ ������
	this->vertexVector.erase(this->vertexVector.begin() + index);

	return true;
}


template<typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::insertEdge(int v1, int v2, EdgeType* newEdge) {
	try {
		if (hasEdge(v1, v2))
			throw "������ ����� ��� ����������";
	}
	catch (const char* exception) {
		throw exception;
	}

	adjacencyMatrix[v1][v2] = newEdge;
	if (this->directed)
		adjacencyMatrix[v2][v1] = newEdge;

	this->amountOfEdges++;

	return false;
}

template<typename VertexType, typename EdgeType>
inline EdgeType* MatrixGraph<VertexType, EdgeType>::getEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= adjacencyMatrix.size() || v2 < 0 || v2 >= adjacencyMatrix.size())
		throw "����� ������� �� ������� ������";

	if (v1 == v2)
		throw "����� �����������";

	EdgeType* edgeToFind = nullptr;

	if (adjacencyMatrix[v1][v2] != NULL)
		edgeToFind = adjacencyMatrix[v1][v2];

	if (!this->directed && adjacencyMatrix[v2][v1] != NULL)
		edgeToFind = adjacencyMatrix[v2][v1];

	if (edgeToFind == nullptr)
		throw "����� �� ����������";

	return edgeToFind;
}

template<typename VertexType, typename EdgeType>
inline bool MatrixGraph<VertexType, EdgeType>::hasEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= adjacencyMatrix.size() || v2 < 0 || v2 >= adjacencyMatrix.size())
		throw "����� ������� �� ������� ������";

	if (v1 == v2)
		throw "����� �����������";

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
			throw "������ ����� �� ����������";
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
		if (printWithNames)
			cout << "������� ��������� ����� � �������:" << endl;
		else
			cout << "������� ��������� ����� � ���������:" << endl;

		for (int i = 0; i < this->getVertexByIndex(0)->getName().size(); i++)
			cout << ' ';
		cout << '|';
		// ����� �� �����������
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
		// ����� �� ��������� �� ����������
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
		cout << "������������ ����������" << endl;
}
