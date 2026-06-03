#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tc = rnd.next(3, 7);
    for (int caseNo = 0; caseNo < tc; ++caseNo) {
        int mode = rnd.next(5);
        int n = rnd.next(1, 12);

        vector<pair<int, int>> allEdges;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                allEdges.push_back({i, j});
            }
        }
        shuffle(allEdges.begin(), allEdges.end());

        vector<pair<int, int>> edges;
        if (mode == 0) {
            // No roads: every occupied city forms its own component.
        } else if (mode == 1) {
            int take = rnd.next(0, min<int>(allEdges.size(), n));
            edges.insert(edges.end(), allEdges.begin(), allEdges.begin() + take);
        } else if (mode == 2 && n >= 2) {
            vector<int> order(n);
            iota(order.begin(), order.end(), 1);
            shuffle(order.begin(), order.end());
            int pathLen = rnd.next(1, n - 1);
            for (int i = 0; i < pathLen; ++i) {
                edges.push_back(minmax(order[i], order[i + 1]));
            }
        } else if (mode == 3) {
            int take = rnd.next(0, static_cast<int>(allEdges.size()));
            edges.insert(edges.end(), allEdges.begin(), allEdges.begin() + take);
        } else {
            for (auto edge : allEdges) {
                if (rnd.next(100) < 35) {
                    edges.push_back(edge);
                }
            }
        }

        sort(edges.begin(), edges.end());
        edges.erase(unique(edges.begin(), edges.end()), edges.end());
        shuffle(edges.begin(), edges.end());

        int k = rnd.next(1, min(25, max(1, n * 3)));

        println(n, static_cast<int>(edges.size()), k);
        for (auto [a, b] : edges) {
            if (rnd.next(2)) {
                swap(a, b);
            }
            println(a, b);
        }

        for (int i = 0; i < k; ++i) {
            int city;
            if (i > 0 && rnd.next(100) < 35) {
                city = rnd.next(1, min(n, 3));
            } else {
                city = rnd.next(1, n);
            }

            int headsMode = rnd.next(5);
            int s;
            int grown;
            if (headsMode == 0) {
                s = 1;
                grown = 0;
            } else if (headsMode == 1) {
                s = rnd.next(1, 8);
                grown = rnd.next(0, 8);
            } else if (headsMode == 2) {
                s = rnd.next(8, 40);
                grown = rnd.next(0, 20);
            } else if (headsMode == 3) {
                s = rnd.next(1, 100);
                grown = rnd.next(80, 200);
            } else {
                s = rnd.next(90000, 100000);
                grown = rnd.next(0, 100000);
            }
            println(city, s, grown);
        }
    }

    println(0, 0, 0);
    return 0;
}
