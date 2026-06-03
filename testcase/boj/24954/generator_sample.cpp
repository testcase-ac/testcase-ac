#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 4);
    } else if (mode == 5) {
        n = rnd.next(8, 10);
    } else {
        n = rnd.next(3, 8);
    }

    vector<int> price(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (mode == 2) {
            price[i] = rnd.next(1, 30);
        } else if (mode == 4) {
            price[i] = rnd.next(1, 120);
        } else {
            price[i] = rnd.next(1, 1000);
        }
    }

    vector<vector<pair<int, int>>> discounts(n + 1);
    auto addDiscount = [&](int from, int to, int value) {
        if (from == to) return;
        for (auto [existing, ignored] : discounts[from]) {
            if (existing == to) return;
        }
        discounts[from].push_back({to, max(1, min(1000, value))});
    };

    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            if (rnd.next(0, 1) == 1) {
                int to = rnd.next(1, n - 1);
                if (to >= i) ++to;
                addDiscount(i, to, rnd.next(1, 20));
            }
        }
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) {
            addDiscount(i, i + 1, rnd.next(1, 1000));
        }
        for (int i = 2; i <= n; ++i) {
            if (rnd.next(0, 2) == 0) {
                addDiscount(i, rnd.next(1, i - 1), rnd.next(1, 500));
            }
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            int to = i == n ? 1 : i + 1;
            addDiscount(i, to, rnd.next(price[to], 1000));
            if (rnd.next(0, 1) == 1) {
                int extra = rnd.next(1, n - 1);
                if (extra >= i) ++extra;
                addDiscount(i, extra, rnd.next(1, 1000));
            }
        }
    } else if (mode == 3) {
        int hub = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != hub) addDiscount(hub, i, rnd.next(1, 1000));
        }
        for (int i = 1; i <= n; ++i) {
            if (i != hub && rnd.next(0, 1) == 1) {
                addDiscount(i, hub, rnd.next(1, 1000));
            }
        }
    } else {
        double density = mode == 4 ? rnd.next(0.35, 0.75) : rnd.next(0.65, 1.0);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i != j && rnd.next() < density) {
                    int value = mode == 4 ? rnd.next(1, max(1, price[j] + 20)) : rnd.next(1, 1000);
                    addDiscount(i, j, value);
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        shuffle(discounts[i].begin(), discounts[i].end());
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << price[i];
    }
    cout << '\n';

    for (int i = 1; i <= n; ++i) {
        println(static_cast<int>(discounts[i].size()));
        for (auto [to, value] : discounts[i]) {
            println(to, value);
        }
    }

    return 0;
}
