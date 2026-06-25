#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

static vector<int> chooseSet(int n, int size) {
    vector<int> nodes;
    for (int i = 1; i <= n; ++i) {
        nodes.push_back(i);
    }
    shuffle(nodes.begin(), nodes.end());
    nodes.resize(size);
    return nodes;
}

static void addPath(vector<pair<int, int>>& edges, int from, int to) {
    for (int i = from; i < to; ++i) {
        edges.emplace_back(i, i + 1);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        addPath(edges, 1, n);
        if (n >= 3 && rnd.next(0, 1)) {
            edges.emplace_back(n, 1);
        }
    } else if (mode == 1) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n - 1);
        if (v >= u) {
            ++v;
        }
        int copies = rnd.next(1, 12);
        for (int i = 0; i < copies; ++i) {
            edges.emplace_back(u, v);
        }
        int extras = rnd.next(0, 6);
        for (int i = 0; i < extras; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n - 1);
            if (b >= a) {
                ++b;
            }
            edges.emplace_back(a, b);
        }
    } else if (mode == 2) {
        int split = rnd.next(1, n - 1);
        addPath(edges, 1, split);
        addPath(edges, split + 1, n);
        if (edges.empty()) {
            edges.emplace_back(1, n);
        }
    } else if (mode == 3) {
        double density = rnd.next(0.10, 0.45);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next() < density) {
                    edges.emplace_back(u, v);
                }
            }
        }
        if (edges.empty()) {
            edges.emplace_back(rnd.next(1, n - 1), rnd.next(2, n));
        }
    } else {
        n = rnd.next(2, 8);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next(0, 3) != 0) {
                    edges.emplace_back(u, v);
                    if (rnd.next(0, 5) == 0) {
                        edges.emplace_back(u, v);
                    }
                }
            }
        }
        if (edges.empty()) {
            edges.emplace_back(1, 2);
        }
    }

    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }

    int k;
    int kMode = rnd.next(0, 4);
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = rnd.next(2, 8);
    } else if (kMode == 2) {
        k = rnd.next(9, 50);
    } else if (kMode == 3) {
        k = rnd.next(100, 1000);
    } else {
        k = rnd.next(100000, 1000000);
    }

    int pSize = rnd.next(1, n);
    int qSize = rnd.next(1, n);
    vector<int> p = chooseSet(n, pSize);
    vector<int> q;
    if (rnd.next(0, 2) == 0) {
        q = chooseSet(n, qSize);
    } else {
        q = p;
        shuffle(q.begin(), q.end());
        while ((int)q.size() < qSize) {
            int x = rnd.next(1, n);
            if (find(q.begin(), q.end(), x) == q.end()) {
                q.push_back(x);
            }
        }
        if ((int)q.size() > qSize) {
            q.resize(qSize);
        }
    }

    println(n, (int)edges.size(), k);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }
    println(pSize, qSize);
    println(p);
    println(q);

    return 0;
}
