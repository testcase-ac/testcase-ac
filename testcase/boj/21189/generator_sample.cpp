#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(int a, int b, set<pair<int, int>>& seen, vector<pair<int, int>>& edges) {
    if (a > b) {
        swap(a, b);
    }
    if (a == b || !seen.insert({a, b}).second) {
        return;
    }
    edges.push_back({a, b});
}

void addRandomExtraEdges(int n, int targetM, set<pair<int, int>>& seen, vector<pair<int, int>>& edges) {
    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!seen.count({a, b})) {
                candidates.push_back({a, b});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (auto edge : candidates) {
        if ((int)edges.size() >= targetM) {
            break;
        }
        addEdge(edge.first, edge.second, seen, edges);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 16);
    set<pair<int, int>> seen;
    vector<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(2, 18);
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1, seen, edges);
        }
        int extras = rnd.next(0, min(12, n * (n - 1) / 2 - (n - 1)));
        addRandomExtraEdges(n, (int)edges.size() + extras, seen, edges);
    } else if (mode == 1) {
        n = rnd.next(4, 18);
        for (int i = 2; i <= n; ++i) {
            int parent = rnd.next(1, i - 1);
            addEdge(parent, i, seen, edges);
        }
        int extras = rnd.next(0, min(14, n * (n - 1) / 2 - (n - 1)));
        addRandomExtraEdges(n, (int)edges.size() + extras, seen, edges);
    } else if (mode == 2) {
        int layers = rnd.next(2, 5);
        vector<vector<int>> layer(layers);
        n = 0;
        layer[0].push_back(++n);
        for (int i = 1; i + 1 < layers; ++i) {
            int width = rnd.next(1, 4);
            while (width--) {
                layer[i].push_back(++n);
            }
        }
        layer.back().push_back(++n);

        for (int i = 0; i + 1 < layers; ++i) {
            for (int a : layer[i]) {
                for (int b : layer[i + 1]) {
                    if (rnd.next(0, 99) < 65) {
                        addEdge(a, b, seen, edges);
                    }
                }
            }
            if (none_of(layer[i].begin(), layer[i].end(), [&](int a) {
                    return any_of(layer[i + 1].begin(), layer[i + 1].end(), [&](int b) {
                        return seen.count(minmax(a, b));
                    });
                })) {
                addEdge(rnd.any(layer[i]), rnd.any(layer[i + 1]), seen, edges);
            }
        }
        for (int i = 1; i < layers; ++i) {
            for (int node : layer[i]) {
                bool hasPrevious = any_of(layer[i - 1].begin(), layer[i - 1].end(), [&](int prev) {
                    return seen.count(minmax(prev, node));
                });
                if (!hasPrevious) {
                    addEdge(rnd.any(layer[i - 1]), node, seen, edges);
                }
            }
        }
        for (int i = 0; i + 1 < layers; ++i) {
            for (int node : layer[i]) {
                bool hasNext = any_of(layer[i + 1].begin(), layer[i + 1].end(), [&](int next) {
                    return seen.count(minmax(node, next));
                });
                if (!hasNext) {
                    addEdge(node, rnd.any(layer[i + 1]), seen, edges);
                }
            }
        }
        for (int i = 0; i + 2 < layers; ++i) {
            if (rnd.next(0, 99) < 25) {
                addEdge(rnd.any(layer[i]), rnd.any(layer[i + 2]), seen, edges);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(3, 14);
        for (int i = 2; i <= n; ++i) {
            addEdge(1, i, seen, edges);
        }
        int extras = rnd.next(0, min(10, (n - 1) * (n - 2) / 2));
        addRandomExtraEdges(n, (int)edges.size() + extras, seen, edges);
    } else {
        n = rnd.next(5, 16);
        int split = rnd.next(2, n - 2);
        for (int i = 1; i < split; ++i) {
            addEdge(i, i + 1, seen, edges);
        }
        for (int i = split; i <= n; ++i) {
            addEdge(split, i, seen, edges);
        }
        addEdge(split - 1, split, seen, edges);
        int extras = rnd.next(0, min(12, n * (n - 1) / 2 - (int)edges.size()));
        addRandomExtraEdges(n, (int)edges.size() + extras, seen, edges);
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (auto [a, b] : edges) {
        if (rnd.next(0, 1)) {
            swap(a, b);
        }
        println(a, b);
    }

    return 0;
}
