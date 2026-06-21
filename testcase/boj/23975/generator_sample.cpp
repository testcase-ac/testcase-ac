#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = 1;
    int k = 1;
    vector<int> stock;
    vector<tuple<int, int, int>> edges;
    vector<int> visits;

    if (mode == 0) {
        n = 1;
        k = rnd.next(1, 6);
        stock = {rnd.next(0, 3)};
        edges.push_back({1, 1, rnd.next(1, 10)});
        visits.assign(k, 1);
    } else {
        n = rnd.next(3, 12);
        k = rnd.next(4, 14);
        stock.resize(n);
        for (int i = 0; i < n; ++i) {
            stock[i] = rnd.next(0, 4);
        }
        stock[rnd.next(0, n - 1)] = rnd.next(1, 4);

        if (mode == 1) {
            for (int i = 2; i <= n; ++i) {
                edges.push_back({i - 1, i, rnd.next(1, 9)});
            }
        } else if (mode == 2) {
            int split = rnd.next(2, n);
            for (int i = 2; i < split; ++i) {
                edges.push_back({i - 1, i, rnd.next(1, 8)});
            }
            for (int i = split + 1; i <= n; ++i) {
                edges.push_back({i - 1, i, rnd.next(1, 8)});
            }
            if (split <= n) {
                edges.push_back({split, split, rnd.next(1, 8)});
            }
        } else if (mode == 3) {
            for (int i = 2; i <= n; ++i) {
                int parent = rnd.next(1, i - 1);
                edges.push_back({parent, i, rnd.next(1, 10)});
            }
            int extra = rnd.next(1, n);
            for (int i = 0; i < extra; ++i) {
                int u = rnd.next(1, n);
                int v = rnd.next(1, n);
                int c = rnd.next(1, 10);
                edges.push_back({u, v, c});
                if (rnd.next(0, 2) == 0) {
                    edges.push_back({u, v, rnd.next(1, 10)});
                }
            }
        } else {
            n = max(n, 5);
            stock.assign(n, 0);
            for (int i = 0; i < n; ++i) {
                stock[i] = rnd.next(0, 3);
            }
            stock[1] = rnd.next(1, 3);
            stock[2] = rnd.next(1, 3);

            edges.push_back({1, 2, 1});
            edges.push_back({1, 3, 1});
            edges.push_back({2, 4, 2});
            edges.push_back({3, 4, 2});
            edges.push_back({2, 5, 3});
            edges.push_back({3, 5, 3});
            for (int i = 6; i <= n; ++i) {
                edges.push_back({rnd.next(1, i - 1), i, rnd.next(1, 8)});
            }
        }

        int targetM = (int)edges.size();
        if (targetM < 24) {
            targetM = rnd.next(targetM, 24);
        }
        while ((int)edges.size() < targetM) {
            edges.push_back({rnd.next(1, n), rnd.next(1, n), rnd.next(1, 12)});
        }

        for (int i = 0; i < k; ++i) {
            if (i < n && rnd.next(0, 1) == 0) {
                visits.push_back(i + 1);
            } else {
                visits.push_back(rnd.next(1, n));
            }
        }
        shuffle(visits.begin(), visits.end());
    }

    println(n, (int)edges.size(), k);
    println(stock);
    for (auto [u, v, c] : edges) {
        println(u, v, c);
    }
    for (int x : visits) {
        println(x);
    }

    return 0;
}
