//
// Created by Karl Henning on 20.10.22.
//

#include "graph.h"
#include <iostream>

Graph::Graph(int V) {
    adjLists = vector<list<unsigned int>*>(V);
    for (int i = 0; i < V; i++) {
        adjLists[i] = new list<unsigned int>;
    }
}

void Graph::addEdge(int s, int d) {
    adjLists[s]->push_back(d);
    adjLists[d]->push_back(s);
}

void Graph::print() {
    for (int d = 0; d < adjLists.size(); ++d) {
        cout << "\n Vertex "
             << d << ":";
        for (auto x : *(adjLists[d]))
            cout << "-> " << x;
    }
}