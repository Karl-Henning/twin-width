#include "graph.h"

#include <iostream>

using namespace std;
#include <fstream>
#include <chrono>
#include <tuple>
#include <climits>

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
    for(unsigned int iteration = 1; iteration < graph->getVertecies(); iteration++) {
        unsigned int min = 99999;
        for (unsigned int outer = 1; outer < graph->getVertecies(); outer++) {
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

        graph->realMergeVertices(v1, v2);

        graph->printSlim();
        // cout << '"' << "merged: " << v1 << " and " << v2 << ", current max RedDeg: " << graph->getMDCE() << '"' << endl;


        minRes = min;
    }
    return minRes;
}

unsigned int newAlgo(Graph* graph) {
    // algorithm 1.0

    // graph->printSlim();
cout << "init..." << endl;
    // store most optimal Merge for each vertex in array (redDeg after merge, merged with vertex)
    auto minMerges = vector<tuple<int, int>>(graph->getVertecies());
    for (unsigned int vertex1 = 1; vertex1 <= graph->getVertecies(); vertex1++) {
	auto start = std::chrono::high_resolution_clock::now();
    minMerges[vertex1-1] = graph->getOptimalMerge(vertex1);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    auto duration = elapsed.count();

    if (duration * 1000 < 1000) {
        cout << "duration: " << duration*1000 << "ms" << endl;
    } else if (duration/60 < 1) {
        cout << "duration: " << duration << "s" << endl;
    } else if (duration/60) {
        cout << "duration: " << duration/60 << "m" << endl;
    }

    }

    cout << "done with init" << endl;

    // merge vertices with lowest redDeg
    for(unsigned int iteration = 1; iteration < graph->getVertecies(); iteration++) {
        // get optimal merge (redDeg after merge, target, del)
        tuple<int, int, int> optimalMerge = make_tuple(INT_MAX, 0, 0);
        for (unsigned int vertex2 = 1; vertex2 < graph->getVertecies(); vertex2++) {
            if (graph->getAdjLists()[vertex2-1] == nullptr) {
                continue;
            }

            auto merge = minMerges[vertex2-1];

            // remove vertex with empty adjLists
            if (get<0>(merge) == INT_MAX) {
                graph->deleteVertex(vertex2);
                break;
            }

            if (get<0>(merge) < get<0>(optimalMerge)) {
                optimalMerge = make_tuple(get<0>(merge), vertex2, get<1>(merge));
            }
            if (get<0>(optimalMerge) == 0) {
                break;
            }
        }

        if (get<0>(optimalMerge) == INT_MAX) {
            continue;
        }

        auto delAdjList = *graph->getAdjLists()[get<2>(optimalMerge)-1];

        // perform merge
        int twinWidth1 = graph->theoreticalMergeVertices(get<1>(optimalMerge), get<2>(optimalMerge));
        int twinWidth2 = graph->realMergeVertices(get<1>(optimalMerge), get<2>(optimalMerge));
        if (twinWidth1 != twinWidth2) {
            cout << "ERROR: twinWidth1 != twinWidth2" << endl;
        }

        // graph->printSlim();
        // cout << '"' << "merged: " << get<1>(optimalMerge) << " and " << get<2>(optimalMerge) << ", current max RedDeg: " << graph->getMDCE() << '"' << endl;

        minMerges[get<2>(optimalMerge)-1] = make_tuple(INT_MAX, 0);

        // update target and it's neighbours

        graph->updateMinMerges(&minMerges, get<1>(optimalMerge), delAdjList, get<2>(optimalMerge));
    }
    return graph->getMDCE();
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

    // graph->printSlim();

    vector<vector<int>> merges = {{13, 12}, {21, 14}, {24, 23}, {9, 8}, {25, 19}, {21, 16}, {21, 20}, {21, 15}, {22, 7}, {25, 17}, {18, 6}, {22, 5}, {25, 18}, {10, 9}, {24, 3}, {11, 4}, {13, 11}, {24, 13}, {24, 10}, {25, 1}, {25, 24}, {25, 22}, {25, 2}, {25, 21}};
    for (int i = 0; i < merges.size(); i++) {

        graph->realMergeVertices(merges[i][0], merges[i][1]);

        // graph->printSlim();
        cout << '"' << "merged: " << merges[i][0] << " and " << merges[i][1] << ", current max RedDeg: " << graph->getMDCE() << '"' << endl;
    }
    // cout << "Twin-Width result: " << graph->getMDCE() << endl;
    delete graph;
}

int main() {
    // vector<int> sol = {1, 2, 0, 0, 3, 0, 2, 4, 1, 2};
    // double average0 = 0;
    string naming = "heuristic-public/heuristic_"; // "heuristic/he";
    for(int i = 2; i <= 20; i += 2) {
        string fileName;
        if(i < 10)
            fileName = naming + "00";
        else if(i < 100)
            fileName = naming + "0";
        else
            fileName = naming;

        measure(fileName + to_string(i) + ".gr", newAlgo);

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
