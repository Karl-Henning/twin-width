#include <iostream>
#include <list>

#include "node.h"
#include "graph.h"

int main() {
    Graph graph(4);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 2);

    graph.print();

    return 0;
}