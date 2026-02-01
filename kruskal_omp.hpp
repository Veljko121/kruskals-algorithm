#pragma once

#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <omp.h>
#include <parallel/algorithm>
#include "types.hpp"
#include "disjoint_set.hpp"
#include "sorting.hpp"

using namespace std;

vector<Edge> kruskal_omp(const Graph& graph) {
    vector<Edge> edges;
    set<tuple<string, string, int>> seen;
    for (const auto& [vertex, neighbors] : graph) {
        for (const auto& [neighbor, weight] : neighbors) {
            if (seen.find({neighbor, vertex, weight}) == seen.end()) {
                edges.push_back({vertex, neighbor, weight});
                seen.insert({vertex, neighbor, weight});
            }
        }
    }

    parallel_sort_edges(edges);

    // extract vertices
    vector<string> vertices;
    for (const auto& [vertex, _] : graph) {
        vertices.push_back(vertex);
    }

    DisjointSet disjointSet(vertices);

    vector<Edge> mst;
    for (const Edge& edge : edges) {
        string root_u = disjointSet.find(edge.u);
        string root_v = disjointSet.find(edge.v);

        if (root_u != root_v) {
            mst.push_back(edge);
            disjointSet.union_(root_u, root_v);
        }
    }

    return mst;
}
