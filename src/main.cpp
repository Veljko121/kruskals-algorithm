#include "types.hpp"
#include <vector>
#include <iostream>
#include <chrono>
#include "kruskal.hpp"
#include "kruskal_omp.hpp"

using namespace std;

int main() {
    printf("Generating graph...\n");
    Graph graph = generate_graph(5000, 1000000);
    printf("Generated graph.\n\n");

    printf("Sequential...\n");
    auto start = chrono::high_resolution_clock::now();
    vector<Edge> mst_sequential = kruskal(graph);
    auto end = chrono::high_resolution_clock::now();
    auto seq_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    printf("Time: %ld ms\n\n", seq_time);

    printf("Parallel...\n");
    start = chrono::high_resolution_clock::now();
    vector<Edge> mst_omp = kruskal_omp(graph);
    end = chrono::high_resolution_clock::now();
    auto omp_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    printf("Time: %ld ms\n\n", omp_time);

    printf("Speedup: %.2fx\n", (double)seq_time / omp_time);

    return 0;
}
