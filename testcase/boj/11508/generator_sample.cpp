#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> prices;

    if (mode == 0) {
        n = rnd.next(1, 8);
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, min(100000, lo + rnd.next(0, 30)));
        for (int i = 0; i < n; ++i) {
            prices.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 1) {
        n = 3 * rnd.next(1, 5) + rnd.next(0, 2);
        int base = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-3, 3);
            prices.push_back(max(1, min(100000, base + delta)));
        }
    } else if (mode == 2) {
        n = rnd.next(3, 15);
        for (int i = 0; i < n; ++i) {
            prices.push_back(rnd.any(vector<int>{1, 2, 99999, 100000}));
        }
    } else if (mode == 3) {
        n = rnd.next(4, 18);
        int groups = rnd.next(2, 5);
        vector<int> choices;
        for (int i = 0; i < groups; ++i) {
            choices.push_back(rnd.next(1, 100000));
        }
        for (int i = 0; i < n; ++i) {
            prices.push_back(rnd.any(choices));
        }
    } else if (mode == 4) {
        n = rnd.next(6, 24);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 2);
            if (bucket == 0) {
                prices.push_back(rnd.next(1, 50));
            } else if (bucket == 1) {
                prices.push_back(rnd.next(500, 1000));
            } else {
                prices.push_back(rnd.next(90000, 100000));
            }
        }
    } else {
        n = rnd.next(10, 30);
        for (int i = 0; i < n; ++i) {
            prices.push_back(rnd.next(1, 100000));
        }
    }

    if (rnd.next(0, 1)) {
        sort(prices.begin(), prices.end());
    } else {
        shuffle(prices.begin(), prices.end());
    }

    println(n);
    for (int price : prices) {
        println(price);
    }

    return 0;
}
