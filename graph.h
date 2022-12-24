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
    unsigned int maxRedDeg;
    vector<list<int>*> adjLists;
    vector<unsigned int> redDeg;
    int edgeValue(const int edge);
    bool edgeIsBlack(const int edge);
    bool edgeIsRed(const int edge);
    void colourEdgeRed(int* edge1, int* edge2);
    int* findEdge(list<int>* list, const int destination);
    void deleteEdge(list<int>* list, const int destination);
    void incrementRedDegree(int edge);
    void decrementRedDegree(int edge);
    void insertRedEdge(int edge1, int edge2);
public:
    explicit Graph(unsigned int V);
    Graph(const Graph& original);
    ~Graph();
    void addEdge(unsigned int s, unsigned int d);
    void print();
    void printSlim();
    unsigned int mergeVertices(unsigned int v1, unsigned int v2);
    unsigned int theoreticalMergeVertices(unsigned int v1, unsigned int v2);
    unsigned int realMergeVertices(unsigned int adjList1, unsigned int adjList2);
    unsigned int getDCEOfVertex(unsigned int node);
    unsigned int getMDCE();
    vector<list<int> *> getAdjLists();
    unsigned int getVertecies();
    tuple<int, int> getOptimalMerge(unsigned int vertex);
    void updateMinMerges(vector<tuple<int, int>>* minMerges, unsigned int vertex, list<int> delAdjList, unsigned int delVertex);
    void deleteVertex(unsigned int vertex);
};

#endif //TWIN_WIDTH_GRAPH_H
