#include <vector>
#include <omp.h>
#include <algorithm>
#include "types.hpp"

static inline bool edge_cmp(const Edge& a, const Edge& b) {
    if (a.weight != b.weight) return a.weight < b.weight;
    if (a.u != b.u) return a.u < b.u;
    return a.v < b.v;
}

void parallel_sort_edges(vector<Edge>& edges) {
    int nthreads = omp_get_max_threads();
    size_t n = edges.size();
    if (n < 10000 || nthreads == 1) {
        sort(edges.begin(), edges.end(), edge_cmp);
        return;
    }

    vector<size_t> starts(nthreads + 1);
    for (int i = 0; i <= nthreads; i++)
        starts[i] = i * n / nthreads;

    // --- Phase 1: local sorts ---
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        sort(edges.begin() + starts[tid],
             edges.begin() + starts[tid + 1],
             edge_cmp);
    }

    // --- Phase 2: parallel merge ---
    for (int width = 1; width < nthreads; width *= 2) {
        int limit = nthreads - width;

        #pragma omp parallel for schedule(static)
        for (int i = 0; i < limit; i += 2 * width) {
            inplace_merge(
                edges.begin() + starts[i],
                edges.begin() + starts[i + width],
                edges.begin() + starts[min(i + 2 * width, nthreads)],
                edge_cmp
            );
        }
    }
}
