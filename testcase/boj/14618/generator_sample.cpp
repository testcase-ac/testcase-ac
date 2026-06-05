#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(3, 14);
    int k = rnd.next(1, n / 2);
    if (2 * k + 1 > n) {
        n = 2 * k + 1;
    }

    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());

    int j = nodes[0];
    vector<int> a(nodes.begin() + 1, nodes.begin() + 1 + k);
    vector<int> b(nodes.begin() + 1 + k, nodes.begin() + 1 + 2 * k);
    shuffle(a.begin(), a.end());
    shuffle(b.begin(), b.end());

    vector<pair<int, int>> simple;
    for (int x = 1; x <= n; ++x) {
        for (int y = x + 1; y <= n; ++y) {
            simple.push_back({x, y});
        }
    }
    shuffle(simple.begin(), simple.end());

    vector<pair<pair<int, int>, int>> edges;
    auto addEdge = [&](int x, int y, int z) {
        edges.push_back({{x, y}, z});
    };
    auto addRandomEdge = [&]() {
        if (rnd.next(0, 9) == 0) {
            int x = rnd.next(1, n);
            addEdge(x, x, rnd.next(1, 100));
        } else {
            auto e = rnd.any(simple);
            addEdge(e.first, e.second, rnd.next(1, 100));
        }
    };

    if (mode == 0) {
        int closeA = rnd.any(a);
        int closeB = rnd.any(b);
        addEdge(j, closeA, rnd.next(1, 20));
        addEdge(j, closeB, rnd.next(21, 60));
    } else if (mode == 1) {
        int closeA = rnd.any(a);
        int closeB = rnd.any(b);
        addEdge(j, closeA, rnd.next(30, 80));
        addEdge(j, closeB, rnd.next(1, 20));
    } else if (mode == 2) {
        int closeA = rnd.any(a);
        int closeB = rnd.any(b);
        int d = rnd.next(1, 60);
        addEdge(j, closeA, d);
        addEdge(j, closeB, d);
    } else if (mode == 3) {
        int closeA = rnd.any(a);
        addEdge(j, closeA, rnd.next(1, 40));
        for (int x : b) {
            addEdge(x, x, rnd.next(1, 100));
        }
    } else {
        for (int x : a) {
            addEdge(x, x, rnd.next(1, 100));
        }
        for (int x : b) {
            addEdge(x, x, rnd.next(1, 100));
        }
    }

    int targetM = rnd.next(3, min(40, 20000));
    while ((int)edges.size() < targetM) {
        addRandomEdge();
    }
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    println(j);
    println(k);
    println(a);
    println(b);
    for (auto edge : edges) {
        println(edge.first.first, edge.first.second, edge.second);
    }

    return 0;
}
