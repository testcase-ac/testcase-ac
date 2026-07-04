#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(set<pair<int, int>>& used, int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    used.insert({a, b});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    set<pair<int, int>> used;

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(used, i, i + 1);
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                addEdge(used, center, v);
            }
        }
    } else if (mode == 2) {
        for (int i = 1; i < n; ++i) {
            addEdge(used, i, i + 1);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 2; j <= n; ++j) {
                if (rnd.next(0, 99) < 35) {
                    addEdge(used, i, j);
                }
            }
        }
    } else if (mode == 3) {
        int split = rnd.next(1, n - 1);
        for (int i = 1; i < split; ++i) {
            addEdge(used, i, i + 1);
        }
        for (int i = split + 1; i < n; ++i) {
            addEdge(used, i, i + 1);
        }
        if (used.empty()) {
            addEdge(used, 1, 2);
        }
    } else if (mode == 4) {
        int groupSize = rnd.next(2, n);
        for (int i = 1; i <= groupSize; ++i) {
            for (int j = i + 1; j <= groupSize; ++j) {
                if (rnd.next(0, 99) < 65) {
                    addEdge(used, i, j);
                }
            }
        }
        if (used.empty()) {
            addEdge(used, 1, 2);
        }
    } else {
        vector<pair<int, int>> candidates;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                candidates.push_back({i, j});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int m = rnd.next(1, min<int>(100000, candidates.size()));
        for (int i = 0; i < m; ++i) {
            addEdge(used, candidates[i].first, candidates[i].second);
        }
    }

    vector<pair<int, int>> edges(used.begin(), used.end());
    shuffle(edges.begin(), edges.end());

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());

    println(n, static_cast<int>(edges.size()));
    for (auto edge : edges) {
        int a = label[edge.first];
        int b = label[edge.second];
        if (rnd.next(0, 1)) {
            swap(a, b);
        }
        println(a, b);
    }

    return 0;
}
