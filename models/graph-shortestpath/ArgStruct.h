//
// Created by 안재찬 on 16/12/2018.
//

#ifndef GRAPH_SHORTESTPATH_ARGSTRUCT_H
#define GRAPH_SHORTESTPATH_ARGSTRUCT_H

#include "Graph.h"
#include <unordered_set>

using namespace std;

class Graph;

class ArgStruct {
public:
    Graph *graph;
    unordered_set<uint64_t> *subset; // Vertex list for problem

    explicit ArgStruct(Graph *graph) {
        this->graph = graph;
    }

    void setSubset(unordered_set<uint64_t> *subset) {
        this->subset = subset;
    }
};

#endif //GRAPH_SHORTESTPATH_ARGSTRUCT_H
