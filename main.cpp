#include "graph.h"

#include <iostream>

using namespace std;

int main() {
    Graph graph(7);

    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 3);
    graph.addEdge(2, 5);
    graph.addEdge(2, 7);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(3, 6);
    graph.addEdge(4, 6);
    graph.addEdge(4, 7);
    graph.addEdge(5, 6);
    graph.addEdge(6, 7);

    graph.print();
    cout << endl;

    graph.mergeVertices(2, 4);
    graph.print();
    cout << endl;

    graph.mergeVertices(5, 6);
    graph.print();
    cout << endl;

    graph.mergeVertices(2, 3);
    graph.print();
    cout << endl;

    graph.mergeVertices(5, 7);
    graph.print();
    cout << endl;

    graph.mergeVertices(1, 2);
    graph.print();
    cout << endl;

    graph.mergeVertices(1, 5);
    graph.print();
    cout << endl;
    return 0;
}