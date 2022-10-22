#include "graph.h"

#include <iostream>

using namespace std;

int main() {
    unsigned int vertices = 7;
    Graph graph(vertices);

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

    // greedy algorithm
    unsigned int v1, v2;
    for(unsigned int iteration = 1; iteration <= vertices-1; iteration++) {
        unsigned int min = 99999;
        for (unsigned int outer = 1; outer <= vertices-1; outer++) {
            if (graph.getAdjLists()[outer-1] == NULL) continue;
            for (unsigned int inner = outer + 1; inner <= vertices; inner++) {
                if (graph.getAdjLists()[inner-1] == NULL) continue;
                Graph testGraph(graph);
                testGraph.mergeVertices(outer, inner);
                if (testGraph.getMDCE() < min) {
                    min = testGraph.getMDCE();
                    v1 = outer;
                    v2 = inner;
                }
            }
        }
        graph.mergeVertices(v1, v2);
        graph.print();
        cout << "merged: " << v1 << " and " << v2 << endl;
        cout << "Max deg: " << min << endl;
    }

    /* Test sequence
    graph.mergeVertices(2, 4);
    graph.print();
    cout << "Max deg: " << graph.getMDCE() << endl;

    graph.mergeVertices(5, 6);
    graph.print();
    cout << "Max deg: " << graph.getMDCE() << endl;

    graph.mergeVertices(2, 3);
    graph.print();
    cout << "Max deg: " << graph.getMDCE() << endl;

    graph.mergeVertices(5, 7);
    graph.print();
    cout << "Max deg: " << graph.getMDCE() << endl;

    graph.mergeVertices(1, 2);
    graph.print();
    cout << "Max deg: " << graph.getMDCE() << endl;

    graph.mergeVertices(1, 5);
    graph.print();
    cout << "Max deg: " << graph.getMDCE() << endl;
    */

    return 0;
}