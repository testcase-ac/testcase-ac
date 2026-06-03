#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 20);
    int m = rnd.next(1, 30);
    long long k = rnd.next(1, 200);
    vector<int> t(m);
    vector<long long> r(m);

    auto fillT = [&]() {
        int pattern = rnd.next(0, 3);
        for (int i = 0; i < m; ++i) {
            if (pattern == 0) {
                t[i] = rnd.next(1, n);
            } else if (pattern == 1) {
                t[i] = min(n, 1 + i % max(1, n));
            } else if (pattern == 2) {
                t[i] = n;
            } else {
                t[i] = rnd.next(1, min(n, 3));
            }
        }
    };

    fillT();

    if (mode == 0) {
        m = rnd.next(1, 8);
        t.resize(m);
        r.assign(m, 1);
        fillT();
        k = rnd.next((long long)m, (long long)m + 30);
    } else if (mode == 1) {
        m = rnd.next(2, 12);
        t.resize(m);
        r.assign(m, 1);
        fillT();
        int breakAt = rnd.next(1, m);
        for (int i = 0; i < breakAt - 1; ++i) r[i] = rnd.next(1, 20);
        long long before = 0;
        for (int i = 0; i < breakAt - 1; ++i) before += r[i];
        k = before + rnd.next(1, 20);
        r[breakAt - 1] = k - before + rnd.next(1, 20);
        for (int i = breakAt; i < m; ++i) r[i] = rnd.next(1, 20);
    } else if (mode == 2) {
        m = rnd.next(2, 16);
        t.resize(m);
        r.assign(m, 1);
        fillT();
        long long sum = 0;
        for (int i = 0; i < m; ++i) {
            r[i] = rnd.next(1, 15);
            sum += r[i];
        }
        k = sum;
    } else if (mode == 3) {
        n = rnd.next(1, 100000);
        m = rnd.next(2, 10);
        t.resize(m);
        r.assign(m, 1);
        fillT();
        k = rnd.next(1000000000LL, 2000000000LL);
        long long remaining = min(2000000000LL, k + rnd.next(0, 5));
        for (int i = 0; i < m; ++i) {
            long long minLeft = m - i - 1;
            long long maxLeft = 1000000000LL * (m - i - 1);
            long long lo = max(1LL, remaining - maxLeft);
            long long hi = min(1000000000LL, remaining - minLeft);
            long long take = (i == m - 1) ? remaining : rnd.next(lo, hi);
            r[i] = take;
            remaining -= take;
        }
    } else {
        long long targetSum = rnd.next((long long)m, 300LL);
        k = rnd.next(1LL, targetSum);
        long long remaining = targetSum;
        for (int i = 0; i < m; ++i) {
            long long maxTake = remaining - (m - i - 1);
            r[i] = rnd.next(1LL, maxTake);
            remaining -= r[i];
        }
    }

    long long total = 0;
    for (long long x : r) total += x;
    ensure(total <= 2000000000LL);

    println(n, m, k);
    for (int i = 0; i < m; ++i) println(t[i], r[i]);
    return 0;
}
