#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 14);
    vector<tuple<int, int, int>> edges;

    auto addEdge = [&](int a, int b, int lo, int hi) {
        edges.emplace_back(a, b, rnd.next(lo, hi));
    };

    if (mode == 0) {
        for (int i = 2; i <= n; ++i) {
            addEdge(i - 1, i, 1, 20);
        }
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            addEdge(1, i, 1, 30);
        }
    } else {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i + 1;
        }
        shuffle(order.begin(), order.end());
        for (int i = 1; i < n; ++i) {
            int parent = order[rnd.next(0, i - 1)];
            addEdge(parent, order[i], 1, 25);
        }
    }

    if (mode == 2 && n >= 3) {
        for (int i = 1; i <= n; ++i) {
            addEdge(i, i % n + 1, 1, 15);
        }
    }

    int targetM;
    if (mode == 3) {
        targetM = rnd.next((int)edges.size(), min(45, max((int)edges.size(), n * (n - 1) / 2 + n)));
    } else if (mode == 4) {
        targetM = rnd.next((int)edges.size(), min(35, max((int)edges.size(), n + 12)));
    } else {
        targetM = rnd.next((int)edges.size(), min(30, max((int)edges.size(), n + 8)));
    }

    while ((int)edges.size() < targetM) {
        int choice = rnd.next(0, 4);
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        int lo = 1;
        int hi = 100;

        if (choice == 0) {
            b = a;
            lo = 1;
            hi = 40;
        } else if (choice == 1 && !edges.empty()) {
            auto [x, y, oldLen] = rnd.any(edges);
            a = x;
            b = y;
            lo = max(1, oldLen - 5);
            hi = min(100, oldLen + 20);
        } else if (choice == 2) {
            if (a == b) {
                b = b % n + 1;
            }
            hi = 12;
        } else if (choice == 3) {
            if (a == b) {
                b = b % n + 1;
            }
            lo = 70;
            hi = 100;
        }

        addEdge(a, b, lo, hi);
    }

    shuffle(edges.begin(), edges.end());
    println(n, (int)edges.size());
    for (auto [a, b, len] : edges) {
        println(a, b, len);
    }

    return 0;
}
