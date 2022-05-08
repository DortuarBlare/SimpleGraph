#pragma once

template<typename NameType, typename DataType>
class Vertex {
private:
	NameType name;
	DataType data;
	
public:
	Vertex();
	Vertex(NameType name, DataType data);

	template<typename NameType, typename DataType>
	friend ostream& operator<<(ostream& os, const Vertex<NameType, DataType>& output);

	template<typename NameType, typename DataType>
	friend istream& operator>>(istream& is, Vertex<NameType, DataType>& input);

	NameType getName();
	DataType getData();
	void setName(NameType name);
	void setData(DataType data);
};

template<typename NameType, typename DataType>
inline Vertex<NameType, DataType>::Vertex() {}

template<typename NameType, typename DataType>
inline Vertex<NameType, DataType>::Vertex(NameType name, DataType data) {
	this->name = name;
	this->data = data;
}

template<typename NameType, typename DataType>
inline ostream& operator<<(ostream& os, const Vertex<NameType, DataType>& output) {
	os << '{' << endl;
	os << "Имя вершины: " << output.name << endl;
	os << "Данные вершины: " << output.data << endl;
	os << '}' << endl;

	return os;
}

template<typename NameType, typename DataType>
inline istream& operator>>(istream& is, Vertex<NameType, DataType>& input) {
	cout << "Имя вершины: ";
	is >> input.name;
	cout << "Данные вершины: ";
	is >> input.data;

	return is;
}

template<typename NameType, typename DataType>
inline NameType Vertex<NameType, DataType>::getName() { return name; }

template<typename NameType, typename DataType>
inline DataType Vertex<NameType, DataType>::getData() { return data; }

template<typename NameType, typename DataType>
inline void Vertex<NameType, DataType>::setName(NameType name) { this->name = name; }

template<typename NameType, typename DataType>
inline void Vertex<NameType, DataType>::setData(DataType data) { this->data = data; }
