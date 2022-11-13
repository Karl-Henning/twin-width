#include "graph.h"

#include <iostream>

using namespace std;
#include <fstream>
#include <sstream>
#include "gtest/gtest.h"

Graph* loadGraph(string fileName) {
    // Create a text string, which is used to output the text file
    string myText;
    string word;

    // Read from the text file
    ifstream MyReadFile(fileName);
    MyReadFile >> myText;
    MyReadFile >> myText;
    MyReadFile >> myText;
    unsigned int vertices = stoi(myText);
    // cout << "Vertecies: " << vertices << endl;

    Graph* graph = new Graph(vertices);

    MyReadFile >> myText;
    unsigned int edges = stoi(myText);
    // cout << "Edges: " << edges << endl;

    int a, b;
    while (MyReadFile >> a >> b)
    {
        graph->addEdge(a, b);
    }

    // Close the file
    MyReadFile.close();

    return graph;
}

unsigned int greedy(Graph* graph) {
    // greedy algorithm
    unsigned int v1, v2, minRes;
    for(unsigned int iteration = 1; iteration <= graph->getVertecies()-1; iteration++) {
        unsigned int min = 99999;
        for (unsigned int outer = 1; outer <= graph->getVertecies()-1; outer++) {
            if (graph->getAdjLists()[outer-1] == NULL) continue;
            for (unsigned int inner = outer + 1; inner <= graph->getVertecies(); inner++) {
                if (graph->getAdjLists()[inner-1] == NULL) continue;
                Graph testGraph(*graph);
                testGraph.mergeVertices(outer, inner);
                if (testGraph.getMDCE() < min) {
                    min = testGraph.getMDCE();
                    v1 = outer;
                    v2 = inner;
                }
            }
        }
        graph->mergeVertices(v1, v2);
        // graph->print();
        // cout << "merged: " << v1 << " and " << v2 << endl;
        // cout << "Max deg: " << min << endl;
        minRes = min;
    }
    return minRes;
}

int main() {
    vector<int> sol = {1, 2, 0, 0, 3, 0, 2, 4, 1, 2};
    for(int i = 0; i < 10; i++) {
        string fileName;
        if(i+1 < 10)
            fileName = "tiny-set/tiny00";
        else
            fileName = "tiny-set/tiny0";
        Graph* graph = loadGraph(fileName + to_string(i+1) + ".gr");
        // graph->print();
        unsigned int twinWidth = greedy(graph);
        cout << "Twin Width: " << twinWidth << ", sol: " << sol[i];
        if (twinWidth < sol[i])
            cout << " WRONG!";
        cout << endl;
        delete graph;
    }

    return 0;
}