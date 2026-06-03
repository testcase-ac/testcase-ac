#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    int d = rnd.next(1, 20);
    int e = rnd.next(1, 20);

    vector<int> h(n + 1, 1);
    for (int i = 2; i < n; ++i) {
        if (mode == 1) {
            h[i] = 1;
        } else if (mode == 2) {
            h[i] = rnd.next(1, 3);
        } else {
            h[i] = rnd.next(2, 30);
        }
    }

    vector<pair<int, int>> edges;
    auto addEdge = [&](int a, int b) {
        edges.push_back({a, b});
    };

    if (mode == 0 && n >= 3) {
        int peak = rnd.next(2, n - 1);
        h[peak] = rnd.next(10, 40);
        for (int i = 2; i < n; ++i) {
            if (i != peak) h[i] = rnd.next(2, max(2, h[peak] - 1));
        }
        addEdge(1, peak);
        addEdge(peak, n);
    } else if (mode == 1) {
        addEdge(1, n);
    } else if (mode == 2 && n >= 3) {
        for (int i = 1; i < n; ++i) addEdge(i, i + 1);
    } else if (mode == 3 && n >= 4) {
        int peak = rnd.next(3, n - 1);
        h[2] = rnd.next(2, 10);
        h[peak] = h[2] + rnd.next(1, 15);
        addEdge(1, 2);
        addEdge(2, peak);
        addEdge(peak, n);
    } else {
        int m0 = rnd.next(1, min(20, n * n));
        for (int i = 0; i < m0; ++i) addEdge(rnd.next(1, n), rnd.next(1, n));
    }

    int extra = rnd.next(0, min(18, n * n));
    for (int i = 0; i < extra; ++i) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        if (rnd.next(0, 4) == 0) b = a;
        addEdge(a, b);
    }

    shuffle(edges.begin(), edges.end());
    if (edges.empty()) addEdge(1, 1);

    println(n, static_cast<int>(edges.size()), d, e);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << h[i];
    }
    cout << '\n';
    for (auto [a, b] : edges) {
        int dist = rnd.next(1, 50);
        if (rnd.next(0, 9) == 0) dist = rnd.next(50000, 100000);
        println(a, b, dist);
    }

    return 0;
}
