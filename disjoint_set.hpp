#pragma once

#include <vector>
#include <map>
#include <string>

using namespace std;

class DisjointSet {
private:
    map<string, string> parent;
    map<string, int> rank_;

public:
    DisjointSet(const vector<string>& vertices) {
        for (const string& v : vertices) {
            parent[v] = v;
            rank_[v] = 0;
        }
    }

    string find(const string& vertex) {
        if (parent[vertex] != vertex) {
            parent[vertex] = find(parent[vertex]);
        }
        return parent[vertex];
    }

    void union_(const string& root1, const string& root2) {
        if (rank_[root1] > rank_[root2]) {
            parent[root2] = root1;
        } else if (rank_[root1] < rank_[root2]) {
            parent[root1] = root2;
        } else {
            parent[root2] = root1;
            rank_[root1]++;
        }
    }
};
