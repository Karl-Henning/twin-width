//
// Created by Karl Henning on 20.10.22.
//

#include "graph.h"
#include <iostream>

Graph::Graph(unsigned int V) {
    if (V > INT_MAX){
        cout << "ERROR: Too many Vertecies! Method: Graph::Graph" << endl;
        exit(EXIT_FAILURE);
    }
    vertecies = V;
    maxDegreeColoredEdges = 0;
    adjLists = vector<list<int>*>(vertecies);
    for (unsigned int i = 0; i < vertecies; i++) {
        adjLists[i] = new list<int>;
    }
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
    // check if empty
    if(adjLists[adjList1-1]->empty()) {
        delete adjLists[adjList1-1];
        adjLists[adjList1-1] = nullptr;
        // done with result in 2
        return adjList2;
    } else {
        if(!adjLists[adjList2-1]->empty()){
            // merge 2 into 1
            // assumption: both lists will most of the time have almost the same lengths

            auto adjList1Iter = adjLists[adjList1-1]->begin();
            auto adjList2Iter = adjLists[adjList2-1]->begin();
            while(adjList1Iter != adjLists[adjList1-1]->end() && adjList2Iter != adjLists[adjList2-1]->end()) {
                if (abs(*adjList1Iter) == abs(*adjList2Iter)) {
                    // in L1 and L2
                    bool sgn = false;
                    if (*adjList2Iter < 0 && *adjList1Iter > 0) {
                        *adjList1Iter *= -1;
                        sgn = true;
                    }
                    adjList2Iter++;

                    // remove references
                    bool stop = false;
                    for (auto it = adjLists[abs(*adjList1Iter)-1]->begin(); it != adjLists[abs(*adjList1Iter)-1]->end(); ++it) {
                        // remove reference to L2
                        if (abs(*it) == adjList2) {
                            it = adjLists[abs(*adjList1Iter)-1]->erase(it);
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
                } else if (abs(*adjList1Iter) > abs(*adjList2Iter)) {
                    // only in L2
                    adjList1Iter = adjLists[adjList1-1]->insert(adjList1Iter, -abs(*adjList2Iter));
                    // remove reference to L2
                    // set new reference to -L1
                    bool inserted = false;
                    bool stop = false;
                    for (auto it = adjLists[abs(*adjList2Iter)-1]->begin(); it != adjLists[abs(*adjList2Iter)-1]->end(); ++it) {
                        // remove reference to L2
                        if (abs(*it) == adjList2) {
                            it = adjLists[abs(*adjList2Iter)-1]->erase(it);
                            if (stop) break;
                            else stop = true;
                        }
                        // set new reference to -L1
                        if (abs(*it) > adjList1 && !inserted) {
                            it = adjLists[abs(*adjList2Iter)-1]->insert(it, -adjList1);
                            if (stop) break;
                            else stop = true;
                            inserted = true;
                        }
                        // reference to -L1 has to be inserted at end
                        if(!inserted && it == adjLists[abs(*adjList2Iter)-1]->end()) {
                            adjLists[abs(*adjList2Iter)-1]->push_back(-adjList1);
                            break;
                        }
                    }
                    adjList2Iter++;
                } else {
                    // only in L1
                    if (*adjList1Iter > 0)
                        *adjList1Iter *= -1;
                    // keep reference but set flag
                    for (auto it = adjLists[abs(*adjList1Iter)-1]->begin(); it != adjLists[abs(*adjList1Iter)-1]->end(); ++it) {
                        // update reference to L1 if sgn
                        if (abs(*it) == adjList1 && *it > 0) {
                            *it *= -1;
                        }
                    }
                }
                adjList1Iter++;
            }

            for (; adjList1Iter != adjLists[adjList1-1]->end(); adjList1Iter++){
                // only in L1
                if (*adjList1Iter > 0)
                    *adjList1Iter *= -1;
                // keep reference but set flag
                for (auto it = adjLists[abs(*adjList1Iter)-1]->begin(); it != adjLists[abs(*adjList1Iter)-1]->end(); ++it) {
                    // update reference to L1 if sgn
                    if (abs(*it) == adjList1 && *it > 0) {
                        *it *= -1;
                    }
                }
            }


            // only in L2
            if(!adjLists[adjList2-1]->empty()) {
                for(; adjList2Iter != adjLists[adjList2-1]->end(); ++adjList2Iter) {
                    adjLists[adjList1-1]->push_back(-abs(*adjList2Iter));
                    bool inserted = false;
                    bool stop = false;
                    for (auto it = adjLists[abs(*adjList2Iter)-1]->begin(); it != adjLists[abs(*adjList2Iter)-1]->end(); ++it) {
                        // remove reference to L2
                        if (abs(*it) == adjList2) {
                            it = adjLists[abs(*adjList2Iter)-1]->erase(it);
                            if (stop) break;
                            else stop = true;
                        }
                        // set new reference to -L1
                        if (abs(*it) > adjList2 && !inserted) {
                            it = adjLists[abs(*adjList2Iter)-1]->insert(it, -adjList1);
                            if (stop) break;
                            else stop = true;
                            inserted = true;
                        }
                        // reference to -L1 has to be inserted at end
                        if(!inserted && it == adjLists[abs(*adjList2Iter)-1]->end()) {
                            adjLists[abs(*adjList2Iter)-1]->push_back(-adjList1);
                            break;
                        }
                    }
                }
            }
            unsigned int degree = getDCEOfVertex(adjList1);
            if (degree > maxDegreeColoredEdges)

                maxDegreeColoredEdges = degree;
            for (auto it = adjLists[adjList1-1]->begin(); it != adjLists[adjList1-1]->end(); ++it) {
                degree = getDCEOfVertex(abs(*it));
                if (degree > maxDegreeColoredEdges)
                    maxDegreeColoredEdges = degree;
            }
        }
        delete adjLists[adjList2-1];
        adjLists[adjList2-1] = nullptr;
        // done with result in 1
        return adjList1;
    }
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
    return maxDegreeColoredEdges;
}

Graph::~Graph() {
    for (unsigned int i = 0; i < vertecies; i++) {
        delete adjLists[i];
    }
}

Graph::Graph(const Graph &original) {
    vertecies = original.vertecies;
    maxDegreeColoredEdges = original.maxDegreeColoredEdges;
    adjLists = vector<list<int>*>(vertecies);
    for (unsigned int i = 0; i < vertecies; i++) {
        if (original.adjLists[i] == NULL)
            adjLists[i] = NULL;
        else
            adjLists[i] = new list<int>(*original.adjLists[i]);
    }
}

vector<list<int> *> Graph::getAdjLists() {
    return adjLists;
}
