#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

vector<int> consecutiveProducts() {
    vector<int> products;
    for (int start = 1; start <= 9; ++start) {
        int value = 0;
        for (int digit = start; digit <= 9; ++digit) {
            value = value * 10 + digit;
            products.push_back(value);
        }
    }
    return products;
}

vector<pair<int, int>> factorPairs(int product) {
    vector<pair<int, int>> pairs;
    for (int a = 1; a * a <= product; ++a) {
        if (product % a != 0) continue;
        int b = product / a;
        if (b <= 10000 && a != b) pairs.push_back({a, b});
    }
    return pairs;
}

void addValue(vector<int>& values, set<int>& used, int value) {
    if (value < 1 || value > 10000 || used.count(value)) return;
    used.insert(value);
    values.push_back(value);
}

void addRandomValues(vector<int>& values, set<int>& used, int targetSize, int lo, int hi) {
    int attempts = 0;
    while ((int)values.size() < targetSize && attempts < 10000) {
        addValue(values, used, rnd.next(lo, hi));
        ++attempts;
    }
    for (int value = 1; (int)values.size() < targetSize && value <= 10000; ++value) {
        addValue(values, used, value);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values;
    set<int> used;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        addValue(values, used, rnd.next(1, 10000));
    } else if (mode == 1) {
        int n = rnd.next(2, 12);
        int lo = rnd.next(1, 100);
        int hi = rnd.next(lo, min(10000, lo + rnd.next(10, 250)));
        addRandomValues(values, used, n, lo, hi);
    } else {
        vector<int> products = consecutiveProducts();
        shuffle(products.begin(), products.end());

        int forcedPairs = mode == 2 ? 1 : rnd.next(1, 4);
        for (int product : products) {
            vector<pair<int, int>> pairs = factorPairs(product);
            if (pairs.empty()) continue;
            auto pair = rnd.any(pairs);
            if (used.count(pair.first) || used.count(pair.second)) continue;
            addValue(values, used, pair.first);
            addValue(values, used, pair.second);
            if (--forcedPairs == 0) break;
        }

        int targetSize = mode == 4 ? rnd.next(20, 80) : rnd.next(max(2, (int)values.size()), 18);
        if (rnd.next(0, 1)) {
            addRandomValues(values, used, targetSize, 1, 120);
        } else {
            addRandomValues(values, used, targetSize, 1, 10000);
        }
    }

    shuffle(values.begin(), values.end());
    println((int)values.size());
    println(values);

    return 0;
}
