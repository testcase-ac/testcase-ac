#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 6) {
        n = rnd.next(30, 50);
    } else {
        n = rnd.next(2, 25);
    }

    int k;
    if (mode == 0 || rnd.next(0, 9) == 0) {
        k = n;
    } else if (rnd.next(0, 5) == 0) {
        k = 1;
    } else {
        k = rnd.next(1, min(n, 50));
    }

    vector<long long> a(n);
    if (mode == 0) {
        a[0] = rnd.any(vector<long long>{0LL, 1LL, 1000000000LL});
    } else if (mode == 1) {
        long long value = rnd.next(0, 20);
        fill(a.begin(), a.end(), value);
    } else if (mode == 2) {
        long long lo = rnd.next(0, 5);
        long long hi = rnd.next(999999990LL, 1000000000LL);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, 1) ? lo : hi;
    } else if (mode == 3) {
        long long start = rnd.next(0, 10);
        long long step = rnd.next(0, 4);
        for (int i = 0; i < n; ++i) a[i] = start + step * i;
    } else if (mode == 4) {
        vector<long long> pool;
        int poolSize = rnd.next(2, min(n, 6));
        for (int i = 0; i < poolSize; ++i) pool.push_back(rnd.next(0, 30));
        pool.push_back(1000000000LL);
        for (int i = 0; i < n; ++i) a[i] = rnd.any(pool);
    } else if (mode == 5) {
        long long cap = rnd.next(3, 1000);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0LL, cap);
    } else {
        for (int i = 0; i < n; ++i) {
            if (i % 10 == 0) {
                a[i] = 1000000000LL;
            } else {
                a[i] = rnd.next(0, 200);
            }
        }
    }

    shuffle(a.begin(), a.end());

    println(n, k);
    println(a);

    return 0;
}
