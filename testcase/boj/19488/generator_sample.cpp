#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {

void addEdge(set<pair<int, int>>& edges, int a, int b) {
    if (a > b) swap(a, b);
    edges.insert({a, b});
}

void addClique(set<pair<int, int>>& edges, const vector<int>& vertices) {
    for (int i = 0; i < int(vertices.size()); ++i) {
        for (int j = i + 1; j < int(vertices.size()); ++j) {
            addEdge(edges, vertices[i], vertices[j]);
        }
    }
}

void printCase(int n, int d, set<pair<int, int>> edges) {
    vector<pair<int, int>> shuffledEdges(edges.begin(), edges.end());
    shuffle(shuffledEdges.begin(), shuffledEdges.end());
    for (auto& edge : shuffledEdges) {
        if (rnd.next(2) == 0) swap(edge.first, edge.second);
    }

    println(n, int(shuffledEdges.size()), d);
    for (const auto& edge : shuffledEdges) {
        println(edge.first, edge.second);
    }
}

vector<int> shuffledLabels(int n) {
    vector<int> label(n);
    for (int i = 0; i < n; ++i) label[i] = i + 1;
    shuffle(label.begin(), label.end());
    return label;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 14);
    vector<int> label = shuffledLabels(n);
    set<pair<int, int>> edges;
    int d = 1;

    if (mode == 0) {
        int cliqueSize = rnd.next(2, n);
        d = rnd.next(1, cliqueSize - 1);
        vector<int> clique(label.begin(), label.begin() + cliqueSize);
        addClique(edges, clique);

        for (int i = cliqueSize; i < n; ++i) {
            int degree = rnd.next(0, min<int>(d, clique.size()));
            vector<int> neighbors = clique;
            shuffle(neighbors.begin(), neighbors.end());
            for (int j = 0; j < degree; ++j) addEdge(edges, label[i], neighbors[j]);
        }
    } else if (mode == 1) {
        d = rnd.next(1, n - 1);
        for (int i = 1; i < n; ++i) {
            int parent = rnd.next(0, i - 1);
            addEdge(edges, label[i], label[parent]);
        }
    } else if (mode == 2) {
        int split = rnd.next(1, n - 1);
        vector<int> left(label.begin(), label.begin() + split);
        vector<int> right(label.begin() + split, label.end());
        if (left.size() >= 2) addClique(edges, left);
        if (right.size() >= 2) addClique(edges, right);
        d = rnd.next(1, max<int>(1, min(left.size(), right.size()) - 1));
    } else if (mode == 3) {
        int coreSize = rnd.next(2, n);
        vector<int> core(label.begin(), label.begin() + coreSize);
        addClique(edges, core);
        d = rnd.next(1, coreSize - 1);

        for (int i = coreSize; i < n; ++i) {
            int attachCount = rnd.next(1, min<int>(d, core.size()));
            vector<int> neighbors = core;
            shuffle(neighbors.begin(), neighbors.end());
            for (int j = 0; j < attachCount; ++j) addEdge(edges, label[i], neighbors[j]);
            if (i > coreSize && rnd.next(2) == 0) addEdge(edges, label[i], label[rnd.next(coreSize, i - 1)]);
        }
    } else {
        d = rnd.next(1, n - 1);
        double probability = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < probability) addEdge(edges, label[i], label[j]);
            }
        }
    }

    if (edges.empty()) addEdge(edges, label[0], label[1]);
    printCase(n, d, edges);
    return 0;
}
