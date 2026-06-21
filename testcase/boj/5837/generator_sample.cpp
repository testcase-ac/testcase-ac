#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedValue(int base, int spread) {
    return max(0, min(100000, base + rnd.next(-spread, spread)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        a.push_back(rnd.any(vector<int>{0, 1, 2, 99999, 100000}));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int value = rnd.any(vector<int>{0, 1, rnd.next(2, 20), rnd.next(99980, 100000)});
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(3, 20);
        int start = rnd.next(0, 20);
        int step = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) {
            a.push_back(min(100000, start + i * step + rnd.next(0, 2)));
        }
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 3) {
        n = rnd.next(5, 25);
        int low = rnd.next(0, 3);
        int high = rnd.any(vector<int>{rnd.next(4, 40), rnd.next(99970, 100000)});
        for (int i = 0; i < n; ++i) {
            a.push_back(i % 2 == 0 ? boundedValue(high, 3) : boundedValue(low, 1));
        }
    } else if (mode == 4) {
        n = rnd.next(6, 30);
        a.assign(n, 0);
        int segments = rnd.next(1, min(6, n));
        for (int s = 0; s < segments; ++s) {
            int l = rnd.next(0, n - 1);
            int r = rnd.next(l, min(n - 1, l + rnd.next(0, 5)));
            int height = rnd.any(vector<int>{rnd.next(1, 30), rnd.next(99980, 100000)});
            for (int i = l; i <= r; ++i) a[i] = max(a[i], boundedValue(height, 5));
        }
    } else if (mode == 5) {
        n = rnd.next(8, 35);
        int center = rnd.next(1, 100000);
        int spread = rnd.next(0, min(100000, max(2, center / 4)));
        for (int i = 0; i < n; ++i) a.push_back(boundedValue(center, spread));
    } else {
        n = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 4);
            if (bucket == 0) a.push_back(0);
            else if (bucket == 1) a.push_back(rnd.next(1, 5));
            else if (bucket == 2) a.push_back(rnd.next(6, 100));
            else if (bucket == 3) a.push_back(rnd.next(99900, 100000));
            else a.push_back(rnd.next(0, 100000));
        }
    }

    println(n);
    for (int value : a) println(value);

    return 0;
}
