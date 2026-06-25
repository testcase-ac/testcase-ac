#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

void addTree(vector<pair<int, int>>& edges, const vector<int>& nodes) {
    for (int i = 1; i < (int)nodes.size(); ++i) {
        int parent = rnd.next(0, i - 1);
        edges.push_back({nodes[i], nodes[parent]});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int active = rnd.next(2, 10);
    vector<int> nodes(active);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());

    vector<pair<int, int>> edges;

    if (mode == 0) {
        addTree(edges, nodes);
    } else if (mode == 1) {
        addTree(edges, nodes);
        edges.push_back({nodes[0], nodes[active - 1]});
    } else if (mode == 2) {
        int components = rnd.next(2, min(4, active));
        int cursor = 0;
        for (int c = 0; c < components; ++c) {
            int remainingNodes = active - cursor;
            int remainingComponents = components - c;
            int sz = (c + 1 == components) ? remainingNodes : rnd.next(1, remainingNodes - remainingComponents + 1);
            vector<int> part(nodes.begin() + cursor, nodes.begin() + cursor + sz);
            addTree(edges, part);
            if (sz >= 3 && rnd.next(0, 1)) edges.push_back({part[0], part[sz - 1]});
            cursor += sz;
        }
    } else if (mode == 3) {
        int pairs = rnd.next(1, min(4, active / 2));
        for (int i = 0; i < pairs; ++i) {
            edges.push_back({nodes[2 * i], nodes[2 * i + 1]});
            edges.push_back({nodes[2 * i], nodes[2 * i + 1]});
        }
    } else if (mode == 4) {
        int sz = rnd.next(3, min(6, active));
        vector<int> part(nodes.begin(), nodes.begin() + sz);
        addTree(edges, part);
        edges.push_back({part[0], part[sz - 1]});
        edges.push_back({part[1], part[sz - 1]});
    } else {
        int m = rnd.next(1, active - 1);
        for (int i = 0; i < m; ++i) {
            int u = rnd.next(0, active - 1);
            int v = rnd.next(0, active - 2);
            if (v >= u) ++v;
            edges.push_back({nodes[u], nodes[v]});
        }
    }
    if (edges.empty()) edges.push_back({nodes[0], nodes[1]});

    shuffle(edges.begin(), edges.end());
    int n = max(active, (int)edges.size() + 1);
    n = min(n, 14);
    if ((int)edges.size() >= n) n = edges.size() + 1;

    vector<int> labels(n);
    iota(labels.begin(), labels.end(), 1);
    shuffle(labels.begin(), labels.end());
    for (auto& edge : edges) {
        edge.first = labels[edge.first - 1];
        edge.second = labels[edge.second - 1];
        if (rnd.next(0, 1)) swap(edge.first, edge.second);
    }

    println(n, (int)edges.size());
    for (auto [u, v] : edges) println(u, v);

    return 0;
}
