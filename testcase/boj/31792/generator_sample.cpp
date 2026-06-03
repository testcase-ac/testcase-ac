#include "testlib.h"

#include <algorithm>
#include <map>
#include <vector>
using namespace std;

const int MIN_PRICE = 1000;
const int MAX_PRICE = 1000000;

int clampPrice(int x) {
    return min(MAX_PRICE, max(MIN_PRICE, x));
}

int jittered(int base, int radius) {
    return clampPrice(base + rnd.next(-radius, radius));
}

int randomPowerPrice() {
    vector<int> prices;
    for (int x = MIN_PRICE; x <= MAX_PRICE; x *= 2) {
        prices.push_back(x);
        if (x <= MAX_PRICE / 2) prices.push_back(x * 2 - 1);
        if (x <= MAX_PRICE / 2) prices.push_back(x * 2);
        if (x <= (MAX_PRICE + 1) / 2) prices.push_back(x * 2 + 1);
    }
    return clampPrice(rnd.any(prices));
}

int chooseExisting(const map<int, int>& active) {
    int index = rnd.next((int)active.size());
    auto it = active.begin();
    advance(it, index);
    return it->first;
}

int choosePrice(int mode, const vector<int>& anchors, const map<int, int>& active) {
    if (!active.empty() && rnd.next(100) < 25) {
        return chooseExisting(active);
    }

    if (mode == 0) {
        int anchor = rnd.any(anchors);
        return jittered(anchor, rnd.next(0, 40));
    }

    if (mode == 1) {
        return randomPowerPrice();
    }

    if (mode == 2) {
        vector<int> boundary = {MIN_PRICE, MIN_PRICE + 1, MAX_PRICE - 1, MAX_PRICE,
                                500000, 500001, 999999};
        return rnd.any(boundary);
    }

    int lo = rnd.next(MIN_PRICE, 20000);
    int hi = rnd.next(50000, MAX_PRICE);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int q = rnd.next(2, mode == 3 ? 90 : 55);

    vector<int> anchors;
    int base = rnd.next(MIN_PRICE, 200000);
    anchors.push_back(base);
    anchors.push_back(clampPrice(2 * base - rnd.next(0, 3)));
    anchors.push_back(clampPrice(2 * base + rnd.next(0, 3)));
    anchors.push_back(clampPrice(4 * base));

    map<int, int> active;
    vector<pair<int, int>> queries;
    bool hasReport = false;

    for (int i = 0; i < q; ++i) {
        int remaining = q - i;
        bool mustReport = !hasReport && remaining == 1;

        int type;
        if (mustReport) {
            type = 3;
        } else if (active.empty()) {
            type = rnd.next(100) < 80 ? 1 : 3;
        } else {
            int roll = rnd.next(100);
            if (roll < 48) {
                type = 1;
            } else if (roll < 76) {
                type = 2;
            } else {
                type = 3;
            }
        }

        if (type == 1) {
            int price = choosePrice(mode, anchors, active);
            ++active[price];
            queries.push_back({1, price});
        } else if (type == 2) {
            int price = chooseExisting(active);
            auto it = active.find(price);
            --it->second;
            if (it->second == 0) active.erase(it);
            queries.push_back({2, price});
        } else {
            hasReport = true;
            queries.push_back({3, 0});
        }
    }

    println((int)queries.size());
    for (auto [type, price] : queries) {
        if (type == 3) {
            println(3);
        } else {
            println(type, price);
        }
    }

    return 0;
}
