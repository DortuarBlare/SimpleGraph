#pragma once
#include "SimpleGraph.h"

template<typename VertexType, typename EdgeType>
class Task2 {
private:

public:
	bool IsVertexesDoublyConnected(SimpleGraph<VertexType, EdgeType>* graph, VertexType* v1, VertexType* v2);
	SimpleGraph<VertexType, EdgeType>* simpleGraph;
	SimpleGraph<VertexType, EdgeType>* resultGraph;

	Task2(SimpleGraph<VertexType, EdgeType>* simpleGraph);
	Task2(const Task2& task);
	~Task2();

	void Execute();
	void Set(SimpleGraph<VertexType, EdgeType>* simpleGraph);
	void Restart();
	void Result();
};

template<typename VertexType, typename EdgeType>
inline bool Task2<VertexType, EdgeType>::IsVertexesDoublyConnected(SimpleGraph<VertexType, EdgeType>* graph, VertexType* v1, VertexType* v2) {
	/*typename SimpleGraph<VertexType, EdgeType>::EdgeIterator it = typename SimpleGraph<VertexType, EdgeType>::EdgeIterator(*resultGraph);

	for (it.begin(); !it.isOnEnd(); it++) {
		int v1 = getVertexIndex((*it)->getV1());
		int v2 = getVertexIndex((*it)->getV2());
		listGraph->insertEdge(v1, v2, *it);
	}*/
	typename SimpleGraph<VertexType, EdgeType>::OutputEdgeIterator it =
		typename SimpleGraph<VertexType, EdgeType>::OutputEdgeIterator(*graph, graph->getVertexIndex(v1));
	vector<int> path;
	bool hasIndex = false;
	bool foundPath = false;

	path.push_back(graph->getVertexIndex(v1));
	for (; !it.isOnEnd(); it++) {
		if (path[path.size() - 1] == graph->getVertexIndex((*it)->getV1())) {
			if (graph->getVertexIndex(v2) == graph->getVertexIndex((*it)->getV2())) {
				foundPath = true;
				break;
			}

			for (auto index : path) {
				if (index == graph->getVertexIndex((*it)->getV2())) {
					hasIndex = true;
					break;
				}
			}

			if (!hasIndex) {
				path.push_back(graph->getVertexIndex((*it)->getV2()));
				it = typename SimpleGraph<VertexType, EdgeType>::OutputEdgeIterator(*graph, path[path.size() - 1]);
			}
		}
		else {
			if (graph->getVertexIndex(v2) == graph->getVertexIndex((*it)->getV1())) {
				foundPath = true;
				break;
			}

			for (auto index : path) {
				if (index == graph->getVertexIndex((*it)->getV1())) {
					hasIndex = true;
					break;
				}
			}

			if (!hasIndex) {
				path.push_back(graph->getVertexIndex((*it)->getV1()));
				it = typename SimpleGraph<VertexType, EdgeType>::OutputEdgeIterator(*graph, path[path.size() - 1]);
			}
		}
		hasIndex = false;
	}

	if (true) {
		graph->print(true);

		cout << endl /*<< graph->getVertexIndex(v1) << " -> "*/;
		for (auto index : path)
			cout << index << " -> ";
		//cout << graph->getVertexIndex(v2) << endl;
	}

	return false;
}

template<typename VertexType, typename EdgeType>
inline Task2<VertexType, EdgeType>::Task2(SimpleGraph<VertexType, EdgeType>* simpleGraph) {
	Set(simpleGraph);
}

template<typename VertexType, typename EdgeType>
inline Task2<VertexType, EdgeType>::Task2(const Task2& task) {
	delete this->simpleGraph;
	delete this->resultGraph;
	this->simpleGraph = new SimpleGraph<VertexType, EdgeType>(*task.simpleGraph);
	this->resultGraph = new SimpleGraph<VertexType, EdgeType>(*task.resultGraph);
}

template<typename VertexType, typename EdgeType>
inline Task2<VertexType, EdgeType>::~Task2() {
	delete resultGraph;
}


template<typename VertexType, typename EdgeType>
inline void Task2<VertexType, EdgeType>::Execute() {
	this->resultGraph = new SimpleGraph<VertexType, EdgeType>(*this->simpleGraph);
	//IsVertexesDoublyConnected(nullptr, nullptr);
}

template<typename VertexType, typename EdgeType>
inline void Task2<VertexType, EdgeType>::Set(SimpleGraph<VertexType, EdgeType>* simpleGraph) {
	this->simpleGraph = simpleGraph;
	//Execute();
}

template<typename VertexType, typename EdgeType>
inline void Task2<VertexType, EdgeType>::Restart() {
	Execute();
}

template<typename VertexType, typename EdgeType>
inline void Task2<VertexType, EdgeType>::Result() {
	if (resultGraph != nullptr)
		resultGraph->print();
}