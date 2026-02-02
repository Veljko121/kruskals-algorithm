#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include "types.hpp"

using namespace std;

// quicksort sorting algorithm
void quicksort_edges(vector<Edge>& arr, int left, int right, bool parallel, size_t threshold) {
    if (left >= right) return;
    
    auto compare = [](const Edge& a, const Edge& b) {
        if (a.weight != b.weight) return a.weight < b.weight;
        if (a.u != b.u) return a.u < b.u;
        return a.v < b.v;
    };
    
    Edge pivot = arr[left + (right - left) / 2];
    int i = left, j = right;
    
    while (i <= j) {
        while (compare(arr[i], pivot)) i++;
        while (compare(pivot, arr[j])) j--;
        
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    
    bool should_parallelize = parallel && (right - left > threshold);
    
    if (should_parallelize) {
        #pragma omp task shared(arr)
        quicksort_edges(arr, left, j, parallel, threshold);
        
        #pragma omp task shared(arr)
        quicksort_edges(arr, i, right, parallel, threshold);
        
        #pragma omp taskwait
    } else {
        quicksort_edges(arr, left, j, parallel, threshold);
        quicksort_edges(arr, i, right, parallel, threshold);
    }
}

// sequential sort only calls the quicksort_edges with no parallelization
void sequential_sort_edges(vector<Edge> &edges) {
    if (edges.empty()) return;
    quicksort_edges(edges, 0, edges.size() - 1, false, 0);
}

// parallel sort calls the method with pragma omp parallel
void parallel_sort_edges(vector<Edge> &edges) {
    if (edges.empty()) return;
    
    const size_t SEQUENTIAL_THRESHOLD = 100;
    
    #pragma omp parallel
    {
        #pragma omp single
        quicksort_edges(edges, 0, edges.size() - 1, true, SEQUENTIAL_THRESHOLD);
    }
}
