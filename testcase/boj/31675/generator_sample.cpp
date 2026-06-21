#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 2) {
        n = rnd.next(2, 8);
    } else if (mode <= 5) {
        n = rnd.next(9, 30);
    } else {
        n = rnd.next(31, 80);
    }

    vector<long long> r(n);
    if (mode == 0) {
        r[0] = rnd.next(1, 1000000000);
    } else if (mode == 1) {
        long long lo = rnd.next(1, 20);
        long long hi = rnd.next(999999950, 1000000000);
        for (int i = 0; i < n; ++i) r[i] = (i % 2 == 0 ? lo : hi);
        if (rnd.next(0, 1)) reverse(r.begin(), r.end());
    } else if (mode == 2) {
        long long base = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) r[i] = base + rnd.next(0, 5);
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) r[i] = rnd.next(1, 1000000000);
    } else if (mode == 4) {
        long long peak = rnd.next(100000000, 1000000000);
        for (int i = 0; i < n; ++i) {
            long long step = rnd.next(0, 1000);
            r[i] = max(1LL, peak - step * abs(2 * i - n + 1));
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                r[i] = rnd.next(1, 10);
            } else {
                r[i] = rnd.next(1000, 1000000);
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) r[i] = rnd.next(1, 30);
            if (bucket == 1) r[i] = rnd.next(31, 1000);
            if (bucket == 2) r[i] = rnd.next(1000000, 1000000000);
            if (bucket == 3) r[i] = (i % 2 == 0 ? 1 : 1000000000);
        }
    }

    println(n);
    println(r);
    return 0;
}
