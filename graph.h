//
// Created by Karl Henning on 20.10.22.
//

#ifndef TWIN_WIDTH_GRAPH_H
#define TWIN_WIDTH_GRAPH_H

class Node;

#include <list>

class Graph {
private:
    int numVertices;
    std::list<Node*> adjLists;
public:
    explicit Graph(int V);
    void addEdge(int src, int dest);
    void print();
};

#endif //TWIN_WIDTH_GRAPH_H
