#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        for (int i = 1; i < n; ++i) {
            edges.push_back({i, i + 1});
        }
    } else if (mode == 2) {
        n = rnd.next(4, 14);
        int split = rnd.next(2, n - 1);
        for (int u = 1; u <= split; ++u) {
            for (int v = split + 1; v <= n; ++v) {
                if (rnd.next(0, 99) < rnd.next(35, 80)) {
                    edges.push_back({u, v});
                }
            }
        }
    } else if (mode == 3) {
        n = rnd.next(2, 16);
        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                candidates.push_back({u, v});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int m = rnd.next(0, min<int>(60, candidates.size()));
        edges.assign(candidates.begin(), candidates.begin() + m);
    } else if (mode == 4) {
        n = rnd.next(5, 13);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next(0, 99) < rnd.next(55, 90)) {
                    edges.push_back({u, v});
                }
            }
        }
    } else {
        n = rnd.next(6, 14);
        for (int v = 2; v <= n; ++v) {
            int parentCount = rnd.next(1, min(3, v - 1));
            vector<int> parents;
            for (int u = 1; u < v; ++u) {
                parents.push_back(u);
            }
            shuffle(parents.begin(), parents.end());
            for (int i = 0; i < parentCount; ++i) {
                edges.push_back({parents[i], v});
            }
        }
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());

    set<pair<int, int>> uniqueEdges;
    for (auto [u, v] : edges) {
        uniqueEdges.insert({label[u], label[v]});
    }

    vector<pair<int, int>> output(uniqueEdges.begin(), uniqueEdges.end());
    shuffle(output.begin(), output.end());

    println(n, (int)output.size());
    for (auto [u, v] : output) {
        println(u, v);
    }

    return 0;
}
