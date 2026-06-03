#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int edgeCost(int mode, int index) {
    if (mode == 0) {
        return rnd.next(1, 9);
    }
    if (mode == 1) {
        return rnd.next(90, 99);
    }
    if (mode == 2) {
        return 1 + (index % 7);
    }
    if (mode == 3) {
        return rnd.next(1, 3) * 10 + rnd.next(0, 9);
    }
    return rnd.next(1, 99);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(1, 6);
    for (int tc = 0; tc < datasets; ++tc) {
        int mode = rnd.next(0, 4);
        int n = rnd.next(2, mode == 1 ? 16 : 12);

        vector<vector<pair<int, int>>> graph(n);
        vector<int> degree(n, 0);
        set<pair<int, int>> used;

        auto addEdge = [&](int a, int b, int cost) {
            if (a > b) {
                swap(a, b);
            }
            if (used.insert({a, b}).second) {
                graph[a].push_back({b, cost});
                ++degree[a];
                ++degree[b];
            }
        };

        for (int v = 1; v < n; ++v) {
            int parent = 0;
            if (mode == 0) {
                parent = v - 1;
            } else if (mode == 1) {
                parent = rnd.next(max(0, v - 4), v - 1);
            } else if (mode == 2) {
                parent = rnd.next(0, v - 1);
            } else if (mode == 3) {
                parent = rnd.next() < 0.75 ? 0 : rnd.next(0, v - 1);
            } else {
                parent = max(0, v - rnd.next(1, min(v, 3)));
            }
            addEdge(parent, v, edgeCost(mode, v));
        }

        vector<pair<int, int>> candidates;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (!used.count({i, j})) {
                    candidates.push_back({i, j});
                }
            }
        }
        shuffle(candidates.begin(), candidates.end());

        int maxEdges = min(75, n * (n - 1) / 2);
        int targetEdges = n - 1;
        if (mode == 1) {
            targetEdges = rnd.next(n - 1, maxEdges);
        } else if (mode == 3) {
            targetEdges = rnd.next(n - 1, min(maxEdges, n + 8));
        } else {
            targetEdges = rnd.next(n - 1, min(maxEdges, 2 * n));
        }

        int costIndex = n;
        for (auto [a, b] : candidates) {
            if ((int)used.size() >= targetEdges) {
                break;
            }
            if (degree[a] >= 15 || degree[b] >= 15) {
                continue;
            }
            addEdge(a, b, edgeCost(mode, costIndex++));
        }

        println(n);
        for (int i = 0; i < n - 1; ++i) {
            sort(graph[i].begin(), graph[i].end());
            printf("%c %d", char('A' + i), (int)graph[i].size());
            for (auto [to, cost] : graph[i]) {
                printf(" %c %d", char('A' + to), cost);
            }
            printf("\n");
        }
    }
    println(0);

    return 0;
}
