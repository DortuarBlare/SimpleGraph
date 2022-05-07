#include <iostream>
#include "SimpleGraph.h"
#include "Vertex.h"
#include "Edge.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    SimpleGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>* simpleGraph = 
        new SimpleGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>();
    
    ListGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::EdgeIterator listEIt;

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
        cout << "Коэф. насыщенности:\t" << simpleGraph->saturationCoefficient() << endl << endl
             << "1) Визуализировать граф" << endl
             << "2) Операции над вершиной" << endl
             << "3) Операции над ребром" << endl
             << "4) Итератор вершин" << endl
             << "5) Итератор рёбер" << endl
             << "6) Итератор исходящих рёбер" << endl
             << "0) Выход" << endl
             << endl << "> ";

        cin >> menuChoice;

        switch (menuChoice) {
        case 1: {
            bool namesOrIndexes;
            cout << "Способ визуализации (имена - 1, индексы - 0): ";
            cin >> namesOrIndexes;

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
        case 5: {
            bool exitEdgeIteratorMenu = false;
            listEIt = ListGraph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::EdgeIterator(
                static_cast<
                    ListGraph<
                        Vertex<string, int>, 
                        Edge<Vertex<string, int>, int, int>
                    >*
                >
                (simpleGraph->getGraph())
            );

            while (!exitEdgeIteratorMenu) {
                system("cls");
                cout << "Итератор рёбер: " << endl
                     << "1) Установить итератор на начальное ребро" << endl
                     << "2) Установить итератор на конечное ребро" << endl
                     << "3) Переход к следующей позиции" << endl
                     << "4) Просмотреть текущее ребро" << endl
                     << "0) Выход в главное меню" << endl
                     << endl << "> ";
                cin >> menuChoice;

                try {
                    switch (menuChoice) {
                    case 1: {
                        listEIt.begin();
                        break;
                    }
                    case 2: {
                        break;
                    }
                    case 3: {
                        listEIt++;
                        break;
                    }
                    case 4: {
                        cout << **listEIt << endl;
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
        case 0:
            return 0;
        default:
            break;
        }
    }
}