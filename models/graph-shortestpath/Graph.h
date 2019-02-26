//
// Created by 안재찬 on 11/12/2018.
//

#ifndef GRAPH_SHORTESTPATH_GRAPH_H
#define GRAPH_SHORTESTPATH_GRAPH_H

#include <vector>
#include <unordered_set>
#include <set>
#include <queue>
#include <list>

#include "ArgStruct.h"

using namespace std;

class ArgStruct;

class Graph {
private:
    const uint64_t INF = UINT64_MAX;

    unsigned long V; // # of Vertices
    vector<pair<uint64_t, uint64_t>> *vertices; // Array representing vertices. Inside, is a pair representing adjacency with weight.

public:
    explicit Graph(unsigned long V);

    void addEdge(uint64_t src, uint64_t dest, uint64_t w); // Source node -> Destination node with weight w
    uint64_t findShortestPathAmongSubset(unordered_set<uint64_t> &subset);

    static void *find_wrapper(void *context) {
        ArgStruct *c = ((ArgStruct *) context);
        return (void *) c->graph->findShortestPathAmongSubset(*c->subset);
    }

    uint64_t dijkstra(uint64_t src, unordered_set<uint64_t> &subset); // Find shortest weight by dijkstra
    uint64_t dijkstra2(uint64_t src, unordered_set<uint64_t> &subset);
};

#endif //GRAPH_SHORTESTPATH_GRAPH_H
