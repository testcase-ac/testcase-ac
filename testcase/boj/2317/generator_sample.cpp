#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int boundedHeight(long long x) {
    x = max(1LL, min(2147483647LL, x));
    return static_cast<int>(x);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int k;

    if (mode == 0) {
        n = 1;
        k = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
        k = n;
    } else if (mode == 2) {
        n = rnd.next(4, 12);
        k = rnd.next(1, n);
    } else if (mode == 3) {
        k = rnd.next(2, 8);
        n = rnd.next(k + 1, k + 10);
    } else if (mode == 4) {
        n = rnd.next(10, 30);
        k = rnd.next(1, n);
    } else if (mode == 5) {
        n = rnd.next(30, 80);
        k = rnd.next(1, n);
    } else if (mode == 6) {
        n = rnd.next(900, 1200);
        k = rnd.next(1, n);
    } else {
        n = rnd.next(20, 60);
        k = rnd.next(1, n);
    }

    int base = rnd.next(1, 2000000000);
    int spread = rnd.next(0, 100000);
    vector<int> heights;
    heights.reserve(n);

    if (mode == 0) {
        heights.push_back(rnd.next(1, 2147483647));
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int step = rnd.next(0, spread + 3);
            heights.push_back(boundedHeight(base + (i % 2 == 0 ? step : -step)));
        }
    } else if (mode == 2) {
        for (int i = 0; i < k; ++i) {
            heights.push_back(boundedHeight(base + i * rnd.next(0, 25)));
        }
        if (rnd.next(0, 1)) reverse(heights.begin(), heights.end());
        while ((int)heights.size() < n) {
            heights.push_back(boundedHeight(base + rnd.next(-spread, spread)));
        }
    } else if (mode == 3) {
        for (int i = 0; i < k; ++i) {
            heights.push_back(boundedHeight(base + rnd.next(-5000, 5000)));
        }
        while ((int)heights.size() < n) {
            int side = rnd.next(0, 2);
            if (side == 0) heights.push_back(boundedHeight(base - rnd.next(1, 200000)));
            else if (side == 1) heights.push_back(boundedHeight(base + rnd.next(1, 200000)));
            else heights.push_back(boundedHeight(base + rnd.next(-5000, 5000)));
        }
    } else if (mode == 4) {
        int low = rnd.next(1, 1000);
        int high = rnd.next(2147482647, 2147483647);
        for (int i = 0; i < n; ++i) {
            heights.push_back(i % 2 == 0 ? low + rnd.next(0, 1000) : high - rnd.next(0, 1000));
        }
    } else if (mode == 5) {
        int value = rnd.next(1, 2147483647);
        for (int i = 0; i < n; ++i) {
            heights.push_back(boundedHeight(value + rnd.next(-3, 3)));
        }
    } else {
        for (int i = 0; i < n; ++i) {
            heights.push_back(rnd.next(1, 2147483647));
        }
    }

    println(n, k);
    for (int height : heights) println(height);

    return 0;
}
