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

unsigned int greedyOld(Graph* graph) {
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
        minRes = min;
    }
    return minRes;
}

unsigned int greedyNew(Graph* graph) {
    // greedy algorithm
    unsigned int v1, v2, minRes;
    for(unsigned int iteration = 1; iteration <= graph->getVertecies()-1; iteration++) {
        unsigned int min = 99999;
        for (unsigned int outer = 1; outer <= graph->getVertecies()-1; outer++) {
            if (graph->getAdjLists()[outer-1] == NULL) continue;
            for (unsigned int inner = outer + 1; inner <= graph->getVertecies(); inner++) {
                if (graph->getAdjLists()[inner-1] == NULL) continue;
                unsigned int temp = graph->theoreticalMergeVertices(outer, inner);
                if (temp < min) {
                    min = temp;
                    v1 = outer;
                    v2 = inner;
                }
            }
        }

        // cout << "Merging " << v1 << " and " << v2 << endl;
        graph->realMergeVertices(v1, v2);
        // graph->print();

        minRes = min;
    }
    return minRes;
}

double measure(string fileName, unsigned int algo(Graph*)) {
    double average = 0;
    unsigned int twinWidth;
    for(int i = 0; i < 1; i++) {
        Graph* graph = loadGraph(fileName);
        // graph->print();
        auto start = std::chrono::high_resolution_clock::now();
        twinWidth = algo(graph);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        average = (average*i + elapsed.count())/(i+1);
        delete graph;
    }
    if (average * 1000 < 1000) {
        cout << fileName << ", runtime: " << average*1000 << "ms, Twin-Width: " << twinWidth << endl;
    } else if (average/60 < 1) {
        cout << fileName << ", runtime: " << average << "s, Twin-Width: " << twinWidth << endl;
    } else if (average/60) {
        cout << fileName << ", runtime: " << average/60 << "m, Twin-Width: " << twinWidth << endl;
    }

    return average;
}

void predefinedMerges(string fileName) {
    Graph* graph = loadGraph(fileName);
    vector<vector<int>> merges = {{7, 1}, {9, 3}, {10, 4}, {10, 5}, {21, 17}, {25, 24}, {25, 20}, {23, 19}, {22, 18}, {25, 23}, {21, 16}, {15, 10}, {15, 14}, {8, 2}, {25, 22}, {15, 9}, {15, 13}, {25, 21}, {8, 7}, {25, 12}, {25, 15}, {25, 11}, {25, 8}, {25, 6}};
    for (int i = 0; i < merges.size(); i++) {
        // graph->printSlim();
        // cout << endl;
        graph->realMergeVertices(merges[i][0], merges[i][1]);
        // cout << '"' << "merged: " << merges[i][0] << " and " << merges[i][1] << ", current max RedDeg: " << graph->getMDCE() << '"' << endl;
    }
    // cout << "Twin-Width result: " << graph->getMDCE() << endl;
    delete graph;
}

int main() {
    // vector<int> sol = {1, 2, 0, 0, 3, 0, 2, 4, 1, 2};
    // double average0 = 0;
    string naming = "heuristic/he"; // "tiny-set/tiny";
    for(int i = 1; i < 11; i++) {
        string fileName;
        if(i < 10)
            fileName = naming + "00";
        else if(i < 100)
            fileName = naming + "0";
        else
            fileName = naming;

        measure(fileName + to_string(i) + ".gr", greedyNew);

        // measure
        /*
        double average1 = measure(fileName + to_string(i+1) + ".gr", sol[i], greedyOld);
        double average2 = measure(fileName + to_string(i+1) + ".gr", sol[i], greedyNew);
        double average3 = abs((average1-average2)/average2);
        average0 = (average0*i+average3)/(i+1);
        cout << "diff: " << average3*100 << "%" << endl;
        */

        // predefinedMerges(fileName + to_string(i) + ".gr");
    }
    // cout << "New algo is " << average0*100 << "% faster than old one" << endl;

    return 0;
}