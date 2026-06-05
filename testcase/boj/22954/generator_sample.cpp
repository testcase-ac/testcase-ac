#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {

void addEdge(set<pair<int, int>>& used, int u, int v) {
    if (u > v) swap(u, v);
    used.insert({u, v});
}

void addTree(set<pair<int, int>>& used, const vector<int>& vertices, int shape) {
    if (vertices.size() <= 1) return;

    if (shape == 0) {
        for (int i = 1; i < int(vertices.size()); ++i) {
            addEdge(used, vertices[i - 1], vertices[i]);
        }
        return;
    }

    if (shape == 1) {
        int center = vertices[0];
        for (int i = 1; i < int(vertices.size()); ++i) {
            addEdge(used, center, vertices[i]);
        }
        return;
    }

    for (int i = 1; i < int(vertices.size()); ++i) {
        int parent = vertices[rnd.next(i)];
        addEdge(used, parent, vertices[i]);
    }
}

void addRandomExtraEdges(set<pair<int, int>>& used, int n, int targetM) {
    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (!used.count({u, v})) candidates.push_back({u, v});
        }
    }

    shuffle(candidates.begin(), candidates.end());
    int addCount = min(targetM - int(used.size()), int(candidates.size()));
    for (int i = 0; i < addCount; ++i) {
        used.insert(candidates[i]);
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n = rnd.next(1, 14);
    set<pair<int, int>> edges;

    if (mode == 0) {
        // Empty graph, including the smallest impossible cases.
    } else if (mode == 1) {
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) vertices[i] = i + 1;
        shuffle(vertices.begin(), vertices.end());
        addTree(edges, vertices, rnd.next(3));
    } else if (mode == 2) {
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) vertices[i] = i + 1;
        shuffle(vertices.begin(), vertices.end());
        addTree(edges, vertices, rnd.next(2));
        addRandomExtraEdges(edges, n, rnd.next(int(edges.size()), min(n * (n - 1) / 2, int(edges.size()) + n)));
    } else if (mode == 3) {
        int firstSize = rnd.next(1, n);
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) vertices[i] = i + 1;
        shuffle(vertices.begin(), vertices.end());

        vector<int> first(vertices.begin(), vertices.begin() + firstSize);
        vector<int> second(vertices.begin() + firstSize, vertices.end());
        addTree(edges, first, rnd.next(3));
        addTree(edges, second, rnd.next(3));
    } else if (mode == 4) {
        int components = rnd.next(2, min(n, 5));
        vector<vector<int>> groups(components);
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) vertices[i] = i + 1;
        shuffle(vertices.begin(), vertices.end());
        for (int i = 0; i < n; ++i) groups[i % components].push_back(vertices[i]);
        for (auto& group : groups) addTree(edges, group, rnd.next(3));
    } else if (mode == 5) {
        addRandomExtraEdges(edges, n, rnd.next(0, n * (n - 1) / 2));
    } else if (mode == 6) {
        for (int i = 1; i < n; ++i) addEdge(edges, i, i + 1);
        if (n >= 3) addEdge(edges, 1, n);
        addRandomExtraEdges(edges, n, rnd.next(int(edges.size()), min(n * (n - 1) / 2, int(edges.size()) + 3)));
    } else {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center && rnd.next(2)) addEdge(edges, center, v);
        }
        addRandomExtraEdges(edges, n, rnd.next(int(edges.size()), min(n * (n - 1) / 2, int(edges.size()) + n / 2 + 1)));
    }

    vector<pair<int, int>> output(edges.begin(), edges.end());
    shuffle(output.begin(), output.end());
    println(n, int(output.size()));
    for (auto [u, v] : output) {
        if (rnd.next(2)) swap(u, v);
        println(u, v);
    }

    return 0;
}
