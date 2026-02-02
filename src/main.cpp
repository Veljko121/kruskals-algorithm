#include <vector>
#include <iostream>
#include <chrono>
#include "types.hpp"
#include "kruskal.hpp"

using namespace std;

int main() {
    cout << "Generating graph..." << flush;
    Graph graph = generate_graph(7000, 1000000);
    cout << " finished." << endl;

    cout << "Sequential..." << flush;
    auto start = chrono::high_resolution_clock::now();
    vector<Edge> mst_sequential = kruskal_sequential(graph);
    auto end = chrono::high_resolution_clock::now();
    auto seq_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << " finished, time: " << seq_time << " ms"<< endl;

    cout << "Parallel..." << flush;
    start = chrono::high_resolution_clock::now();
    vector<Edge> mst_omp = kruskal_omp(graph);
    end = chrono::high_resolution_clock::now();
    auto omp_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << " finished, time: " << omp_time << " ms"<< endl;

    printf("Speedup: %.2fx\n", (double)seq_time / omp_time);

    return 0;
}
