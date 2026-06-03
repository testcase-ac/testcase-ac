#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 14);
    if (mode == 2) n = rnd.next(3, 9);
    if (mode == 5) n = rnd.next(2, 12);

    vector<pair<int, int>> edges;

    if (mode == 0) {
        int m = rnd.next(0, min(5, n * 2));
        for (int i = 0; i < m; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n - 1);
            if (b >= a) ++b;
            edges.emplace_back(a, b);
        }
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next(0, 99) < 30) edges.emplace_back(i, j);
            }
        }
    } else if (mode == 2) {
        int k = rnd.next(3, min(n, 7));
        for (int i = 1; i <= k; ++i) {
            for (int j = i + 1; j <= k; ++j) edges.emplace_back(i, j);
        }
        for (int i = k + 1; i <= n; ++i) {
            int links = rnd.next(0, min(k, 3));
            vector<int> targets;
            for (int j = 1; j <= k; ++j) targets.push_back(j);
            shuffle(targets.begin(), targets.end());
            for (int j = 0; j < links; ++j) edges.emplace_back(i, targets[j]);
        }
    } else if (mode == 3) {
        for (int i = 2; i <= n; ++i) edges.emplace_back(i - 1, i);
        for (int i = 3; i <= n; ++i) {
            if (rnd.next(0, 1)) edges.emplace_back(i - 2, i);
        }
    } else if (mode == 4) {
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                if ((a % 2) != (b % 2) && rnd.next(0, 99) < 55) {
                    edges.emplace_back(a, b);
                }
            }
        }
    } else {
        int base = rnd.next(1, n - 1);
        int other = rnd.next(1, n - 1);
        if (other >= base) ++other;
        int m = rnd.next(1, min(12, n + 4));
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 99) < 70) {
                edges.emplace_back(base, other);
            } else {
                int a = rnd.next(1, n);
                int b = rnd.next(1, n - 1);
                if (b >= a) ++b;
                edges.emplace_back(a, b);
            }
        }
    }

    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(0, 1)) swap(edge.first, edge.second);
    }

    if (static_cast<int>(edges.size()) > 100000) edges.resize(100000);

    println(n, static_cast<int>(edges.size()));
    for (const auto& edge : edges) println(edge.first, edge.second);

    return 0;
}
