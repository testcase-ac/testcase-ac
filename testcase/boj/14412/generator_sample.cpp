#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

static vector<pair<int, int>> allEdges(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            edges.emplace_back(i, j);
        }
    }
    return edges;
}

static void addEdge(vector<pair<int, int>>& edges, int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    edges.emplace_back(a, b);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    int mode = rnd.next(5);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        vector<pair<int, int>> candidates = allEdges(n);
        shuffle(candidates.begin(), candidates.end());
        int m = rnd.next(0, min<int>(n + 2, (int)candidates.size() - 1));
        edges.assign(candidates.begin(), candidates.begin() + m);
    } else if (mode == 1) {
        edges = allEdges(n);
        shuffle(edges.begin(), edges.end());
        int missing = rnd.next(1, min<int>(n + 2, (int)edges.size()));
        edges.resize(edges.size() - missing);
    } else if (mode == 2) {
        vector<int> part(n + 1);
        for (int i = 1; i <= n; ++i) {
            part[i] = rnd.next(2);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (part[i] != part[j]) {
                    addEdge(edges, i, j);
                }
            }
        }
    } else if (mode == 3) {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1);
        }
        int extra = rnd.next(0, n);
        vector<pair<int, int>> candidates = allEdges(n);
        shuffle(candidates.begin(), candidates.end());
        for (auto edge : candidates) {
            if ((int)edges.size() >= n - 1 + extra) {
                break;
            }
            if (find(edges.begin(), edges.end(), edge) == edges.end()) {
                edges.push_back(edge);
            }
        }
    } else {
        int threshold = rnd.next(15, 85);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next(100) < threshold) {
                    addEdge(edges, i, j);
                }
            }
        }
    }

    vector<pair<int, int>> complete = allEdges(n);
    if ((int)edges.size() == (int)complete.size()) {
        shuffle(edges.begin(), edges.end());
        edges.pop_back();
    }

    shuffle(edges.begin(), edges.end());
    println(n);
    println((int)edges.size());
    for (auto edge : edges) {
        if (rnd.next(2)) {
            swap(edge.first, edge.second);
        }
        println(edge.first, edge.second);
    }

    return 0;
}
