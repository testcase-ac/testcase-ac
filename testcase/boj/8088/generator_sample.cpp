#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(int u, int v, set<pair<int, int>>& edges) {
    if (u == v) {
        return;
    }
    if (u > v) {
        swap(u, v);
    }
    edges.insert({u, v});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(3, 24);
    set<pair<int, int>> edges;

    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            addEdge(i, i % n + 1, edges);
        }

        int extra = rnd.next(0, min(20, n * (n - 3) / 2));
        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (!edges.count({u, v})) {
                    candidates.push_back({u, v});
                }
            }
        }
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < extra; ++i) {
            edges.insert(candidates[i]);
        }
    } else if (mode == 1) {
        if (n % 2 == 1) {
            ++n;
        }

        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) {
            vertices[i] = i + 1;
        }
        shuffle(vertices.begin(), vertices.end());
        for (int i = 0; i < n; i += 2) {
            addEdge(vertices[i], vertices[i + 1], edges);
        }

        int extra = rnd.next(0, min(12, n));
        for (int i = 0; i < extra; ++i) {
            addEdge(rnd.next(1, n), rnd.next(1, n), edges);
        }
    } else if (mode == 2) {
        int leftSize = rnd.next(1, n - 1);
        vector<int> left, right;
        for (int i = 1; i <= n; ++i) {
            if (i <= leftSize) {
                left.push_back(i);
            } else {
                right.push_back(i);
            }
        }

        for (int u : left) {
            addEdge(u, rnd.any(right), edges);
        }
        for (int v : right) {
            addEdge(rnd.any(left), v, edges);
        }

        int extra = rnd.next(0, min(20, leftSize * (n - leftSize)));
        for (int i = 0; i < extra; ++i) {
            addEdge(rnd.any(left), rnd.any(right), edges);
        }
    } else {
        n = rnd.next(3, 16);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next(100) < 75) {
                    addEdge(u, v, edges);
                }
            }
        }

        for (int u = 1; u <= n; ++u) {
            bool hasEdge = false;
            for (const auto& edge : edges) {
                hasEdge = hasEdge || edge.first == u || edge.second == u;
            }
            if (!hasEdge) {
                int v = rnd.next(1, n - 1);
                if (v >= u) {
                    ++v;
                }
                addEdge(u, v, edges);
            }
        }
    }

    vector<int> degrees(n + 1, 0);
    for (const auto& edge : edges) {
        ++degrees[edge.first];
        ++degrees[edge.second];
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        println(degrees[i]);
    }

    return 0;
}
