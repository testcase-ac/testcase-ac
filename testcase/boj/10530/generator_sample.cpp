#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <tuple>
#include <vector>
using namespace std;

using Edge = tuple<int, int, int>;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int p = rnd.next(2, 14);
    vector<Edge> edges;

    auto addEdge = [&](int a, int b, int w) {
        edges.emplace_back(a, b, w);
    };

    if (mode == 0) {
        for (int i = 0; i + 1 < p; ++i) {
            addEdge(i, i + 1, rnd.next(1, 40));
        }
    } else if (mode == 1) {
        for (int i = 1; i + 1 < p; ++i) {
            int a = rnd.next(1, 25);
            int b = rnd.next(1, 25);
            addEdge(0, i, a);
            addEdge(i, p - 1, b);
            if (rnd.next(0, 1)) {
                addEdge(0, i, a);
            }
        }
        addEdge(0, p - 1, rnd.next(2, 50));
    } else if (mode == 2) {
        for (int i = 0; i + 1 < p; ++i) {
            int w = rnd.next(1, 20);
            addEdge(i, i + 1, w);
            addEdge(i, i + 1, w);
        }
        for (int i = 0; i < p; ++i) {
            if (rnd.next(0, 2) == 0) {
                addEdge(i, i, rnd.next(1, 1000));
            }
        }
    } else {
        vector<int> order(p);
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin() + 1, order.end() - 1);
        for (int i = 0; i + 1 < p; ++i) {
            addEdge(order[i], order[i + 1], rnd.next(1, 35));
        }
    }

    int extra = rnd.next(0, min(18, p * 3));
    for (int i = 0; i < extra; ++i) {
        int a = rnd.next(0, p - 1);
        int b = rnd.next(0, p - 1);
        int w = rnd.next(1, 120);
        addEdge(a, b, w);
    }

    shuffle(edges.begin(), edges.end());

    println(p, static_cast<int>(edges.size()));
    for (auto [a, b, w] : edges) {
        println(a, b, w);
    }

    return 0;
}
