#pragma once
#include "SimpleGraph.h"

template<typename VertexType, typename EdgeType>
class Task2 {
private:
	bool vectorHas(vector<int>& vec, int element);

public:
	bool VertexesDoublyConnected(SimpleGraph<VertexType, EdgeType>* graph, VertexType* v1, VertexType* v2);
	SimpleGraph<VertexType, EdgeType>* simpleGraph;
	SimpleGraph<VertexType, EdgeType>* resultGraph;

	Task2();
	Task2(SimpleGraph<VertexType, EdgeType>* simpleGraph);
	Task2(const Task2& task);
	~Task2();

	void Execute();
	void Set(SimpleGraph<VertexType, EdgeType>* simpleGraph);
	void Restart();
	void Result();
};

template<typename VertexType, typename EdgeType>
inline bool Task2<VertexType, EdgeType>::vectorHas(vector<int>& vec, int element) {
	for (auto index : vec) {
		/*if (index == vec.front())
			continue;*/

		if (index == element)
			return true;
	}

	return false;
}

template<typename VertexType, typename EdgeType>
inline bool Task2<VertexType, EdgeType>::VertexesDoublyConnected(SimpleGraph<VertexType, EdgeType>* graph, VertexType* v1, VertexType* v2) {
	typename SimpleGraph<VertexType, EdgeType>::OutputEdgeIterator it =
		typename SimpleGraph<VertexType, EdgeType>::OutputEdgeIterator(*graph, graph->getVertexIndex(v1));
	vector<int> visitedVertices;
	vector<int> firstPath;
	vector<int> secondPath;
	bool hasIndex = false;
	bool foundFirstPath = false, foundSecondPath = false;
	bool checkedAllVertexEdges = false;
	int attemptsNumber = 0;
	int indexV1 = graph->getVertexIndex(v1);
	int indexV2 = graph->getVertexIndex(v2);

	visitedVertices.push_back(indexV1);

	while (!foundFirstPath) {
		if (attemptsNumber >= graph->getAmountOfEdges())
			break;

		firstPath.clear();
		firstPath.push_back(indexV1);
		it = typename SimpleGraph<VertexType, EdgeType>::OutputEdgeIterator(*graph, indexV1);

		while (!it.isOnEnd()) {
			int currentIndexV1 = graph->getVertexIndex((*it)->getV1());
			int currentIndexV2 = graph->getVertexIndex((*it)->getV2());

			if (firstPath.back() == currentIndexV1) {
				if (indexV2 == currentIndexV2) {
					foundFirstPath = true;
					firstPath.push_back(indexV2);
					break;
				}

				if (checkedAllVertexEdges) {
					hasIndex = vectorHas(visitedVertices, currentIndexV2);

					if (!hasIndex) {
						firstPath.push_back(currentIndexV2);
						visitedVertices.push_back(currentIndexV2);
						it = typename SimpleGraph<VertexType, EdgeType>::OutputEdgeIterator(*graph, firstPath.back());
						checkedAllVertexEdges = false;
					}
				}
			}
			else {
				if (indexV2 == currentIndexV1) {
					foundFirstPath = true;
					firstPath.push_back(indexV2);
					break;
				}

				if (checkedAllVertexEdges) {
					hasIndex = vectorHas(visitedVertices, currentIndexV1);

					if (!hasIndex) {
						firstPath.push_back(currentIndexV1);
						visitedVertices.push_back(currentIndexV1);
						it = typename SimpleGraph<VertexType, EdgeType>::OutputEdgeIterator(*graph, firstPath.back());
						checkedAllVertexEdges = false;
					}
				}
			}

			it++;

			if (it.isOnEnd() && !checkedAllVertexEdges) {
				it.begin();
				checkedAllVertexEdges = true;
			}
			else if (it.isOnEnd() && checkedAllVertexEdges) {
				if (firstPath.size() >= 3)
					it = typename SimpleGraph<VertexType, EdgeType>::OutputEdgeIterator(*graph, firstPath[firstPath.size() - 2]);

				checkedAllVertexEdges = false;
				break;
			}

			hasIndex = false;
		}

		attemptsNumber++;
	}

	/*if (foundFirstPath) {
		graph->print(true);

		cout << endl << "Первый путь: ";
		for (auto index : firstPath)
			cout << index << " -> ";
		cout << "\b\b\b  " << endl;
	}
	else {
		cout << "Ни один путь не был найден :(" << endl;
		return false;
	}*/

	/*cout << "Посещенные вершины: ";
	for (auto index : visitedVertices)
		cout << index << " ";
	cout << endl << "Ушло " << attemptsNumber << " попыток" << endl;*/

	attemptsNumber = 0;
	visitedVertices.clear();
	visitedVertices.push_back(indexV1);
	/*if (firstPath.size() > 2) {
		firstPath.erase(firstPath.begin());
		firstPath.pop_back();
	}*/

	while (!foundSecondPath) {
		if (attemptsNumber >= graph->getAmountOfEdges())
			break;

		secondPath.clear();
		secondPath.push_back(indexV1);
		it = typename SimpleGraph<VertexType, EdgeType>::OutputEdgeIterator(*graph, indexV1);

		while (!it.isOnEnd()) {
			int currentIndexV1 = graph->getVertexIndex((*it)->getV1());
			int currentIndexV2 = graph->getVertexIndex((*it)->getV2());

			if (secondPath.back() == currentIndexV1) {
				if (indexV2 == currentIndexV2) {
					secondPath.push_back(indexV2);

					if (firstPath == secondPath) {
						secondPath.pop_back();
						it++;
						continue;
					}

					foundSecondPath = true;

					break;
				}

				if (!vectorHas(firstPath, currentIndexV2) &&
					!vectorHas(visitedVertices, currentIndexV2)) {
					secondPath.push_back(currentIndexV2);
					visitedVertices.push_back(currentIndexV2);
					it = typename SimpleGraph<VertexType, EdgeType>::OutputEdgeIterator(*graph, secondPath.back());
				}
			}
			else {
				if (indexV2 == currentIndexV1) {
					secondPath.push_back(indexV2);

					if (firstPath == secondPath) {
						secondPath.pop_back();
						it++;
						continue;
					}

					foundSecondPath = true;

					break;
				}

				if (!vectorHas(firstPath, currentIndexV1) &&
					!vectorHas(visitedVertices, currentIndexV1)) {
					secondPath.push_back(currentIndexV1);
					visitedVertices.push_back(currentIndexV1);
					it = typename SimpleGraph<VertexType, EdgeType>::OutputEdgeIterator(*graph, secondPath.back());
				}
			}

			it++;
			hasIndex = false;
		}

		attemptsNumber++;
	}

	/*if (foundSecondPath) {
		cout << endl << "Второй путь: ";
		for (auto index : secondPath)
			cout << index << " -> ";
		cout << "\b\b\b  " << endl;
	}
	else
		cout << "Второй путь не был найден :(" << endl;*/

	return foundFirstPath && foundSecondPath;
}

template<typename VertexType, typename EdgeType>
inline Task2<VertexType, EdgeType>::Task2() {}

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

	for (int i = 0; i < resultGraph->getAmountOfVertices() - 1; i++) {
		for (int j = i + 1; j < resultGraph->getAmountOfVertices() - 1; j++) {
			try {
				if (
					!VertexesDoublyConnected(
						resultGraph,
						resultGraph->getGraph()->getVertexVector().at(i),
						resultGraph->getGraph()->getVertexVector().at(j)
					)
					)
					resultGraph->insertEdge(
						resultGraph->getGraph()->getVertexVector().at(i),
						resultGraph->getGraph()->getVertexVector().at(j)
					);
			}
			catch (out_of_range const& exc) {}
			catch (const char* exception) {}
		}
	}
	cout << "Результирующий граф: " << endl;
	resultGraph->print(true);
}

template<typename VertexType, typename EdgeType>
inline void Task2<VertexType, EdgeType>::Set(SimpleGraph<VertexType, EdgeType>* simpleGraph) {
	this->simpleGraph = simpleGraph;
	Execute();
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