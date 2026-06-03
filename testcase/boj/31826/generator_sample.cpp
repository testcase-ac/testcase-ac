#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int randomPrice() {
    return rnd.next(700, 1300) * 10;
}

int nearbyPrice(int center, int radius) {
    int lo = max(700, center / 10 - radius);
    int hi = min(1300, center / 10 + radius);
    return rnd.next(lo, hi) * 10;
}

int randomQty(int mode) {
    if (mode == 0) return rnd.next(1, 5);
    if (mode == 1) return rnd.next(900, 1000);
    return rnd.next(1, 1000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(4, 40);
    vector<pair<int, pair<int, int>>> orders;

    if (mode == 0) {
        int center = randomPrice();
        for (int i = 0; i < n; ++i) {
            int p = nearbyPrice(center, rnd.next(0, 12));
            int x = randomQty(rnd.next(0, 2));
            int f = rnd.next(0, 1) == 0 ? -1 : 1;
            orders.push_back({p, {x, f}});
        }
    } else if (mode == 1) {
        vector<int> prices = {7000, 7010, 9990, 10000, 10010, 12990, 13000};
        for (int i = 0; i < n; ++i) {
            int p = rnd.any(prices);
            int x = randomQty(rnd.next(0, 2));
            int f = rnd.next(0, 1) == 0 ? -1 : 1;
            orders.push_back({p, {x, f}});
        }
    } else if (mode == 2) {
        int p = randomPrice();
        int firstSide = rnd.next(0, 1) == 0 ? -1 : 1;
        int stored = 0;
        for (int i = 0; i < n; ++i) {
            bool cross = stored > 0 && rnd.next(0, 99) < 55;
            int f = cross ? -firstSide : firstSide;
            int x = cross ? rnd.next(1, min(1000, stored + 7)) : randomQty(rnd.next(0, 2));
            if (cross) {
                stored = max(0, stored - x);
            } else {
                stored = min(2000, stored + x);
            }
            orders.push_back({p, {x, f}});
        }
    } else {
        int base = nearbyPrice(10000, 20);
        vector<int> prices;
        for (int d = -3; d <= 3; ++d) {
            int price = base + d * 10;
            if (7000 <= price && price <= 13000) prices.push_back(price);
        }
        shuffle(prices.begin(), prices.end());
        for (int p : prices) {
            int side = rnd.next(0, 1) == 0 ? -1 : 1;
            orders.push_back({p, {rnd.next(1, 20), side}});
            orders.push_back({p, {rnd.next(1, 25), -side}});
        }
        while ((int)orders.size() < n) {
            int p = rnd.any(prices);
            int f = rnd.next(0, 1) == 0 ? -1 : 1;
            orders.push_back({p, {randomQty(0), f}});
        }
        shuffle(orders.begin(), orders.end());
    }

    println((int)orders.size());
    for (const auto& order : orders) {
        println(order.first, order.second.first, order.second.second);
    }

    return 0;
}
