#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    vector<long long> a(n);

    if (mode == 0) {
        long long value = rnd.next(1, 1000000000);
        fill(a.begin(), a.end(), value);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) a[i] = i + 1;
    } else if (mode == 2) {
        vector<long long> pool = {1, 2, 3, 42, 999999937LL, 1000000000LL};
        int kinds = rnd.next(1, (int)pool.size());
        shuffle(pool.begin(), pool.end());
        for (int i = 0; i < n; ++i) a[i] = pool[rnd.next(0, kinds - 1)];
    } else if (mode == 3) {
        long long base = rnd.next(1, 999999970);
        int kinds = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) a[i] = base + rnd.next(0, kinds - 1);
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 1) ? 1LL : 1000000000LL;
        }
    }

    vector<long long> b = a;
    if (mode == 0) {
        shuffle(b.begin(), b.end());
    } else if (mode == 1) {
        if (rnd.next(0, 1)) {
            reverse(b.begin(), b.end());
        } else {
            shuffle(b.begin(), b.end());
        }
    } else if (mode == 4) {
        shuffle(b.begin(), b.end());
    } else {
        int pos = 0;
        while (pos < n) {
            int remaining = n - pos;
            int len = rnd.next(1, min(remaining, 8));
            shuffle(b.begin() + pos, b.begin() + pos + len);
            pos += len;
        }
        if (rnd.next(0, 3) == 0) shuffle(b.begin(), b.end());
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
