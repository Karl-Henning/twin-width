//
// Created by Karl Henning on 20.10.22.
//

#include <iostream>

#include "graph.h"
#include "node.h"

Graph::Graph(int V) {
    numVertices = V;
    for (int i = 0; i < V; i++) {
        adjLists.push_back(nullptr);
    }
}

void Graph::addEdge(int src, int dest) {
    auto it = adjLists.begin();

    // Add edge from s to d
    Node *newNode1 = new Node(dest);
    advance(it, src);
    newNode1->next = *it;
    *it = newNode1;


    it = adjLists.begin();

    // Add edge from d to s
    Node *newNode2 = new Node(src);
    advance(it, dest);
    newNode2->next = *it;
    *it = newNode2;
}

void Graph::print() {
    int v = 0;
    for (auto temp : adjLists) {
        std::cout << "Vertex " << v << ": " << std::endl;
        while (temp) {
            std::cout << temp->vertex;
            temp = temp->next;
            if (temp)
                std::cout << " -> ";
        }
        std::cout << std::endl;
        v++;
    }
}