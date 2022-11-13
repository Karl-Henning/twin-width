//
// Created by Karl Henning on 20.10.22.
//

#ifndef TWIN_WIDTH_GRAPH_H
#define TWIN_WIDTH_GRAPH_H

#include <list>
#include <vector>

using namespace std;

class Graph {
private:
    unsigned int vertecies;
    unsigned int maxDegreeColoredEdges;
    vector<list<int>*> adjLists;
    unsigned int getDCEOfVertex(unsigned int node);
    void updateReferences(unsigned int list);
public:
    Graph(unsigned int V);
    Graph(const Graph& original);
    ~Graph();
    void loadGraph(string file);
    void addEdge(unsigned int s, unsigned int d);
    void print();
    unsigned int mergeVertices(unsigned int v1, unsigned int v2);
    unsigned int getMDCE();
    vector<list<int>*> getAdjLists();
};

#endif //TWIN_WIDTH_GRAPH_H
