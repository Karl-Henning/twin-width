//
// Created by Karl Henning on 20.10.22.
//

#ifndef TWIN_WIDTH_GRAPH_H
#define TWIN_WIDTH_GRAPH_H

#include <list>
#include <vector>

using namespace std;

class Graph {
    vector<list<unsigned int>*> adjLists;
public:
    explicit Graph(int V);
    void addEdge(int s, int d);
    void print();
};

#endif //TWIN_WIDTH_GRAPH_H
