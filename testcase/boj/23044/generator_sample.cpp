#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makeTree(int n, int mode) {
    vector<pair<int, int>> edges;

    if (mode == 0) {
        for (int i = 0; i + 1 < n; ++i) {
            edges.push_back({i, i + 1});
        }
    } else if (mode == 1) {
        int center = rnd.next(n);
        for (int i = 0; i < n; ++i) {
            if (i != center) {
                edges.push_back({center, i});
            }
        }
    } else if (mode == 2) {
        int spine = rnd.next(2, n);
        for (int i = 0; i + 1 < spine; ++i) {
            edges.push_back({i, i + 1});
        }
        for (int i = spine; i < n; ++i) {
            edges.push_back({rnd.next(spine), i});
        }
    } else if (mode == 3) {
        for (int i = 1; i < n; ++i) {
            edges.push_back({(i - 1) / 2, i});
        }
    } else if (mode == 4) {
        for (int i = 1; i < n; ++i) {
            edges.push_back({rnd.next(i), i});
        }
    } else {
        int a = 0;
        int b = 1;
        edges.push_back({a, b});
        for (int i = 2; i < n; ++i) {
            edges.push_back({rnd.next(2) == 0 ? a : b, i});
        }
    }

    return edges;
}

vector<int> makeColors(int n, const vector<pair<int, int>>& edges, int mode) {
    vector<int> c(n, 0);

    if (mode == 0) {
        int l = rnd.next(n);
        int r = rnd.next(l, n - 1);
        for (int i = l; i <= r; ++i) {
            c[i] = 1;
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            c[i] = i % 2;
        }
        if (rnd.next(2)) {
            for (int& value : c) {
                value ^= 1;
            }
        }
    } else if (mode == 2) {
        vector<int> degree(n, 0);
        for (auto [u, v] : edges) {
            ++degree[u];
            ++degree[v];
        }
        for (int i = 0; i < n; ++i) {
            c[i] = degree[i] <= 1;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            c[i] = rnd.next(100) < 35;
        }
    } else {
        for (int i = 0; i < n; ++i) {
            c[i] = rnd.next(100) < 65;
        }
    }

    int removed = accumulate(c.begin(), c.end(), 0);
    if (removed == 0) {
        c[rnd.next(n)] = 1;
    } else if (removed == n) {
        c[rnd.next(n)] = 0;
    }

    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    int treeMode = rnd.next(6);
    vector<pair<int, int>> edges = makeTree(n, treeMode);
    vector<int> colors = makeColors(n, edges, rnd.next(5));

    vector<int> label(n);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin(), label.end());

    vector<int> outputColors(n + 1);
    for (int oldVertex = 0; oldVertex < n; ++oldVertex) {
        outputColors[label[oldVertex]] = colors[oldVertex];
    }

    shuffle(edges.begin(), edges.end());
    for (auto& [u, v] : edges) {
        u = label[u];
        v = label[v];
        if (rnd.next(2)) {
            swap(u, v);
        }
    }

    println(n);
    vector<int> line;
    for (int vertex = 1; vertex <= n; ++vertex) {
        line.push_back(outputColors[vertex]);
    }
    println(line);
    for (auto [u, v] : edges) {
        println(u, v);
    }

    return 0;
}
