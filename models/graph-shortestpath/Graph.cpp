//
// Created by 안재찬 on 11/12/2018.
//

#include "Graph.h"

Graph::Graph(unsigned long V) {
    this->V = V;
    this->vertices = new vector<pair<uint64_t, uint64_t>>[V];
}

// Connect both ways to represent undirected graph.
void Graph::addEdge(uint64_t src, uint64_t dest, uint64_t w) {
    vertices[src].emplace_back(make_pair(dest, w));
    vertices[dest].emplace_back(make_pair(src, w));
}

uint64_t Graph::findShortestPathAmongSubset(unordered_set<uint64_t> &subset) {
    uint64_t min = INF;

    for (uint64_t const &v: subset) {
        uint64_t result = dijkstra2(v, subset);

        if (result < min) {
            min = result;
        }
    }

    return min;
}

uint64_t Graph::dijkstra(uint64_t src, unordered_set<uint64_t> &subset) {
    priority_queue<pair<uint64_t, uint64_t>, vector<pair<uint64_t, uint64_t>>, greater<pair<uint64_t, uint64_t>>> min_heap; // min heap
    min_heap.push(make_pair(0, src)); // pair(weight, vertex index) since the sorting of priority queue works that way.

    vector<uint64_t> dist(V, INF); // Set every distance to INF
    dist[src] = 0; // Set the source node's distance to 0

    while (!min_heap.empty()) {
        uint64_t u = min_heap.top().second;

        if (subset.find(u) != subset.end() && u != src) {
            return min_heap.top().first; // Weight of shortest path to one of the subset.
        }

        min_heap.pop();

        // For all adjacent of u.
        for (pair<uint64_t, uint64_t> const &adj : vertices[u]) {
            uint64_t v = adj.first; // vertex
            uint64_t weight = adj.second; // weight

            // If there is a shorter way,
            if (dist[v] > dist[u] + weight) {
                // update the distance.
                dist[v] = dist[u] + weight;
                min_heap.push(make_pair(dist[v], v));
            }
        }
    }

    return INF; // Could not reach one of the subset, calculate all of the distance between this an all the others.
}

uint64_t Graph::dijkstra2(uint64_t src, unordered_set<uint64_t> &subset) {
    set<pair<uint64_t, uint64_t>> min_heap; // min heap
    min_heap.insert(make_pair(0, src)); // pair(weight, vertex index) since the sorting of priority queue works that way.

    vector<uint64_t> dist(V, INF); // Set every distance to INF
    dist[src] = 0; // Set the source node's distance to 0

    while (!min_heap.empty()) {
        pair<uint64_t, uint64_t> min_node = *(min_heap.begin());
        min_heap.erase(min_heap.begin());

        uint64_t u = min_node.second;

        if (subset.find(u) != subset.end() && u != src) {
            return min_node.first; // Weight of shortest path to one of the subset.
        }

        // For all adjacent of u.
        for (pair<uint64_t, uint64_t> const &adj : vertices[u]) {
            uint64_t v = adj.first; // vertex
            uint64_t weight = adj.second; // weight

            // If there is a shorter way,
            if (dist[v] > dist[u] + weight) {
                // update the distance.
                dist[v] = dist[u] + weight;
                min_heap.insert(make_pair(dist[v], v));
            }
        }
    }

    return INF; // Could not reach one of the subset, calculate all of the distance between this an all the others.
}