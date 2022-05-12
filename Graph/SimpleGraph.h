#pragma once
#include "Graph.h"

template<typename VertexType, typename EdgeType>
class SimpleGraph {
private:
	Graph<VertexType, EdgeType>* graph;

public:
	SimpleGraph(); // Пустой List-Граф
	SimpleGraph(int amountOfVertices, bool directed, bool listGraph);
	SimpleGraph(int amountOfVertices, int amountOfEdges, bool directed, bool listGraph); // Случайные ребра
	SimpleGraph(SimpleGraph<VertexType, EdgeType>& graph);
	~SimpleGraph();

	// Вершины
	VertexType* pushBackVertex();
	VertexType* insertVertex(int index);
	VertexType* getVertexByIndex(int index);
	template<typename VertexNameType> VertexType* getVertexByName(VertexNameType name);
	int getVertexIndex(VertexType* vertex);
	bool deleteVertex(VertexType* vertexToDelete);
	bool deleteVertexByIndex(int index);
	template<typename VertexNameType> bool deleteVertexByName(VertexNameType name);

	// Ребра
	bool insertEdge(VertexType* v1, VertexType* v2);
	bool insertEdgeByVertexIndexes(int v1, int v2);
	template<typename VertexNameType> bool insertEdgeByVertexNames(VertexNameType v1, VertexNameType v2);
	EdgeType* getEdge(VertexType* v1, VertexType* v2);
	EdgeType* getEdgeByVertexIndexes(int v1, int v2);
	template<typename VertexNameType> EdgeType* getEdgeByVertexNames(VertexNameType v1, VertexNameType v2);
	bool hasEdge(VertexType* v1, VertexType* v2);
	bool hasEdge(int v1, int v2);
	bool deleteEdge(VertexType* v1, VertexType* v2);
	bool deleteEdgeByVertexIndexes(int v1, int v2);
	template<typename VertexNameType> bool deleteEdgeByVertexNames(VertexNameType v1, VertexNameType v2);

	void toListGraph();
	void toMatrixGraph();

	void print(bool printWithNames);

	double saturationCoefficient();
	Graph<VertexType, EdgeType>* getGraph();
	bool isDirected();
	bool isListGraph();
	int getAmountOfVertices();
	int getAmountOfEdges();
	
	class VertexIterator {
	private:
		SimpleGraph<VertexType, EdgeType>* simpleGraph;
		typename Graph<VertexType, EdgeType>::VertexIterator it;

	public:
		VertexIterator() {}

		VertexIterator(SimpleGraph<VertexType, EdgeType>& graph) {
			this->simpleGraph = &graph;
			try {
				it = Graph<VertexType, EdgeType>::VertexIterator(*simpleGraph->graph);
			}
			catch (const char* exception) {
				throw exception;
			}
		}

		bool begin() {
			try {
				return it.begin();
			}
			catch (const char* exception) {
				throw exception;
			}

			return false;
		}

		bool operator++(int) {
			return it++;
		}

		VertexType* operator*() {
			try {
				return *it;
			}
			catch (const char* exception) {
				throw exception;
			}

			return nullptr;
		}

		bool end() {
			try {
				return it.end();
			}
			catch (const char* exception) {
				throw exception;
			}

			return false;
		}

		bool isOnEnd() {
			return it->isOnEnd();
		}
	};

	class EdgeIterator {
	private:
		SimpleGraph<VertexType, EdgeType>* simpleGraph;
		typename Graph<VertexType, EdgeType>::EdgeIterator* it;

	public:
		EdgeIterator() {}

		EdgeIterator(SimpleGraph<VertexType, EdgeType>& graph) {
			this->simpleGraph = &graph;
			try {
				if (graph.isListGraph())
					it = new typename ListGraph<VertexType, EdgeType>::EdgeIterator(
						static_cast<ListGraph<VertexType, EdgeType>*>(simpleGraph->graph)
					);
				else
					it = new typename MatrixGraph<VertexType, EdgeType>::EdgeIterator(
						static_cast<MatrixGraph<VertexType, EdgeType>*>(simpleGraph->graph)
					);
			}
			catch (const char* exception) {
				throw exception;
			}
		}

		bool begin() {
			try {
				return it->begin();
			}
			catch (const char* exception) {
				throw exception;
			}

			return false;
		}

		bool operator++(int) {
			return (*it)++;
		}

		EdgeType* operator*() {
			try {
				return **it;
			}
			catch (const char* exception) {
				throw exception;
			}

			return nullptr;
		}

		bool end() {
			try {
				return it->end();
			}
			catch (const char* exception) {
				throw exception;
			}

			return false;
		}

		bool isOnEnd() {
			return it->isOnEnd();
		}
	};

	class OutputEdgeIterator {
	private:
		SimpleGraph<VertexType, EdgeType>* simpleGraph;
		typename Graph<VertexType, EdgeType>::OutputEdgeIterator* it;

	public:
		OutputEdgeIterator() {}

		OutputEdgeIterator(SimpleGraph<VertexType, EdgeType>& graph, int vertexIndex) {
			this->simpleGraph = &graph;

			try {
				if (graph.isListGraph())
					it = new typename ListGraph<VertexType, EdgeType>::OutputEdgeIterator(
						static_cast<ListGraph<VertexType, EdgeType>*>(simpleGraph->graph), vertexIndex
					);
				else
					it = new typename MatrixGraph<VertexType, EdgeType>::OutputEdgeIterator(
						static_cast<MatrixGraph<VertexType, EdgeType>*>(simpleGraph->graph), vertexIndex
					);
			}
			catch (const char* exception) {
				throw exception;
			}
		}

		bool begin() {
			try {
				return it->begin();
			}
			catch (const char* exception) {
				throw exception;
			}

			return false;
		}

		bool operator++(int) {
			return (*it)++;
		}

		EdgeType* operator*() {
			try {
				return **it;
			}
			catch (const char* exception) {
				throw exception;
			}

			return nullptr;
		}

		bool end() {
			try {
				return it->end();
			}
			catch (const char* exception) {
				throw exception;
			}

			return false;
		}

		bool isOnEnd() {
			return it->isOnEnd();
		}
	};
};

template<typename VertexType, typename EdgeType>
inline SimpleGraph<VertexType, EdgeType>::SimpleGraph() {
	graph = new ListGraph<VertexType, EdgeType>(false);
}

template<typename VertexType, typename EdgeType>
inline SimpleGraph<VertexType, EdgeType>::SimpleGraph(int amountOfVertices, bool directed, bool listGraph) {
	if (listGraph)
		graph = new ListGraph<VertexType, EdgeType>(directed);
	else
		graph = new MatrixGraph<VertexType, EdgeType>(directed);

	for (int i = 0; i < amountOfVertices; i++) {
		stringstream ss;
		ss << i;
		VertexType* newVertex = pushBackVertex();
		newVertex->setName("v" + ss.str());
		newVertex->setData(i);
	}
}

template<typename VertexType, typename EdgeType>
inline SimpleGraph<VertexType, EdgeType>::SimpleGraph(int amountOfVertices, int amountOfEdges, bool directed, bool listGraph) {
	if (listGraph)
		graph = new ListGraph<VertexType, EdgeType>(directed);
	else
		graph = new MatrixGraph<VertexType, EdgeType>(directed);

	for (int i = 0; i < amountOfVertices; i++) {
		stringstream ss;
		ss << i;
		VertexType* newVertex = pushBackVertex();
		newVertex->setName("v" + ss.str());
		newVertex->setData(i);
	}

	if (amountOfEdges > (amountOfVertices * (amountOfVertices - 1)) / 2) {
		throw "Количество рёбер превышают максимальное число";
		return;
	}

	srand(time(0));
	while (getAmountOfEdges() != amountOfEdges) {
		try {
			int v1 = rand() % getAmountOfVertices();
			int v2 = rand() % getAmountOfVertices();

			if (v1 == v2)
				continue;

			if (directed && (hasEdge(v1, v2) || hasEdge(v2, v1)))
				continue;

			if (!directed && hasEdge(v1, v2))
				continue;

			insertEdgeByVertexIndexes(v1, v2);
		}
		catch (const char* exception) {}
	}
}

template<typename VertexType, typename EdgeType>
inline SimpleGraph<VertexType, EdgeType>::SimpleGraph(SimpleGraph<VertexType, EdgeType>& simpleGraph) {
	delete this->graph;

	if (simpleGraph.isListGraph())
		this->graph = new ListGraph<VertexType, EdgeType>(simpleGraph.isDirected());
	else
		this->graph = new MatrixGraph<VertexType, EdgeType>(simpleGraph.isDirected());

	for (auto vertex : simpleGraph.getGraph()->getVertexVector())
		this->graph->insertVertex(getAmountOfVertices(), new VertexType(vertex->getName(), vertex->getData()));

	EdgeIterator it = EdgeIterator(simpleGraph);

	for (it.begin(); !it.isOnEnd(); it++) {
		int v1 = simpleGraph.getVertexIndex((*it)->getV1());
		int v2 = simpleGraph.getVertexIndex((*it)->getV2());
		this->graph->insertEdge(v1, v2, new EdgeType(getVertexByIndex(v1), getVertexByIndex(v2)));
	}
}

template<typename VertexType, typename EdgeType>
inline SimpleGraph<VertexType, EdgeType>::~SimpleGraph() {
	delete graph;
}


template<typename VertexType, typename EdgeType>
inline VertexType* SimpleGraph<VertexType, EdgeType>::pushBackVertex() {
	VertexType* newVertex = nullptr;

	try {
		newVertex = graph->insertVertex(graph->getAmountOfVertices());
	}
	catch (const char* exception) {
		throw exception;
	}

	return newVertex;
}

template<typename VertexType, typename EdgeType>
inline VertexType* SimpleGraph<VertexType, EdgeType>::insertVertex(int index) {
	VertexType* newVertex = nullptr;

	try {
		newVertex = graph->insertVertex(index);
	}
	catch (const char* exception) {
		throw exception;
	}

	return newVertex;
}

template<typename VertexType, typename EdgeType>
inline VertexType* SimpleGraph<VertexType, EdgeType>::getVertexByIndex(int index) {
	VertexType* vertex = nullptr;

	try {
		vertex = graph->getVertexByIndex(index);
	}
	catch (const char* exception) {
		throw exception;
	}

	return vertex;
}

template<typename VertexType, typename EdgeType>
template<typename VertexNameType>
inline VertexType* SimpleGraph<VertexType, EdgeType>::getVertexByName(VertexNameType name) {
	VertexType* vertex = nullptr;

	try {
		vertex = graph->getVertexByName(name);
	}
	catch (const char* exception) {
		throw exception;
	}

	return vertex;
}

template<typename VertexType, typename EdgeType>
inline int SimpleGraph<VertexType, EdgeType>::getVertexIndex(VertexType* vertex) {
	return graph->getVertexIndex(vertex);
}

template<typename VertexType, typename EdgeType>
inline bool SimpleGraph<VertexType, EdgeType>::deleteVertex(VertexType* vertexToDelete) {
	bool result = false;

	try {
		result = graph->deleteVertex(getVertexIndex(vertexToDelete));
	}
	catch (const char* exception) {
		throw exception;
	}

	return result;
}

template<typename VertexType, typename EdgeType>
inline bool SimpleGraph<VertexType, EdgeType>::deleteVertexByIndex(int index) {
	bool result = false;

	try {
		result = graph->deleteVertex(index);
	}
	catch (const char* exception) {
		throw exception;
	}

	return result;
}

template<typename VertexType, typename EdgeType>
template<typename VertexNameType>
inline bool SimpleGraph<VertexType, EdgeType>::deleteVertexByName(VertexNameType name) {
	bool result = false;

	try {
		result = graph->deleteVertex(getVertexIndex(getVertexByName(name)));
	}
	catch (const char* exception) {
		throw exception;
	}

	return result;
}


template<typename VertexType, typename EdgeType>
inline bool SimpleGraph<VertexType, EdgeType>::insertEdge(VertexType* v1, VertexType* v2) {
	bool result = false;

	try {
		result = graph->insertEdge(getVertexIndex(v1), getVertexIndex(v2), new EdgeType(v1, v2));
	}
	catch (const char* exception) {
		throw exception;
	}

	return result;
}

template<typename VertexType, typename EdgeType>
inline bool SimpleGraph<VertexType, EdgeType>::insertEdgeByVertexIndexes(int v1, int v2) {
	bool result = false;

	try {
		result = graph->insertEdge(
			v1, 
			v2, 
			new EdgeType(getVertexByIndex(v1), getVertexByIndex(v2))
		);
	}
	catch (const char* exception) {
		throw exception;
	}

	return result;
}

template<typename VertexType, typename EdgeType>
template<typename VertexNameType>
inline bool SimpleGraph<VertexType, EdgeType>::insertEdgeByVertexNames(VertexNameType v1, VertexNameType v2) {
	bool result = false;
	VertexType* vertex1 = getVertexByName(v1);
	VertexType* vertex2 = getVertexByName(v2);

	try {
		result = graph->insertEdge(
			getVertexIndex(vertex1), 
			getVertexIndex(vertex2), 
			new EdgeType(vertex1, vertex2)
		);
	}
	catch (const char* exception) {
		throw exception;
	}

	return result;
}

template<typename VertexType, typename EdgeType>
inline EdgeType* SimpleGraph<VertexType, EdgeType>::getEdge(VertexType* v1, VertexType* v2) {
	EdgeType* edge = nullptr;

	try {
		edge = graph->getEdge(getVertexIndex(v1), getVertexIndex(v2));
	}
	catch (const char* exception) {
		throw exception;
	}

	return edge;
}

template<typename VertexType, typename EdgeType>
inline EdgeType* SimpleGraph<VertexType, EdgeType>::getEdgeByVertexIndexes(int v1, int v2) {
	EdgeType* edge = nullptr;

	try {
		edge = graph->getEdge(v1, v2);
	}
	catch (const char* exception) {
		throw exception;
	}

	return edge;
}

template<typename VertexType, typename EdgeType>
template<typename VertexNameType>
inline EdgeType* SimpleGraph<VertexType, EdgeType>::getEdgeByVertexNames(VertexNameType v1, VertexNameType v2) {
	EdgeType* edge = nullptr;

	try {
		edge = getEdge(
			getVertexByName(v1), 
			getVertexByName(v2)
		);
	}
	catch (const char* exception) {
		throw exception;
	}

	return edge;
}

template<typename VertexType, typename EdgeType>
inline bool SimpleGraph<VertexType, EdgeType>::hasEdge(VertexType* v1, VertexType* v2) {
	bool result = false;

	try {
		result = graph->hasEdge(getVertexIndex(v1), getVertexIndex(v2));
	}
	catch (const char* exception) {
		throw exception;
	}

	return result;
}

template<typename VertexType, typename EdgeType>
inline bool SimpleGraph<VertexType, EdgeType>::hasEdge(int v1, int v2) {
	bool result = false;

	try {
		result = graph->hasEdge(v1, v2);
	}
	catch (const char* exception) {
		throw exception;
	}

	return result;
}

template<typename VertexType, typename EdgeType>
inline bool SimpleGraph<VertexType, EdgeType>::deleteEdge(VertexType* v1, VertexType* v2) {
	bool result = false;

	try {
		result = graph->deleteEdge(getVertexIndex(v1), getVertexIndex(v2));
	}
	catch (const char* exception) {
		throw exception;
	}

	return result;
}

template<typename VertexType, typename EdgeType>
inline bool SimpleGraph<VertexType, EdgeType>::deleteEdgeByVertexIndexes(int v1, int v2) {
	bool result = false;

	try {
		result = graph->deleteEdge(v1, v2);
	}
	catch (const char* exception) {
		throw exception;
	}

	return result;
}

template<typename VertexType, typename EdgeType>
template<typename VertexNameType>
inline bool SimpleGraph<VertexType, EdgeType>::deleteEdgeByVertexNames(VertexNameType v1, VertexNameType v2) {
	bool result = false;
	VertexType* vertex1 = getVertexByName(v1);
	VertexType* vertex2 = getVertexByName(v2);

	try {
		result = graph->deleteEdge(getVertexIndex(vertex1), getVertexIndex(vertex2));
	}
	catch (const char* exception) {
		throw exception;
	}

	return result;
}


template<typename VertexType, typename EdgeType>
inline void SimpleGraph<VertexType, EdgeType>::toListGraph() {
	if (graph->isListGraph()) {
		throw "Граф уже в форме List-Граф";
		return;
	}

	Graph<VertexType, EdgeType>* listGraph = new ListGraph<VertexType, EdgeType>(graph->isDirected());

	for (auto vertex : graph->getVertexVector()) {
		listGraph->insertVertex(listGraph->getAmountOfVertices(), vertex);
	}

	SimpleGraph<VertexType, EdgeType>::EdgeIterator it = SimpleGraph<VertexType, EdgeType>::EdgeIterator(*this);

	for (it.begin(); !it.isOnEnd(); it++) {
		int v1 = getVertexIndex((*it)->getV1());
		int v2 = getVertexIndex((*it)->getV2());
		listGraph->insertEdge(v1, v2, *it);
	}

	delete this->graph;
	this->graph = listGraph;
}

template<typename VertexType, typename EdgeType>
inline void SimpleGraph<VertexType, EdgeType>::toMatrixGraph() {
	if (!graph->isListGraph()) {
		throw "Граф уже в форме Matrix-Граф";
		return;
	}

	Graph<VertexType, EdgeType>* matrixGraph = new MatrixGraph<VertexType, EdgeType>(graph->isDirected());

	for (auto vertex : graph->getVertexVector()) {
		matrixGraph->insertVertex(matrixGraph->getAmountOfVertices(), vertex);
	}

	SimpleGraph<VertexType, EdgeType>::EdgeIterator it = SimpleGraph<VertexType, EdgeType>::EdgeIterator(*this);

	for (it.begin(); !it.isOnEnd(); it++) {
		int v1 = getVertexIndex((*it)->getV1());
		int v2 = getVertexIndex((*it)->getV2());
		matrixGraph->insertEdge(v1, v2, *it);
	}

	delete this->graph;
	this->graph = matrixGraph;
}


template<typename VertexType, typename EdgeType>
inline void SimpleGraph<VertexType, EdgeType>::print(bool printWithNames) {
	graph->print(printWithNames);
}


template<typename VertexType, typename EdgeType>
inline double SimpleGraph<VertexType, EdgeType>::saturationCoefficient() {
	return graph->saturationCoefficient();
}

template<typename VertexType, typename EdgeType>
inline Graph<VertexType, EdgeType>* SimpleGraph<VertexType, EdgeType>::getGraph() {
	return graph;
}

template<typename VertexType, typename EdgeType>
inline bool SimpleGraph<VertexType, EdgeType>::isDirected() {
	return graph->isDirected();
}

template<typename VertexType, typename EdgeType>
inline bool SimpleGraph<VertexType, EdgeType>::isListGraph() {
	return graph->isListGraph();
}

template<typename VertexType, typename EdgeType>
inline int SimpleGraph<VertexType, EdgeType>::getAmountOfVertices() {
	return graph->getAmountOfVertices();
}

template<typename VertexType, typename EdgeType>
inline int SimpleGraph<VertexType, EdgeType>::getAmountOfEdges() {
	return graph->getAmountOfEdges();
}