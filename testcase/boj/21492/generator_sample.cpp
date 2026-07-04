#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int sizeMode = rnd.next(0, 5);
    if (sizeMode == 0) {
        n = 3;
    } else if (sizeMode == 1) {
        n = rnd.next(4, 9);
    } else if (sizeMode <= 3) {
        n = rnd.next(10, 30);
    } else {
        n = rnd.next(31, 60);
    }

    int k = rnd.next(1, n / 3);
    int mode = rnd.next(0, 6);
    vector<long long> a(n);

    if (mode == 0) {
        long long value = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            a[i] = value;
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 15);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a[i] = i + 1;
        }
        if (rnd.next(0, 1)) {
            for (int i = 0; i < n / 2; ++i) {
                swap(a[i], a[n - 1 - i]);
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? rnd.next(1, 5) : rnd.next(50, 120));
        }
    } else if (mode == 4) {
        int center = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            int distance = abs(i - center);
            a[i] = 100 - min(90, distance * rnd.next(3, 12));
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 30);
        }
        int spikes = rnd.next(1, max(1, n / 5));
        for (int i = 0; i < spikes; ++i) {
            a[rnd.next(0, n - 1)] = rnd.next(100000000LL, 1000000000LL);
        }
    } else {
        long long low = rnd.next(1, 10);
        long long high = rnd.next(20, 80);
        for (int block = 0; block * k < n; ++block) {
            long long value = (block % 2 == 0 ? low : high);
            for (int i = block * k; i < n && i < (block + 1) * k; ++i) {
                a[i] = value + rnd.next(0, 3);
            }
        }
    }

    println(n, k);
    println(a);

    return 0;
}
