#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

void relabelEdges(vector<pair<int, int>>& edges, const vector<int>& label) {
    for (auto& edge : edges) {
        edge.first = label[edge.first];
        edge.second = label[edge.second];
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 14);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(1, 10);
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        for (int i = 1; i < n; ++i) {
            edges.emplace_back(i, i + 1);
        }
    } else if (mode == 2) {
        n = rnd.next(3, 14);
        for (int i = 2; i <= n; ++i) {
            if (rnd.next(0, 1) == 0) {
                edges.emplace_back(1, i);
            } else {
                edges.emplace_back(i - 1, n);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(4, 14);
        int firstEnd = rnd.next(1, n - 2);
        int secondEnd = rnd.next(firstEnd + 1, n - 1);
        for (int u = 1; u <= firstEnd; ++u) {
            for (int v = firstEnd + 1; v <= secondEnd; ++v) {
                if (rnd.next(0, 99) < 65) {
                    edges.emplace_back(u, v);
                }
            }
        }
        for (int u = firstEnd + 1; u <= secondEnd; ++u) {
            for (int v = secondEnd + 1; v <= n; ++v) {
                if (rnd.next(0, 99) < 65) {
                    edges.emplace_back(u, v);
                }
            }
        }
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                candidates.emplace_back(u, v);
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int m = rnd.next(1, min<int>(candidates.size(), 22));
        edges.assign(candidates.begin(), candidates.begin() + m);
    } else {
        n = rnd.next(2, 9);
        int u = rnd.next(1, n - 1);
        int v = rnd.next(u + 1, n);
        int copies = rnd.next(2, 5);
        for (int i = 0; i < copies; ++i) {
            edges.emplace_back(u, v);
        }
        for (int i = 1; i < n; ++i) {
            if (rnd.next(0, 99) < 35) {
                edges.emplace_back(i, i + 1);
            }
        }
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());
    relabelEdges(edges, label);
    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
