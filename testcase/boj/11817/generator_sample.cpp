#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {

struct Edge {
    int u;
    int v;
    int w;
};

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v) {
    if (u > v) {
        swap(u, v);
    }
    if (!used.insert({u, v}).second) {
        return;
    }
    edges.push_back({u, v, rnd.next(1, 1000)});
}

void makeConnectedBlock(vector<int> vertices, vector<Edge>& edges, set<pair<int, int>>& used) {
    shuffle(vertices.begin(), vertices.end());
    for (int i = 1; i < static_cast<int>(vertices.size()); ++i) {
        int parent = vertices[rnd.next(0, i - 1)];
        addEdge(edges, used, parent, vertices[i]);
    }
}

void addOptionalBlockEdges(const vector<int>& vertices, vector<Edge>& edges, set<pair<int, int>>& used,
                           int probabilityPercent) {
    vector<pair<int, int>> candidates;
    for (int i = 0; i < static_cast<int>(vertices.size()); ++i) {
        for (int j = i + 1; j < static_cast<int>(vertices.size()); ++j) {
            pair<int, int> edge = minmax(vertices[i], vertices[j]);
            if (!used.count(edge)) {
                candidates.push_back(edge);
            }
        }
    }

    shuffle(candidates.begin(), candidates.end());
    for (auto [u, v] : candidates) {
        if (rnd.next(1, 100) <= probabilityPercent) {
            addEdge(edges, used, u, v);
        }
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 14);
    int leftSize = rnd.next(1, n - 1);

    vector<int> labels(n);
    for (int i = 0; i < n; ++i) {
        labels[i] = i + 1;
    }
    shuffle(labels.begin(), labels.end());

    vector<int> left(labels.begin(), labels.begin() + leftSize);
    vector<int> right(labels.begin() + leftSize, labels.end());

    vector<Edge> edges;
    set<pair<int, int>> used;

    makeConnectedBlock(left, edges, used);
    makeConnectedBlock(right, edges, used);
    addEdge(edges, used, rnd.any(left), rnd.any(right));

    int density = rnd.next(0, 75);
    addOptionalBlockEdges(left, edges, used, density);
    addOptionalBlockEdges(right, edges, used, density);

    shuffle(edges.begin(), edges.end());
    println(n, static_cast<int>(edges.size()));
    for (auto edge : edges) {
        if (rnd.next(0, 1)) {
            swap(edge.u, edge.v);
        }
        println(edge.u, edge.v, edge.w);
    }

    println(rnd.next(1, n), rnd.next(1, n));
    return 0;
}
