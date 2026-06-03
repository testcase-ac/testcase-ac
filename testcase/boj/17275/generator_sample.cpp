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

static vector<pair<int, int>> allPairs(int n) {
    vector<pair<int, int>> pairs;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            pairs.push_back({i, j});
        }
    }
    return pairs;
}

static vector<pair<int, int>> makeCase(int n, int mode) {
    set<pair<int, int>> chosen;
    vector<pair<int, int>> pairs = allPairs(n);

    if (mode == 0) {
        int m = rnd.next(1, min<int>(4, pairs.size()));
        shuffle(pairs.begin(), pairs.end());
        for (int i = 0; i < m; ++i) {
            chosen.insert(pairs[i]);
        }
    } else if (mode == 1) {
        int m = rnd.next(max<int>(1, (int)pairs.size() - min<int>(5, pairs.size() - 1)),
                         (int)pairs.size());
        shuffle(pairs.begin(), pairs.end());
        for (int i = 0; i < m; ++i) {
            chosen.insert(pairs[i]);
        }
    } else if (mode == 2) {
        int cliqueSize = rnd.next(3, n);
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) {
            vertices[i] = i + 1;
        }
        shuffle(vertices.begin(), vertices.end());

        for (int i = 0; i < cliqueSize; ++i) {
            for (int j = i + 1; j < cliqueSize; ++j) {
                addEdge(chosen, vertices[i], vertices[j]);
            }
        }

        shuffle(pairs.begin(), pairs.end());
        int extra = rnd.next(0, min<int>(3, pairs.size()));
        for (const auto& edge : pairs) {
            if ((int)chosen.size() >= cliqueSize * (cliqueSize - 1) / 2 + extra) {
                break;
            }
            chosen.insert(edge);
        }
    } else if (mode == 3) {
        int split = rnd.next(1, n - 1);
        for (int i = 1; i <= split; ++i) {
            for (int j = split + 1; j <= n; ++j) {
                if (rnd.next(0, 99) < 65) {
                    addEdge(chosen, i, j);
                }
            }
        }
    } else {
        int percent = rnd.next(10, 90);
        for (const auto& edge : pairs) {
            if (rnd.next(0, 99) < percent) {
                chosen.insert(edge);
            }
        }
    }

    if (chosen.empty()) {
        chosen.insert(rnd.any(pairs));
    }

    vector<pair<int, int>> edges(chosen.begin(), chosen.end());
    shuffle(edges.begin(), edges.end());
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(3, 14);
        int mode = rnd.next(0, 4);
        vector<pair<int, int>> edges = makeCase(n, mode);

        println(n, (int)edges.size());
        for (const auto& edge : edges) {
            println(edge.first, edge.second);
        }
    }

    return 0;
}
