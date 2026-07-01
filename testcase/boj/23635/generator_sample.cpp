#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k;
    int n;
    vector<int> a;

    if (mode == 0) {
        k = rnd.next(2, 5);
        n = rnd.next(k, min(12, k + 7));
        int hi = rnd.next(1, 30);
        a.resize(n);
        for (int& x : a) x = rnd.next(1, hi);
    } else if (mode == 1) {
        k = rnd.next(2, 10);
        n = rnd.next(k, min(80, k * rnd.next(1, 8)));
        int value = rnd.next(1, max(1, 500000 / n));
        a.assign(n, value);
    } else if (mode == 2) {
        k = rnd.next(2, 10);
        n = rnd.next(k, 40);
        int remaining = 500000;
        a.assign(n, 1);
        remaining -= n;
        int spikes = rnd.next(1, min(n, 6));
        for (int i = 0; i < spikes; ++i) {
            int pos = rnd.next(0, n - 1);
            int add = rnd.next(0, remaining);
            a[pos] += add;
            remaining -= add;
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 3) {
        k = rnd.next(2, 10);
        n = rnd.next(k, 70);
        int base = rnd.next(1, 12);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            int wave = i % rnd.next(2, min(9, n));
            a[i] = base + wave + rnd.next(0, 4);
        }
    } else if (mode == 4) {
        k = rnd.next(2, 10);
        n = rnd.next(k, 90);
        a.resize(n);
        int total = 0;
        for (int i = 0; i < n; ++i) {
            int limit = max(1, (500000 - total - (n - i - 1)) / (n - i));
            a[i] = rnd.wnext(limit, 2) + 1;
            total += a[i];
        }
    } else {
        k = rnd.next(2, 10);
        n = rnd.next(k, min(120, k * 15));
        int segmentValue = rnd.next(3, 60);
        a.assign(n, 1);
        int cursor = 0;
        for (int part = 0; part < k && cursor < n; ++part) {
            int len = rnd.next(1, max(1, (n - cursor) / (k - part)));
            int sum = 0;
            for (int i = 0; i < len; ++i) sum += a[cursor + i];
            while (sum < segmentValue && cursor + len - 1 < n) {
                int add = rnd.next(0, segmentValue - sum);
                a[cursor + rnd.next(0, len - 1)] += add;
                sum += add;
            }
            cursor += len;
        }
    }

    long long sum = accumulate(a.begin(), a.end(), 0LL);
    while (sum > 500000) {
        int pos = rnd.next(0, n - 1);
        if (a[pos] > 1) {
            --a[pos];
            --sum;
        }
    }

    println(k, n);
    println(a);

    return 0;
}
