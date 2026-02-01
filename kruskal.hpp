#pragma once

#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include "types.hpp"
#include "disjoint_set.hpp"

using namespace std;

vector<Edge> kruskal(const Graph& graph) {
    // extract edges and deduplicate
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

    // sort edges by weight ascending
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        if (a.weight != b.weight) return a.weight < b.weight;
        if (a.u != b.u) return a.u < b.u;
        return a.v < b.v;
    });

    // extract vertices
    vector<string> vertices;
    for (const auto& [vertex, _] : graph) {
        vertices.push_back(vertex);
    }

    // initialize disjointset
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
