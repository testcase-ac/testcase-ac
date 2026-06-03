#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int k = rnd.next(1, min(n, 4));
    int mode = rnd.next(0, 4);

    vector<tuple<int, int, int>> flights;
    auto addFlight = [&](int u, int v, int d) {
        flights.emplace_back(u, v, d);
    };

    int backboneEnd = min(n, max(k + 1, 2));
    for (int i = 1; i < backboneEnd; ++i) {
        addFlight(i, i + 1, rnd.next(1, 30));
    }
    if (backboneEnd < n && rnd.next(0, 1)) {
        addFlight(backboneEnd + 1, 1, rnd.next(1, 30));
    }

    if (mode == 1 || mode == 3) {
        for (int v = k + 1; v <= n; ++v) {
            addFlight(v, rnd.next(1, k), rnd.next(1, 80));
            if (rnd.next(0, 1)) {
                addFlight(rnd.next(1, k), v, rnd.next(1, 80));
            }
        }
    }

    if (mode == 2 || mode == 4) {
        int loopCount = rnd.next(1, min(4, n));
        for (int i = 0; i < loopCount; ++i) {
            int v = rnd.next(1, n);
            addFlight(v, v, rnd.next(1, 1000000));
        }
    }

    int extra = rnd.next(0, 20);
    for (int i = 0; i < extra; ++i) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        int d;
        if (rnd.next(0, 9) == 0) {
            d = 1000000;
        } else {
            d = rnd.next(1, 200);
        }
        addFlight(u, v, d);
    }

    shuffle(flights.begin(), flights.end());
    int m = min<int>(flights.size(), 10000);
    flights.resize(m);

    int q = rnd.next(1, 20);
    vector<pair<int, int>> queries;
    queries.reserve(q);
    while ((int)queries.size() < q) {
        int choice = rnd.next(0, 4);
        if (choice == 0) {
            queries.emplace_back(rnd.next(1, k), rnd.next(1, n));
        } else if (choice == 1) {
            queries.emplace_back(rnd.next(1, n), rnd.next(1, k));
        } else if (choice == 2 && k < n) {
            queries.emplace_back(rnd.next(k + 1, n), rnd.next(k + 1, n));
        } else if (choice == 3) {
            int v = rnd.next(1, n);
            queries.emplace_back(v, v);
        } else {
            queries.emplace_back(rnd.next(1, n), rnd.next(1, n));
        }
    }

    println(n, m, k, q);
    for (auto [u, v, d] : flights) {
        println(u, v, d);
    }
    for (auto [a, b] : queries) {
        println(a, b);
    }

    return 0;
}
