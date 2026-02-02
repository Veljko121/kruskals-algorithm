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
#include "utils.hpp"

using namespace std;

vector<Edge> kruskal_omp(const Graph& graph) {
    // extract edges and deduplicate
    vector<Edge> edges = extract_edges(graph);
    
    // sort edges
    parallel_sort_edges(edges);
    
    // extract vertices
    vector<string> vertices = extract_vertices(graph);
    
    // find MST
    vector<Edge> mst = find_mst(vertices, edges);
    
    return mst;
}
