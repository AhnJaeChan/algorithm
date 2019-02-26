#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>

#include "Graph.h"
#include "ArgStruct.h"

using namespace std;

int main(int argc, char **argv) {
    string input_file_name = argv[1];

    string output_file_name("output.txt");

    ifstream input_stream(input_file_name);

    unsigned long V;
    int E;
    input_stream >> V; // Vertex size
    input_stream >> E; // Edge size

    Graph graph(V);

    uint64_t src, dest; // src -> dest (Starting node -> End node)
    uint64_t w; // weight

    // Graph build
    for (int i = 0; i < E; i++) {
        input_stream >> src >> dest >> w;
        graph.addEdge(src, dest, w);
    }

    int P, N;
    uint64_t index;

    input_stream >> P; // Problem size

    uint64_t answer[P];
    pthread_t prob_threads[P];

    // Problem solve
    for (int i = 0; i < P; i++) {
        input_stream >> N; // # of vertices

        ArgStruct args(&graph);

        unordered_set<uint64_t> subset;
        for (int j = 0; j < N; j++) {
            input_stream >> index;
            subset.insert(index);
        }

        args.setSubset(&subset);

        pthread_create(&prob_threads[i], nullptr, &Graph::find_wrapper, (void *) &args);
        pthread_join(prob_threads[i], (void **) &answer[i]);
    }
    input_stream.close();

    ofstream output_stream(output_file_name);

    for (uint64_t const &val: answer) {
        output_stream << val << endl;
    }
    output_stream.close();

    return 0;
}
