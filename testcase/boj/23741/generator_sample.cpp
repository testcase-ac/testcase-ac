#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 14);
    int x = rnd.next(1, n);
    int y = rnd.next(1, 30);
    vector<pair<int, int>> edges;

    auto addEdge = [&](int a, int b) {
        if (a > b && rnd.next(2)) swap(a, b);
        edges.push_back({a, b});
    };

    if (mode == 0) {
        n = rnd.next(2, 14);
        x = rnd.next(1, n);
        y = rnd.next(1, 30);
        for (int i = 1; i < n; ++i) addEdge(i, i + 1);
        if (rnd.next(2) && n > 2) addEdge(n, 1);
    } else if (mode == 1) {
        n = rnd.next(3, 14);
        x = rnd.next(1, n / 2);
        y = rnd.next(1, 30);
        for (int i = 1; i < n / 2; ++i) addEdge(i, i + 1);
        for (int i = n / 2 + 1; i < n; ++i) addEdge(i, i + 1);
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        x = rnd.next(1, n);
        y = rnd.next(1, 30);
        int a = rnd.next(1, n);
        int b = rnd.next(1, n - 1);
        if (b >= a) ++b;
        int copies = rnd.next(1, 25);
        for (int i = 0; i < copies; ++i) addEdge(a, b);
        for (int i = 0; i < rnd.next(0, 8); ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n - 1);
            if (v >= u) ++v;
            addEdge(u, v);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 14);
        int center = rnd.next(1, n);
        x = rnd.next(1, n);
        y = rnd.next(1, 30);
        for (int i = 1; i <= n; ++i) {
            if (i != center && rnd.next(3) != 0) addEdge(center, i);
        }
        if (edges.empty()) addEdge(center, center == 1 ? 2 : 1);
    } else {
        n = rnd.next(2, 14);
        x = rnd.next(1, n);
        y = rnd.next(1, 30);
        double density = rnd.next(0.08, 0.45);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < density) addEdge(i, j);
            }
        }
        if (edges.empty()) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n - 1);
            if (b >= a) ++b;
            addEdge(a, b);
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()), x, y);
    for (auto [a, b] : edges) println(a, b);

    return 0;
}
