#pragma once

#include <vector>
#include <map>
#include <string>

using namespace std;

struct Edge {
    string u;
    string v;
    int weight;
};

using Graph = map<string, vector<pair<string, int>>>;
