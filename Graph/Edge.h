#pragma once

template<typename VertexType, typename WeightType, typename DataType>
class Edge {
private:
	VertexType* v1; // Вершина, из которой исходит ребро
	VertexType* v2; // Вершина, в которую входит ребро
	WeightType weight;
	DataType data;

public:
	Edge();
	Edge(VertexType* v1, VertexType* v2);
	Edge(VertexType* v1, VertexType* v2, WeightType weight);
	Edge(VertexType* v1, VertexType* v2, WeightType weight, DataType data);

	template<typename VertexType, typename WeightType, typename DataType>
	friend ostream& operator<<(ostream& os, const Edge<VertexType, WeightType, DataType>& output);

	template<typename VertexType, typename WeightType, typename DataType>
	friend istream& operator>>(istream& is, Edge<VertexType, WeightType, DataType>& input);

	VertexType* getV1();
	VertexType* getV2();
	WeightType getWeight();
	DataType getData();
	void setWeight(WeightType weight);
	void setData(DataType data);
};

template<typename VertexType, typename WeightType, typename DataType>
inline Edge<VertexType, WeightType, DataType>::Edge() {}

template<typename VertexType, typename WeightType, typename DataType>
inline Edge<VertexType, WeightType, DataType>::Edge(VertexType* v1, VertexType* v2) {
	this->v1 = v1;
	this->v2 = v2;
}

template<typename VertexType, typename WeightType, typename DataType>
inline Edge<VertexType, WeightType, DataType>::Edge(VertexType* v1, VertexType* v2, WeightType weight) {
	this->v1 = v1;
	this->v2 = v2;
	this->weight = weight;
}

template<typename VertexType, typename WeightType, typename DataType>
inline Edge<VertexType, WeightType, DataType>::Edge(VertexType* v1, VertexType* v2, WeightType weight, DataType data) {
	this->v1 = v1;
	this->v2 = v2;
	this->weight = weight;
	this->data = data;
}

template<typename VertexType, typename WeightType, typename DataType>
inline ostream& operator<<(ostream& os, const Edge<VertexType, WeightType, DataType>& output) {
	os << '{' << endl;
	os << "Первая вершина: " << endl << *output.v1 << endl;
	os << "Вторая вершина: " << endl << *output.v2 << endl;
	os << "Вес ребра: " << output.weight << endl;
	os << "Данные ребра: " << output.data << endl;
	os << '}' << endl;

	return os;
}

template<typename VertexType, typename WeightType, typename DataType>
inline istream& operator>>(istream& is, Edge<VertexType, WeightType, DataType>& input) {
	cout << "Вес ребра: ";
	is >> input.weight;
	cout << "Данные ребра: ";
	is >> input.data;

	return is;
}

template<typename VertexType, typename WeightType, typename DataType>
inline VertexType* Edge<VertexType, WeightType, DataType>::getV1() {
	return v1;
}

template<typename VertexType, typename WeightType, typename DataType>
inline VertexType* Edge<VertexType, WeightType, DataType>::getV2() {
	return v2; 
}

template<typename VertexType, typename WeightType, typename DataType>
inline WeightType Edge<VertexType, WeightType, DataType>::getWeight() { 
	return weight;
}

template<typename VertexType, typename WeightType, typename DataType>
inline DataType Edge<VertexType, WeightType, DataType>::getData() { 
	return data;
}

template<typename VertexType, typename WeightType, typename DataType>
inline void Edge<VertexType, WeightType, DataType>::setWeight(WeightType weight) { 
	this->weight = weight;
}

template<typename VertexType, typename WeightType, typename DataType>
inline void Edge<VertexType, WeightType, DataType>::setData(DataType data) { 
	this->data = data;
}