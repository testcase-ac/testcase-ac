#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static void addEdge(set<pair<int, int>>& edges, int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    edges.insert({a, b});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    set<pair<int, int>> edgeSet;

    if (mode == 0) {
        n = rnd.next(3, 12);
    } else if (mode == 1) {
        n = rnd.next(3, 16);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                addEdge(edgeSet, i, j);
            }
        }
    } else if (mode == 2) {
        n = rnd.next(4, 18);
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != center) {
                addEdge(edgeSet, center, i);
            }
        }

        int extra = rnd.next(0, min(12, n * (n - 1) / 2 - (n - 1)));
        while (extra > 0) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            if (a == b) {
                continue;
            }
            int before = static_cast<int>(edgeSet.size());
            addEdge(edgeSet, a, b);
            if (static_cast<int>(edgeSet.size()) > before) {
                --extra;
            }
        }
    } else if (mode == 3) {
        n = rnd.next(5, 18);
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) {
            vertices[i] = i + 1;
        }
        shuffle(vertices.begin(), vertices.end());

        int leftSize = rnd.next(1, n - 1);
        for (int i = 0; i < leftSize; ++i) {
            for (int j = leftSize; j < n; ++j) {
                if (rnd.next(0, 99) < rnd.next(45, 90)) {
                    addEdge(edgeSet, vertices[i], vertices[j]);
                }
            }
        }
    } else if (mode == 4) {
        n = rnd.next(6, 20);
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) {
            vertices[i] = i + 1;
        }
        shuffle(vertices.begin(), vertices.end());

        int cliqueSize = rnd.next(3, n);
        for (int i = 0; i < cliqueSize; ++i) {
            for (int j = i + 1; j < cliqueSize; ++j) {
                addEdge(edgeSet, vertices[i], vertices[j]);
            }
        }
        for (int i = cliqueSize; i < n; ++i) {
            int links = rnd.next(0, min(3, cliqueSize));
            for (int t = 0; t < links; ++t) {
                addEdge(edgeSet, vertices[i], vertices[rnd.next(0, cliqueSize - 1)]);
            }
        }
    } else {
        n = rnd.next(3, 22);
        int density = rnd.next(0, 100);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next(0, 99) < density) {
                    addEdge(edgeSet, i, j);
                }
            }
        }
    }

    vector<int> perm(n + 1);
    for (int i = 1; i <= n; ++i) {
        perm[i] = i;
    }
    shuffle(perm.begin() + 1, perm.end());

    vector<pair<int, int>> edges;
    for (auto [a, b] : edgeSet) {
        int u = perm[a];
        int v = perm[b];
        if (u > v) {
            swap(u, v);
        }
        edges.push_back({u, v});
    }

    sort(edges.begin(), edges.end());

    println(n);
    println(static_cast<int>(edges.size()));
    for (auto [u, v] : edges) {
        println(u, v);
    }

    return 0;
}
