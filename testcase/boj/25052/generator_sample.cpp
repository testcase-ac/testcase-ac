#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

vector<int> makeBeauty(int n, int mode) {
    vector<int> p(n + 1);
    if (mode == 0) {
        fill(p.begin() + 1, p.end(), rnd.next(1, 100));
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            p[i] = i % 2 == 0 ? 1 : 100;
        }
    } else if (mode == 2) {
        int lo = rnd.next(1, 70);
        int hi = rnd.next(lo, 100);
        for (int i = 1; i <= n; ++i) {
            p[i] = rnd.next(lo, hi);
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            p[i] = rnd.next(1, 100);
        }
    }
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = mode == 0 ? rnd.next(2, 18) : rnd.next(3, 30);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({v - 1, v});
        }
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({1, v});
        }
    } else if (mode == 2) {
        int spine = rnd.next(2, max(2, n / 2));
        for (int v = 2; v <= spine; ++v) {
            edges.push_back({v - 1, v});
        }
        for (int v = spine + 1; v <= n; ++v) {
            edges.push_back({rnd.next(1, spine), v});
        }
    } else if (mode == 3) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({max(1, v / 2), v});
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            int bias = rnd.next(0, 2);
            int parent = bias == 0 ? rnd.next(1, v - 1) : rnd.wnext(v - 1, -2) + 1;
            edges.push_back({parent, v});
        }
    }

    vector<int> labels(n);
    iota(labels.begin(), labels.end(), 1);
    if (rnd.next(0, 1)) {
        shuffle(labels.begin() + 1, labels.end());
    }
    for (auto& edge : edges) {
        edge.first = labels[edge.first - 1];
        edge.second = labels[edge.second - 1];
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    vector<int> p = makeBeauty(n, rnd.next(0, 3));

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << p[i];
    }
    cout << '\n';
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
