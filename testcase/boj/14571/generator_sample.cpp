#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(set<pair<int, int>>& edges, int u, int v) {
    if (u > v) swap(u, v);
    edges.insert({u, v});
}

void addTriangle(set<pair<int, int>>& edges, int a, int b, int c) {
    addEdge(edges, a, b);
    addEdge(edges, b, c);
    addEdge(edges, c, a);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 5;
    set<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(5, 10);
        int center = rnd.next(1, n);
        vector<int> other;
        for (int v = 1; v <= n; ++v) {
            if (v != center) other.push_back(v);
        }
        shuffle(other.begin(), other.end());

        addTriangle(edges, center, other[0], other[1]);
        addTriangle(edges, center, other[2], other[3]);

        int extra = rnd.next(0, min(8, n * (n - 1) / 2 - 6));
        while (extra--) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u != v) addEdge(edges, u, v);
        }
    } else if (mode == 1) {
        n = rnd.next(6, 12);
        int center = rnd.next(1, n);
        vector<int> other;
        for (int v = 1; v <= n; ++v) {
            if (v != center) other.push_back(v);
        }
        shuffle(other.begin(), other.end());

        int pairs = rnd.next(2, min(5, (int)other.size() / 2));
        for (int i = 0; i < pairs; ++i) {
            addTriangle(edges, center, other[2 * i], other[2 * i + 1]);
        }
        for (int i = 0; i < (int)other.size(); ++i) {
            for (int j = i + 1; j < (int)other.size(); ++j) {
                if (rnd.next(0, 99) < 18) addEdge(edges, other[i], other[j]);
            }
        }
    } else if (mode == 2) {
        n = rnd.next(5, 9);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next(0, 99) < 65) addEdge(edges, u, v);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(8, 16);
        int triangles = rnd.next(2, 5);
        for (int i = 0; i < triangles; ++i) {
            vector<int> vertices;
            while ((int)vertices.size() < 3) {
                int v = rnd.next(1, n);
                if (find(vertices.begin(), vertices.end(), v) == vertices.end()) {
                    vertices.push_back(v);
                }
            }
            addTriangle(edges, vertices[0], vertices[1], vertices[2]);
        }
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next(0, 99) < 12) addEdge(edges, u, v);
            }
        }
    } else if (mode == 4) {
        n = rnd.next(10, 24);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next(0, 99) < rnd.next(8, 35)) addEdge(edges, u, v);
            }
        }
    } else {
        n = rnd.next(5, 14);
        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                candidates.push_back({u, v});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int m = rnd.next(6, (int)candidates.size());
        for (int i = 0; i < m; ++i) edges.insert(candidates[i]);
    }

    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            candidates.push_back({u, v});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (auto edge : candidates) {
        if ((int)edges.size() >= 6) break;
        edges.insert(edge);
    }

    vector<pair<int, int>> output(edges.begin(), edges.end());
    shuffle(output.begin(), output.end());
    for (auto& edge : output) {
        if (rnd.next(0, 1)) swap(edge.first, edge.second);
    }

    println(n, (int)output.size());
    for (auto edge : output) {
        println(edge.first, edge.second);
    }

    return 0;
}
