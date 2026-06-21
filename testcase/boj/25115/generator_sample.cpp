#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long clampPrice(long long value) {
    return max(1LL, min(1000000000LL, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<long long> prices;

    if (mode == 0) {
        n = rnd.next(1, 2);
        for (int i = 0; i < n; ++i) {
            long long base = rnd.any(vector<long long>{1, 9, 10, 11, 99, 100, 101, 1000000000LL});
            prices.push_back(base);
        }
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        long long base = rnd.next(1, 20) * 10LL;
        for (int i = 0; i < n; ++i) {
            prices.push_back(clampPrice(base + rnd.next(-2, 2)));
        }
    } else if (mode == 2) {
        n = rnd.next(4, 18);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                prices.push_back(rnd.next(900000000, 1000000000));
            } else {
                prices.push_back(rnd.next(1, 25));
            }
        }
    } else if (mode == 3) {
        n = rnd.next(5, 30);
        long long current = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            current += rnd.next(0, 20);
            prices.push_back(clampPrice(current));
        }
        if (rnd.next(0, 1) == 1) {
            reverse(prices.begin(), prices.end());
        }
    } else if (mode == 4) {
        n = rnd.next(8, 40);
        long long low = rnd.next(1, 100);
        long long high = rnd.next(low, min(1000000000LL, low + rnd.next(0, 1000)));
        for (int i = 0; i < n; ++i) {
            prices.push_back(rnd.next(low, high));
        }
    } else {
        n = rnd.next(20, 80);
        vector<long long> pool = {1, 2, 9, 10, 11, 19, 20, 21, 99, 100, 101, 999999999LL, 1000000000LL};
        for (int i = 0; i < n; ++i) {
            prices.push_back(rnd.any(pool));
        }
    }

    println(n);
    println(prices);

    return 0;
}
