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

static void addRandomExtraEdges(int n, int targetM, set<pair<int, int>>& edges) {
    if ((int)edges.size() >= targetM) {
        return;
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!edges.count({a, b})) {
                candidates.push_back({a, b});
            }
        }
    }

    shuffle(candidates.begin(), candidates.end());
    for (const auto& edge : candidates) {
        if ((int)edges.size() >= targetM) {
            break;
        }
        edges.insert(edge);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.next(1, 4);
    println(k);

    for (int tc = 0; tc < k; ++tc) {
        int mode = rnd.next(0, 4);
        int n = rnd.next(2, mode == 4 ? 18 : 12);

        set<pair<int, int>> edges;
        if (mode == 0) {
            for (int v = 2; v <= n; ++v) {
                addEdge(edges, 1, v);
            }
        } else if (mode == 1) {
            for (int v = 1; v < n; ++v) {
                addEdge(edges, v, v + 1);
            }
        } else if (mode == 2) {
            for (int v = 1; v <= n; ++v) {
                addEdge(edges, v, v % n + 1);
            }
            int maxEdges = n * (n - 1) / 2;
            int targetM = rnd.next((int)edges.size(), min(3 * n, maxEdges));
            addRandomExtraEdges(n, targetM, edges);
        } else if (mode == 3) {
            int hubCount = rnd.next(2, min(n, 4));
            for (int v = 2; v <= n; ++v) {
                addEdge(edges, rnd.next(1, min(v - 1, hubCount)), v);
            }
            int maxEdges = n * (n - 1) / 2;
            int targetM = rnd.next((int)edges.size(), min(n + 6, maxEdges));
            addRandomExtraEdges(n, targetM, edges);
        } else {
            for (int v = 2; v <= n; ++v) {
                addEdge(edges, rnd.next(1, v - 1), v);
            }
            int maxEdges = n * (n - 1) / 2;
            int targetM = rnd.next((int)edges.size(), min(60, maxEdges));
            addRandomExtraEdges(n, targetM, edges);
        }

        vector<int> weights;
        int weightMode = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            if (weightMode == 0) {
                weights.push_back(rnd.next(0, 12));
            } else if (weightMode == 1) {
                weights.push_back(rnd.next(0, 1) ? rnd.next(0, 25) : 0);
            } else if (weightMode == 2) {
                weights.push_back(rnd.next(0, 1000));
            } else {
                weights.push_back(rnd.next(0, 1) ? 1000000 : rnd.next(0, 20));
            }
        }

        println(n, (int)edges.size());
        println(weights);

        vector<pair<int, int>> orderedEdges(edges.begin(), edges.end());
        shuffle(orderedEdges.begin(), orderedEdges.end());
        for (const auto& edge : orderedEdges) {
            if (rnd.next(0, 1)) {
                println(edge.first, edge.second);
            } else {
                println(edge.second, edge.first);
            }
        }

        println(rnd.next(1, n));
    }

    return 0;
}
