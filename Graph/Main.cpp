#include <iostream>
#include "SimpleGraph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Task2.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    SimpleGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>* simpleGraph = 
        new SimpleGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>();
    
	SimpleGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::VertexIterator vertexIterator;
	SimpleGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::EdgeIterator edgeIterator;
    SimpleGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::OutputEdgeIterator outputEdgeIterator;

    int menuChoice;
    bool exitCreateMenu = false;

    while (!exitCreateMenu) {
        system("cls");
        cout << "1) Создать пустой, неориентированный List-Граф" << endl
             << "2) Создать граф с V вершинами, без ребер, типа D, формы представления F" << endl
             << "3) Создать граф с V вершинами, с E случайными ребрами, типа D , формы F" << endl
             << "0) Выход" << endl
             << endl << "> ";
        cin >> menuChoice;

        switch (menuChoice) {
        case 1: {
            exitCreateMenu = true;
            break;
        }
        case 2: {
            int amountOfVertices;
            bool listGraph, directedGraph;

            cout << "Введите количество вершин: ";
            cin >> amountOfVertices;

            cout << "Введите тип графа (1 - Ориентированный, 0 - Неориентированный): ";
            cin >> directedGraph;

            cout << "Введите тип графа (1 - List-Граф, 0 - Matrix-Граф): ";
            cin >> listGraph;

            simpleGraph =  new SimpleGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>
                (amountOfVertices, directedGraph, listGraph);

            exitCreateMenu = true;
            break;
        }
        case 3: {
            int amountOfVertices, amountOfEdges;
            bool listGraph, directedGraph;

            cout << "Введите количество вершин: ";
            cin >> amountOfVertices;

            cout << "Введите количество рёбер: ";
            cin >> amountOfEdges;

            cout << "Введите тип графа (1 - Ориентированный, 0 - Неориентированный): ";
            cin >> directedGraph;

            cout << "Введите тип графа (1 - List-Граф, 0 - Matrix-Граф): ";
            cin >> listGraph;

            try {
                simpleGraph = new SimpleGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>
                    (amountOfVertices, amountOfEdges, directedGraph, listGraph);
            }
            catch (const char* exception) {
                cout << exception << endl;
                system("pause");
                break;
            }

            exitCreateMenu = true;
            break;
        }
        case 0:
            return 0;
        default:
            break;
        }
    }

    while (true) {
        system("cls");
        cout << "Текущее  состояние:\t";
        if (simpleGraph->isDirected()) cout << "Ориентированный ";
        else cout << "Неориентированный ";
        if (simpleGraph->isListGraph()) cout << "List-Граф";
        else cout << "Matrix-Граф";
        cout << endl << "Количество  вершин:\t" << simpleGraph->getAmountOfVertices() << endl;
        cout << "Количество   рёбер:\t" << simpleGraph->getAmountOfEdges() << endl;
        cout << "Коэф. насыщенности:\t" << simpleGraph->saturationCoefficient() << endl
             << endl
             << "1) Визуализировать граф" << endl
             << "2) Операции над вершиной" << endl
             << "3) Операции над ребром" << endl
             << "4) Итератор вершин" << endl
             << "5) Итератор рёбер" << endl
             << "6) Итератор исходящих рёбер" << endl
             << "7) Преобразовать в List-Граф" << endl
             << "8) Преобразовать в Matrix-Граф" << endl
             << "9) Задание 2" << endl
             << "0) Выход" << endl
             << endl << "> ";

        cin >> menuChoice;

        switch (menuChoice) {
        case 1: {
            bool namesOrIndexes = true;

			if (simpleGraph->isListGraph()) {
				cout << "Способ визуализации (имена - 1, индексы - 0): ";
				cin >> namesOrIndexes;
			}

            cout << endl;
            simpleGraph->print(namesOrIndexes);
            cout << endl;
            system("pause");
            break;
        }
        case 2: {
            bool exitVertexMenu = false;
            while (!exitVertexMenu) {
                system("cls");
                cout << "Текущее  состояние:\t";
                if (simpleGraph->isDirected()) cout << "Ориентированный ";
                else cout << "Неориентированный ";
                if (simpleGraph->isListGraph()) cout << "List-Граф";
                else cout << "Matrix-Граф";
                cout << endl << "Количество  вершин:\t" << simpleGraph->getAmountOfVertices() << endl;
                cout << "Количество   рёбер:\t" << simpleGraph->getAmountOfEdges() << endl;
                cout << "Коэф. насыщенности:\t" << simpleGraph->saturationCoefficient() << endl << endl
                     << "1) Добавить вершину в конец" << endl
                     << "2) Добавить вершину по индексу" << endl
                     << "3) Просмотреть вершину по индексу" << endl
                     << "4) Просмотреть вершину по имени" << endl
                     << "5) Редактировать вершину по индексу" << endl
                     << "6) Редактировать вершину по имени" << endl
                     << "7) Удалить вершину по индексу" << endl
                     << "8) Удалить вершину по имени" << endl
                     << "0) Выход в главное меню" << endl
                     << endl << "> ";
                cin >> menuChoice;

                try {
                    switch (menuChoice) {
                    case 1: {
                        simpleGraph->pushBackVertex();
                        break;
                    }
                    case 2: {
                        int index;
                        cout << "Введите индекс: ";
                        cin >> index;
                        simpleGraph->insertVertex(index);
                        break;
                    }
                    case 3: {
                        int index;
                        cout << "Введите индекс: ";
                        cin >> index;
                        cout << *simpleGraph->getVertexByIndex(index);
                        system("pause");
                        break;
                    }
                    case 4: {
                        string name;
                        cout << "Введите имя: ";
                        cin >> name;
                        cout << *simpleGraph->getVertexByName(name);
                        system("pause");
                        break;
                    }
                    case 5: {
                        int index;
                        cout << "Введите индекс: ";
                        cin >> index;
                        cin >> *simpleGraph->getVertexByIndex(index);
                        break;
                    }
                    case 6: {
                        string name;
                        cout << "Введите имя: ";
                        cin >> name;
                        cin >> *simpleGraph->getVertexByName(name);
                        break;
                    }
                    case 7: {
                        int index;
                        cout << "Введите индекс: ";
                        cin >> index;
                        simpleGraph->deleteVertexByIndex(index);
                        break;
                    }
                    case 8: {
                        string name;
                        cout << "Введите имя: ";
                        cin >> name;
                        simpleGraph->deleteVertexByName(name);
                        break;
                    }
                    case 0: {
                        exitVertexMenu = true;
                        break;
                    }
                    default:
                        break;
                    }
                }
                catch (const char* exception) {
                    cout << exception << endl;
                    system("pause");
                }
            }
            break;
        }
        case 3: {
            bool exitEdgeMenu = false;
            while (!exitEdgeMenu) {
                system("cls");
                cout << "Текущее  состояние:\t";
                if (simpleGraph->isDirected()) cout << "Ориентированный ";
                else cout << "Неориентированный ";
                if (simpleGraph->isListGraph()) cout << "List-Граф";
                else cout << "Matrix-Граф";
                cout << endl << "Количество  вершин:\t" << simpleGraph->getAmountOfVertices() << endl;
                cout << "Количество   рёбер:\t" << simpleGraph->getAmountOfEdges() << endl;
                cout << "Коэф. насыщенности:\t" << simpleGraph->saturationCoefficient() << endl << endl
                    << "1) Добавить ребро по индексам вершин" << endl
                    << "2) Добавить ребро по именам вершин" << endl
                    << "3) Просмотреть ребро по индексам вершин" << endl
                    << "4) Просмотреть ребро по именам вершин" << endl
                    << "5) Редактировать ребро по индексам вершин" << endl
                    << "6) Редактировать ребро по именам вершин" << endl
                    << "7) Удалить ребро по индексам вершин" << endl
                    << "8) Удалить ребро по именам вершин" << endl
                    << "0) Выход в главное меню" << endl
                    << endl << "> ";
                cin >> menuChoice;

                try {
                    switch (menuChoice) {
                    case 1: {
                        int v1, v2;
                        cout << "Введите индекс первой вершины: ";
                        cin >> v1;
                        cout << "Введите индекс второй вершины: ";
                        cin >> v2;
                        simpleGraph->insertEdgeByVertexIndexes(v1, v2);
                        break;
                    }
                    case 2: {
                        string v1, v2;
                        cout << "Введите имя первой вершины: ";
                        cin >> v1;
                        cout << "Введите имя второй вершины: ";
                        cin >> v2;
                        simpleGraph->insertEdgeByVertexNames(v1, v2);
                        break;
                    }
                    case 3: {
                        int v1, v2;
                        cout << "Введите индекс первой вершины: ";
                        cin >> v1;
                        cout << "Введите индекс второй вершины: ";
                        cin >> v2;
                        cout << *simpleGraph->getEdgeByVertexIndexes(v1, v2);
                        system("pause");
                        break;
                    }
                    case 4: {
                        string v1, v2;
                        cout << "Введите имя первой вершины: ";
                        cin >> v1;
                        cout << "Введите имя второй вершины: ";
                        cin >> v2;
                        cout << *simpleGraph->getEdgeByVertexNames(v1, v2);
                        system("pause");
                        break;
                    }
                    case 5: {
                        int v1, v2;
                        cout << "Введите индекс первой вершины: ";
                        cin >> v1;
                        cout << "Введите индекс второй вершины: ";
                        cin >> v2;
                        cin >> *simpleGraph->getEdgeByVertexIndexes(v1, v2);
                        break;
                    }
                    case 6: {
                        string v1, v2;
                        cout << "Введите имя первой вершины: ";
                        cin >> v1;
                        cout << "Введите имя второй вершины: ";
                        cin >> v2;
                        cin >> *simpleGraph->getEdgeByVertexNames(v1, v2);
                        break;
                    }
                    case 7: {
                        int v1, v2;
                        cout << "Введите индекс первой вершины: ";
                        cin >> v1;
                        cout << "Введите индекс второй вершины: ";
                        cin >> v2;
                        simpleGraph->deleteEdgeByVertexIndexes(v1, v2);
                        break;
                    }
                    case 8: {
                        string v1, v2;
                        cout << "Введите имя первой вершины: ";
                        cin >> v1;
                        cout << "Введите имя второй вершины: ";
                        cin >> v2;
                        simpleGraph->deleteEdgeByVertexNames(v1, v2);
                        break;
                    }
                    case 0: {
                        exitEdgeMenu = true;
                        break;
                    }
                    default:
                        break;
                    }
                }
                catch (const char* exception) {
                    cout << exception << endl;
                    system("pause");
                }
            }
            break;
        }
        case 4: {
            bool exitVertexIteratorMenu = false;

            try {
                vertexIterator = SimpleGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>
					::VertexIterator(*simpleGraph);
            }
            catch (const char* exception) {
                cout << exception << endl;
            }

            while (!exitVertexIteratorMenu) {
                system("cls");
                cout << "Итератор вершин: " << endl
                    << "1) Установить итератор на начало" << endl
                    << "2) Установить итератор на конец" << endl
                    << "3) Переход к следующей позиции" << endl
                    << "4) Просмотреть текущую вершину" << endl
                    << "0) Выход в главное меню" << endl
                    << endl << "> ";
                cin >> menuChoice;

                try {
                    switch (menuChoice) {
                    case 1: {
                        vertexIterator.begin();
                        break;
                    }
                    case 2: {
                        vertexIterator.end();
                        break;
                    }
                    case 3: {
                        vertexIterator++;
                        break;
                    }
                    case 4: {
                        cout << **vertexIterator << endl;
                        system("pause");
                        break;
                    }
                    case 0: {
                        exitVertexIteratorMenu = true;
                        break;
                    }
                    default:
                        break;
                    }
                }
                catch (const char* exception) {
                    cout << exception << endl;
                    system("pause");
                }

            }

            break;
        }
        case 5: {
            bool exitEdgeIteratorMenu = false;

            try {
                /*edgeIterator = ListGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::EdgeIterator(
                    static_cast<
                    ListGraph<
                    Vertex<string, int>,
                    Edge<Vertex<string, int>, int, int>
                    >*
                    >
                    (simpleGraph->getGraph())
                );//*/
				edgeIterator = SimpleGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>
					::EdgeIterator(*simpleGraph);
            }
            catch (const char* exception) {
                exitEdgeIteratorMenu = true;
                cout << exception << endl;
                system("pause");
            }

            while (!exitEdgeIteratorMenu) {
                system("cls");
                cout << "Итератор рёбер: " << endl
                     << "1) Установить итератор на начало" << endl
                     << "2) Установить итератор на конец" << endl
                     << "3) Переход к следующей позиции" << endl
                     << "4) Просмотреть текущее ребро" << endl
                     << "0) Выход в главное меню" << endl
                     << endl << "> ";
                cin >> menuChoice;

                try {
                    switch (menuChoice) {
                    case 1: {
                        edgeIterator.begin();
                        break;
                    }
                    case 2: {
                        edgeIterator.end();
                        break;
                    }
                    case 3: {
                        edgeIterator++;
                        break;
                    }
                    case 4: {
                        cout << **edgeIterator << endl;
                        system("pause");
                        break;
                    }
                    case 0: {
                        exitEdgeIteratorMenu = true;
                        break;
                    }
                    default:
                        break;
                    }
                }
                catch (const char* exception) {
                    cout << exception << endl;
                    system("pause");
                }
                
            }
            break;
        }
        case 6: {
            bool exitOutputEdgeIteratorMenu = false;
            int vertexIndex;

            cout << "Введите индекс вершины для итератора исходящих рёбер: ";
            cin >> vertexIndex;

            try {
                /*outputEdgeIterator = ListGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::OutputEdgeIterator(
                    static_cast<
                    ListGraph<
                    Vertex<string, int>,
                    Edge<Vertex<string, int>, int, int>
                    >*
                    >
                    (simpleGraph->getGraph()), vertexIndex
                );*/
                outputEdgeIterator = SimpleGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>
                    ::OutputEdgeIterator(*simpleGraph, vertexIndex);
            }
            catch (const char* exception) {
                exitOutputEdgeIteratorMenu = true;
                cout << exception << endl;
                system("pause");
            }

            while (!exitOutputEdgeIteratorMenu) {
                system("cls");
                cout << "Итератор исходящих рёбер: " << endl
                    << "1) Установить итератор на начало" << endl
                    << "2) Установить итератор на конец" << endl
                    << "3) Переход к следующей позиции" << endl
                    << "4) Просмотреть текущее ребро" << endl
                    << "0) Выход в главное меню" << endl
                    << endl << "> ";
                cin >> menuChoice;

                try {
                    switch (menuChoice) {
                    case 1: {
                        outputEdgeIterator.begin();
                        break;
                    }
                    case 2: {
                        outputEdgeIterator.end();
                        break;
                    }
                    case 3: {
                        outputEdgeIterator++;
                        break;
                    }
                    case 4: {
                        cout << **outputEdgeIterator << endl;
                        system("pause");
                        break;
                    }
                    case 0: {
                        exitOutputEdgeIteratorMenu = true;
                        break;
                    }
                    default:
                        break;
                    }
                }
                catch (const char* exception) {
                    cout << exception << endl;
                    system("pause");
                }

            }

            break;
        }
        case 7: {
            try {
                simpleGraph->toListGraph();
            }
            catch (const char* exception) {
                cout << exception << endl;
                system("pause");
            }
            break;
        }
        case 8: {
            try {
                simpleGraph->toMatrixGraph();
            }
            catch (const char* exception) {
                cout << exception << endl;
                system("pause");
            }
            break;
        }
        case 9: {
            Task2<Vertex<string, int>, Edge<Vertex<string, int>, int, int>> task2 = 
                Task2<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>(simpleGraph);

            int v1, v2;

            cout << "Введите первый индекс: ";
            cin >> v1;
            cout << "Введите второй индекс: ";
            cin >> v2;
            task2.IsVertexesDoublyConnected(simpleGraph, simpleGraph->getVertexByIndex(v1), simpleGraph->getVertexByIndex(v2));
            system("pause");
            break;
        }
        case 0:
            return 0;
        default:
            break;
        }
    }
}