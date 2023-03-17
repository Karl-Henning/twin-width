//
// Created by Karl Henning on 20.10.22.
//

#include "graph.h"
#include <iostream>
#include <algorithm>
#include <climits>
#include <tuple>

Graph::Graph(unsigned int V) {
    if (V > INT_MAX){
        cout << "ERROR: Too many Vertecies! Method: Graph::Graph" << endl;
        exit(EXIT_FAILURE);
    }
    vertecies = V;
    maxRedDeg = 0;
    adjLists = vector<list<int>*>(vertecies);
    for (unsigned int i = 0; i < vertecies; i++) {
        adjLists[i] = new list<int>;
    }
    redDeg = vector<unsigned int>(vertecies, 0);
}

void Graph::addEdge(unsigned int s, unsigned int d) {
    if (s > vertecies || d > vertecies ){
        cout << "ERROR: Index out of range! Method: Graph::addEdge" << endl;
        exit(EXIT_FAILURE);
    }
    // undirected graph
    // insert in a sorted list
    // TODO: check for unique value when entering an edge twice
    adjLists[s-1]->insert(std::lower_bound(adjLists[s-1]->begin(), adjLists[s-1]->end(), d), d);
    adjLists[d-1]->insert(std::lower_bound(adjLists[d-1]->begin(), adjLists[d-1]->end(), s), s);
}

void Graph::print() {
    for (unsigned int d = 0; d < adjLists.size(); ++d) {
        cout << "\n Vertex "
             << d+1 << ":";
        if (adjLists[d] != NULL){
            for (auto x : *(adjLists[d]))
                cout << " -> " << x;
        } else {
            cout << "--- does not exist ---";
        }
    }
    cout << endl;
}

void Graph::printSlim() {
    cout << "[";
    bool first1= true;
    for (unsigned int d = 0; d < adjLists.size(); ++d) {
        if (first1) {
            cout << "[";;
            first1 = false;
        } else
            cout << ", [";

        if (adjLists[d] != NULL){
            bool first2= true;
            for (auto it = adjLists[d]->begin(); it != adjLists[d]->end(); ++it) {
                if (first2) {
                    cout << *it;
                    first2 = false;
                } else
                    cout << ", " << *it;
            }
        } else
            cout << 0;
        cout << "]";
    }
    cout << "], ";
}

unsigned int Graph::mergeVertices(unsigned int adjList1, unsigned int adjList2) {
    if (adjList1 > vertecies || adjList2 > vertecies ){
        cout << "ERROR: Index out of range! Method: Graph::mergeVertices" << endl;
        exit(EXIT_FAILURE);
    }

    // remove self references
    for(auto it = adjLists[adjList1-1]->begin(); it != adjLists[adjList1-1]->end(); ++it) {
        if (abs(*it) == adjList2) {
            adjLists[adjList1-1]->erase(it);
            break;
        }
    }
    for(auto it = adjLists[adjList2-1]->begin(); it != adjLists[adjList2-1]->end(); ++it) {
        if (abs(*it) == adjList1) {
            adjLists[adjList2-1]->erase(it);
            break;
        }
    }

    // merge both lists

    // merge 2 into 1
    // cout << "merge " << adjList2 << " into " << adjList1 << endl;

    // assumption: both lists will most of the time have almost the same lengths

    auto targetIt = adjLists[adjList1-1]->begin();
    auto delIt = adjLists[adjList2-1]->begin();
    while(targetIt != adjLists[adjList1-1]->end() && delIt != adjLists[adjList2-1]->end()) {
        if (abs(*targetIt) == abs(*delIt)) {
            // in L1 and L2
            bool sgn = false;
            if (*delIt < 0 && *targetIt > 0) {
                *targetIt *= -1;
                sgn = true;
            }
            delIt++;

            // remove references
            bool stop = false;
            for (auto it = adjLists[abs(*targetIt)-1]->begin(); it != adjLists[abs(*targetIt)-1]->end(); ++it) {
                // remove reference to L2
                if (abs(*it) == adjList2) {
                    it = adjLists[abs(*targetIt)-1]->erase(it);
                    if(sgn || stop) break;
                    else stop = true;
                }

                // update reference to L1 if sgn
                if (abs(*it) == adjList1 && *it > 0 && sgn) {
                    *it *= -1;
                    if(stop) break;
                    else stop = true;
                }
            }
        } else if (abs(*targetIt) > abs(*delIt)) {
            // only in L2
            targetIt = adjLists[adjList1-1]->insert(targetIt, -abs(*delIt));
            // remove reference to L2
            // set new reference to -L1
            bool inserted = false;
            bool stop = false;
            for (auto it = adjLists[abs(*delIt)-1]->begin(); it != adjLists[abs(*delIt)-1]->end(); ++it) {
                // remove reference to L2
                if (abs(*it) == adjList2) {
                    it = adjLists[abs(*delIt)-1]->erase(it);
                    if (stop) break;
                    else stop = true;
                }
                // set new reference to -L1
                if (abs(*it) > adjList1 && !inserted) {
                    cout << abs(*delIt)-1 << ", " << adjLists.size() << endl;
                    it = adjLists[abs(*delIt)-1]->insert(it, -adjList1);
                    if (stop) break;
                    else stop = true;
                    inserted = true;
                }
                // reference to -L1 has to be inserted at end
                if(!inserted && it == adjLists[abs(*delIt)-1]->end()) {
                    adjLists[abs(*delIt)-1]->push_back(-adjList1);
                    break;
                }
            }
            delIt++;
        } else {
            // only in L1
            if (*targetIt > 0)
                *targetIt *= -1;
            // keep reference but set flag
            for (auto it = adjLists[abs(*targetIt)-1]->begin(); it != adjLists[abs(*targetIt)-1]->end(); ++it) {
                // update reference to L1 if sgn
                if (abs(*it) == adjList1 && *it > 0) {
                    *it *= -1;
                }
            }
        }
        targetIt++;
    }

    for (; targetIt != adjLists[adjList1-1]->end(); targetIt++){
        // only in L1
        if (*targetIt > 0)
            *targetIt *= -1;
        // keep reference but set flag
        for (auto it = adjLists[abs(*targetIt)-1]->begin(); it != adjLists[abs(*targetIt)-1]->end(); ++it) {
            // update reference to L1 if sgn
            if (abs(*it) == adjList1 && *it > 0) {
                *it *= -1;
            }
        }
    }

    // only in L2
    if(!adjLists[adjList2-1]->empty()) {
        for(; delIt != adjLists[adjList2-1]->end(); ++delIt) {
            adjLists[adjList1-1]->push_back(-abs(*delIt));
            bool inserted = false;
            bool stop = false;
            for (auto it = adjLists[abs(*delIt)-1]->begin(); it != adjLists[abs(*delIt)-1]->end(); ++it) {
                // remove reference to L2
                if (abs(*it) == adjList2) {
                    it = adjLists[abs(*delIt)-1]->erase(it);
                    if (stop) break;
                    else stop = true;
                }
                // set new reference to -L1
                if (abs(*it) > adjList2 && !inserted) {
                    it = adjLists[abs(*delIt)-1]->insert(it, -adjList1);
                    if (stop) break;
                    else stop = true;
                    inserted = true;
                }
                // reference to -L1 has to be inserted at end
                if(!inserted && it == adjLists[abs(*delIt)-1]->end()) {
                    adjLists[abs(*delIt)-1]->push_back(-adjList1);
                    break;
                }
            }
        }
    }
    unsigned int degree = getDCEOfVertex(adjList1);
    redDeg[adjList1-1] = degree;
    if (degree > maxRedDeg)
        maxRedDeg = degree;
    for (auto it = adjLists[adjList1-1]->begin(); it != adjLists[adjList1-1]->end(); ++it) {
        degree = getDCEOfVertex(abs(*it));
        redDeg[abs(*it)-1] = degree;
        if (degree > maxRedDeg)
            maxRedDeg = degree;
    }

    delete adjLists[adjList2-1];
    adjLists[adjList2-1] = nullptr;

    // done with result in 1
    return adjList1;
}

unsigned int Graph::getDCEOfVertex(unsigned int node) {
    unsigned int degree = 0;
    for (auto it = adjLists[node-1]->begin(); it != adjLists[node-1]->end(); ++it) {
        if (*it < 0) {
            degree += 1;
        }
    }
    return degree;
}

unsigned int Graph::getMDCE() {
    return maxRedDeg;
}

Graph::~Graph() {
    for (unsigned int i = 0; i < vertecies; i++) {
        delete adjLists[i];
    }
}

Graph::Graph(const Graph &original) {
    vertecies = original.vertecies;
    maxRedDeg = original.maxRedDeg;
    adjLists = vector<list<int>*>(vertecies);
    for (unsigned int i = 0; i < vertecies; i++) {
        if (original.adjLists[i] == NULL)
            adjLists[i] = NULL;
        else
            adjLists[i] = new list<int>(*original.adjLists[i]);
    }
    redDeg = original.redDeg;
}

vector<list<int> *> Graph::getAdjLists() {
    return adjLists;
}

unsigned int Graph::getVertecies() {
    return vertecies;
}

unsigned int Graph::theoreticalMergeVertices(unsigned int adjList1, unsigned int adjList2) {
    if (adjList1 > vertecies || adjList2 > vertecies ){
        cout << "ERROR: Index out of range! Method: Graph::theoreticalMergeVertices" << endl;
        cout << "adjList1: " << adjList1 << " adjList2: " << adjList2 << endl;
        exit(EXIT_FAILURE);
    }

    unsigned int target = adjList1;
    unsigned int del = adjList2;
    unsigned int targetCounter = redDeg[target-1];
    unsigned int maxRedDegTemp = maxRedDeg;

    auto targetIt = adjLists[target-1]->begin();
    auto delIt = adjLists[del-1]->begin();
    while(!(targetIt == adjLists[target-1]->end() && delIt == adjLists[del-1]->end())) {
        if (abs(*targetIt) == abs(*delIt) && targetIt != adjLists[target-1]->end() && delIt != adjLists[del-1]->end()) {
            // in both
            if(*targetIt > 0 && *delIt < 0) {
                targetCounter++;
            }
            delIt++;
            targetIt++;
        } else if (abs(*targetIt) > abs(*delIt) && delIt != adjLists[del-1]->end() || targetIt == adjLists[target-1]->end()) {
            // only in del
            if (abs(*delIt) != target) {
                if (*delIt > 0) {
                    // del is positive
                    if (maxRedDegTemp < redDeg[abs(*delIt) - 1]+1)
                        maxRedDegTemp++;
                }
                targetCounter++;
            }
            delIt++;
        } else {
            // only in target
            if (*targetIt > 0 && abs(*targetIt) != del) {
                // target is positive and != del
                targetCounter++;
                if (maxRedDegTemp < redDeg[abs(*targetIt)-1]+1)
                    maxRedDegTemp++;
            } else if (*targetIt < 0 && abs(*targetIt) == del) {
                // target is negative and == del
                targetCounter--;
            }
            targetIt++;
        }
    }

    if (maxRedDegTemp < targetCounter)
        maxRedDegTemp = targetCounter;

    return maxRedDegTemp;
}

int Graph::edgeValue(const int edge) {
    return abs(edge);
}

bool Graph::edgeIsBlack(const int edge) {
    if(edge > 0) return true;
    else return false;
}

bool Graph::edgeIsRed(const int edge) {
    if(edge < 0) return true;
    else return false;
}

void Graph::colourEdgeRed(int* edge1, int* edge2) {
    // color edge red
    *edge1 *= -1;
    *edge2 *= -1;
}

int* Graph::findEdge(list<int>* list, const int destination) {
    return &*std::find_if(list->begin(), list->end(), [&]( const int edge ){ return abs(edge) == destination; } );
}

void Graph::deleteEdge(list<int>* list, const int destination) {
    auto it = std::find_if(list->begin(), list->end(), [&]( const int e ){ return abs(e) == destination; } );
    list->erase(it);
}

void Graph::incrementRedDegree(int edge) {
    int value = redDeg[abs(edge)-1];
    redDeg[abs(edge)-1] = value+1;

    // TODO: could implement check for maxRedDeg here
}

void Graph::decrementRedDegree(int edge) {
    redDeg[abs(edge)-1]--;
}

void Graph::insertRedEdge(int vertex1, int vertex2) {
    vertex1 = abs(vertex1);
    vertex2 = abs(vertex2);

    auto list = adjLists[vertex1-1];
    auto it = std::find_if(list->begin(), list->end(), [&]( const int e ){ return abs(e) > vertex2; } );
    list->insert(it,-vertex2);

    list = adjLists[vertex2-1];
    it = std::find_if(list->begin(), list->end(), [&]( const int e ){ return abs(e) > vertex1; } );
    list->insert(it,-vertex1);
}

unsigned int Graph::realMergeVertices(unsigned int adjList1, unsigned int adjList2) {
    if (adjList1 > vertecies || adjList2 > vertecies ){
        cout << "ERROR: Index out of range! Method: Graph::realMergeVertices" << endl;
        cout << "adjList1: " << adjList1 << " adjList2: " << adjList2 << endl;
        exit(EXIT_FAILURE);
    }

    unsigned int target = adjList1;
    unsigned int del = adjList2;

    auto targetIt = adjLists[target-1]->begin();
    auto delIt = adjLists[del-1]->begin();
    while(targetIt != adjLists[target-1]->end() || delIt != adjLists[del-1]->end()) {
        // check if both vertices have an edge to n
        if (edgeValue(*targetIt) == edgeValue(*delIt) && targetIt != adjLists[target-1]->end() && delIt != adjLists[del-1]->end()) {
            // if edge from del to n is red
            if(edgeIsRed(*delIt)) {
                if(edgeIsBlack(*targetIt)) {
                    // color edge from target to n and from n to target red
                    colourEdgeRed(&*targetIt, findEdge(adjLists[edgeValue(*targetIt)-1], target));

                    // increment redDegreeCounter
                    incrementRedDegree(target);
                } else {
                    decrementRedDegree(*targetIt);
                }
            }

            // delete edge from n to del
            deleteEdge(adjLists[edgeValue(*targetIt)-1], del);

            delIt++;
            targetIt++;
        } else if (edgeValue(*targetIt) > edgeValue(*delIt) && delIt != adjLists[del-1]->end() || targetIt == adjLists[target-1]->end()) {
            // only in del
            if (abs(*delIt) != target) {
                // insert red edge from target to n
                insertRedEdge(target, *delIt);
                incrementRedDegree(target);
                if(edgeIsBlack(*delIt)) {
                    incrementRedDegree(*delIt);
                }

                // delete edge from n to del
                deleteEdge(adjLists[edgeValue(*delIt)-1], del);
            }

            delIt++;
        } else {
            // only in target
            if(abs(*targetIt) != del) {
                if(edgeIsBlack(*targetIt)) {
                    // target is black and != del
                    colourEdgeRed(&*targetIt, findEdge(adjLists[edgeValue(*targetIt)-1], target));

                    // increment redDegreeCounter
                    incrementRedDegree(target);
                    incrementRedDegree(*targetIt);
                }
                targetIt++;
            } else {
                if(edgeIsRed(*targetIt)) {
                    decrementRedDegree(target);
                }

                // delete edge
                targetIt = adjLists[edgeValue(*targetIt)-1]->erase(targetIt);
            }
        }
        int max = 0;
        for (auto it = redDeg.begin(); it != redDeg.end(); ++it) {
            if (*it > max)
                max = *it;
        }
    }

    delete adjLists[del-1];
    adjLists[del-1] = nullptr;


    int value = redDeg[target-1];
    if(maxRedDeg < value) {
        maxRedDeg = value;
    }
    // if implemented in incrementRedDegree this could be removed
    for (auto it = adjLists[target-1]->begin(); it != adjLists[target-1]->end(); ++it) {
        value = redDeg[edgeValue(*it)-1];
        if(maxRedDeg < value) {
            maxRedDeg = value;
        }
    }

    /*
    // checks
    // check for same signs / adjLists
    for (unsigned int index = 0; index < adjLists.size(); index++) {
        if (adjLists[index]) {
            for (auto edgeIt = adjLists[index]->begin(); edgeIt != adjLists[index]->end(); ++edgeIt) {
                auto it = findEdge(adjLists[edgeValue(*edgeIt) - 1], index+1);
                if (it == nullptr || *it / abs(*it) != *edgeIt / abs(*edgeIt)) {
                    cout << *it << ", " << *edgeIt << endl;
                    cout << "ERROR: Not same signs!" << endl;
                }
            }
        }
    }
    // check redDeg
    for (unsigned int index = 0; index < adjLists.size(); index++) {
        if (adjLists[index]) {
            int count = 0;
            for (auto edgeIt = adjLists[index]->begin(); edgeIt != adjLists[index]->end(); ++edgeIt) {
                if(edgeIsRed(*edgeIt)) {
                    count++;
                }
            }
            if (redDeg[index] != count) {
                cout << "ERROR: Wrong redDeg stored!" << endl;
            }
        }
    }
    */

    return maxRedDeg;
}

tuple<int, int> Graph::getOptimalMerge(unsigned int vertex) {
    // get first and second degree neighbours
    vector<unsigned int> allNeighbours;
    for (auto it = adjLists[vertex-1]->begin(); it != adjLists[vertex-1]->end(); ++it) {
        // add all first degree neighbours
        auto vertex = edgeValue(*it);
        allNeighbours.push_back(vertex);

        // add all second degree neighbours
        for (auto it2 = adjLists[vertex-1]->begin(); it2 != adjLists[vertex-1]->end(); ++it2) {
            if (edgeValue(*it2) == vertex) {
                continue;
            }
            auto vertex2 = edgeValue(*it2);
            if (find(allNeighbours.begin(), allNeighbours.end(), vertex2) == allNeighbours.end()) {
                allNeighbours.push_back(vertex2);
            }
        }
    }

    // get optimal merge
    tuple<int, int> optimalMerge = make_tuple(INT_MAX, 0);

    for (auto it = allNeighbours.begin(); it != allNeighbours.end(); ++it) {
        int redDeg = theoreticalMergeVertices(vertex, *it);
        if (redDeg == 0) {
            return make_tuple(redDeg, *it);
        } else if (redDeg < get<0>(optimalMerge)) {
            optimalMerge = make_tuple(redDeg, *it);
        }
    }

    return optimalMerge;
}

// TODO: doublecheck if we really need to update that much
void Graph::updateMinMerges(vector<tuple<int, int>>* minMerges, unsigned int vertex1, list<int> delAdjList, unsigned int delVertex) {
    // add all up to second degree neighbours of delVertex to allNeighbours
    // delVertex cann not be found in adjLists[delVertex-1]
    // delAdjList contains all first degree neighbours of delVertex
    vector<unsigned int> allNeighbours;
    for (auto it = delAdjList.begin(); it != delAdjList.end(); ++it) {
        // add all first degree neighbours
        auto vertex = edgeValue(*it);
        auto minMerge = (*minMerges)[vertex-1];
        if (get<1>(minMerge) == delVertex) {
            allNeighbours.push_back(vertex);
        }

        // add all second degree neighbours
        for (auto it2 = adjLists[vertex-1]->begin(); it2 != adjLists[vertex-1]->end(); ++it2) {
            auto vertex2 = edgeValue(*it2);
            auto minMerge2 = (*minMerges)[vertex2-1];
            if (get<1>(minMerge2) == delVertex) {
                if (find(allNeighbours.begin(), allNeighbours.end(), vertex2) == allNeighbours.end()) {
                    allNeighbours.push_back(vertex2);
                }
            }
        }
    }

    // update all vertecies in allNeighbours
    for (auto it = allNeighbours.begin(); it != allNeighbours.end(); ++it) {
        (*minMerges)[*it-1] = getOptimalMerge(*it);
    }
}

void Graph::deleteVertex(unsigned int vertex) {
    delete adjLists[vertex-1];
    adjLists[vertex-1] = nullptr;
}
