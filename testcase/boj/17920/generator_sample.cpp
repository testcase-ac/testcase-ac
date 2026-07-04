#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampPrice(int value) {
    return max(1, min(100000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 4) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(13, 40);
    }

    int k = rnd.any(vector<int>{1, 2, 5, 10, 50, 100, rnd.next(1, 100)});
    vector<int> prices(n);

    if (mode == 0) {
        prices[0] = rnd.any(vector<int>{1, 100000, rnd.next(1, 100000)});
    } else if (mode == 1) {
        int value = rnd.next(1, 2000);
        int step = rnd.next(0, 50);
        for (int i = 0; i < n; ++i) {
            prices[i] = clampPrice(value + i * step + rnd.next(0, 3));
        }
    } else if (mode == 2) {
        int value = rnd.next(1000, 100000);
        int step = rnd.next(1, max(1, value / n));
        for (int i = 0; i < n; ++i) {
            prices[i] = clampPrice(value - i * step - rnd.next(0, 20));
        }
    } else if (mode == 3) {
        int low = rnd.next(1, 200);
        int high = rnd.next(50000, 100000);
        for (int i = 0; i < n; ++i) {
            prices[i] = (i % 2 == 0) ? high - rnd.next(0, 1000) : low + rnd.next(0, 1000);
            prices[i] = clampPrice(prices[i]);
        }
    } else if (mode == 4) {
        int base = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) {
            prices[i] = clampPrice(base + rnd.next(-2, 2));
        }
        prices[rnd.next(0, n - 1)] = clampPrice(base + rnd.next(-100, 100));
    } else if (mode == 5) {
        int value = rnd.next(100, 99900);
        for (int i = 0; i < n; ++i) {
            value = clampPrice(value + rnd.next(-5000, 5000));
            prices[i] = value;
        }
    } else {
        int highDay = rnd.next(0, n - 2);
        int lowDay = rnd.next(highDay + 1, n - 1);
        for (int i = 0; i < n; ++i) {
            prices[i] = rnd.next(1000, 5000);
        }
        prices[highDay] = rnd.next(90000, 100000);
        prices[lowDay] = rnd.next(1, 500);
    }

    println(n, k);
    println(prices);

    return 0;
}
