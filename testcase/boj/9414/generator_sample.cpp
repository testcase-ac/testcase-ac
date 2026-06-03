#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MAX_PRICE = 1000000000;

int pickUnique(set<int>& used, int lo, int hi) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        int value = rnd.next(lo, hi);
        if (used.insert(value).second) {
            return value;
        }
    }

    for (int value = lo; value <= hi; ++value) {
        if (used.insert(value).second) {
            return value;
        }
    }

    quitf(_fail, "no unique value in [%d, %d]", lo, hi);
}

vector<int> makeCase(int mode) {
    set<int> used;
    vector<int> prices;

    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            prices.push_back(pickUnique(used, 1, 12));
        }
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int lo = rnd.next(2, 15);
        int hi = rnd.next(max(lo, 20), 80);
        for (int i = 0; i < n; ++i) {
            prices.push_back(pickUnique(used, lo, hi));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 6);
        int base = rnd.next(35, 70);
        for (int i = 0; i < n; ++i) {
            int lo = max(1, base - 8);
            int hi = min(MAX_PRICE, base + 8);
            prices.push_back(pickUnique(used, lo, hi));
        }
    } else if (mode == 3) {
        n = rnd.next(1, 5);
        int start = rnd.next(999999900, MAX_PRICE);
        for (int i = 0; i < n; ++i) {
            prices.push_back(pickUnique(used, max(1, start - 150), MAX_PRICE));
        }
    } else if (mode == 4) {
        n = rnd.next(30, 40);
        int lo = rnd.next(1, 10);
        int hi = lo + rnd.next(45, 120);
        for (int i = 0; i < n; ++i) {
            prices.push_back(pickUnique(used, lo, hi));
        }
    } else {
        n = rnd.next(8, 25);
        int lowCount = rnd.next(1, n - 1);
        for (int i = 0; i < lowCount; ++i) {
            prices.push_back(pickUnique(used, 1, 30));
        }
        for (int i = lowCount; i < n; ++i) {
            prices.push_back(pickUnique(used, 31, 5000));
        }
    }

    shuffle(prices.begin(), prices.end());
    return prices;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        vector<int> prices = makeCase(mode);
        for (int price : prices) {
            println(price);
        }
        println(0);
    }

    return 0;
}
