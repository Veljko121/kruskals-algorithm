#include <random>
#include <chrono>
#include <set>
#include "types.hpp"
#include <random>
#include <chrono>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

Graph generate_graph(unsigned num_of_vertices, unsigned num_of_edges);

Graph generate_graph(unsigned num_of_vertices, unsigned num_of_edges) {
    // these checks ensure that dimensions are valid
    unsigned max_edges = num_of_vertices * (num_of_vertices - 1) / 2;
    if (num_of_edges < num_of_vertices - 1) num_of_edges = num_of_vertices - 1;
    if (num_of_edges > max_edges) num_of_edges = max_edges;

    // initialize random number generator and graph
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    Graph graph;
    
    // initialize (empty) neighbors for each vertex at the beginning
    for (unsigned i = 0; i < num_of_vertices; i++) {
        graph[to_string(i)] = {};
    }
    
    // make a random order of vertices
    vector<unsigned> order(num_of_vertices);
    iota(order.begin(), order.end(), 0); // fill order vector with 0,1,2,...,num_of_vertices
    shuffle(order.begin(), order.end(), rng); // shuffle vector, something like 5,2,3,7,...
    
    // connect vertices randomly first with vertices with lower order
    set<pair<int, int>> seen;
    for (unsigned i = 1; i < num_of_vertices; i++) {
        unsigned u = order[i];
        unsigned v = order[rng() % i];
        int weight = rng() % 100 + 1;

        string su = to_string(u);
        string sv = to_string(v);
        graph[su].push_back({sv, weight});
        graph[sv].push_back({su, weight});
        seen.insert({min(u, v), max(u, v)});
    }

    // connect remaining edges
    while (seen.size() < num_of_edges) {
        unsigned u = rng() % num_of_vertices;
        unsigned v = rng() % num_of_vertices;
        if (u == v) continue;

        pair<int,int> edge = {min(u, v), max(u, v)};
        if (seen.count(edge)) continue;  // skip duplicates

        int weight = rng() % 100 + 1;
        string su = to_string(u);
        string sv = to_string(v);
        graph[su].push_back({sv, weight});
        graph[sv].push_back({su, weight});
        seen.insert(edge);
    }

    return graph;
}
