//
// Created by Karl Henning on 20.10.22.
//

#ifndef TWIN_WIDTH_GRAPH_H
#define TWIN_WIDTH_GRAPH_H

#include <list>
#include <vector>

using namespace std;

class Graph {
    vector<list<int>*> adjLists;
public:
    explicit Graph(unsigned int V);
    void addEdge(unsigned int s, unsigned int d);
    void print();
    void mergeVertices(unsigned int v1, unsigned int v2);
};

#endif //TWIN_WIDTH_GRAPH_H
