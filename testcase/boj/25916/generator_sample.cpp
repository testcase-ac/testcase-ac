#include "testlib.h"
#include <vector>
using namespace std;

const long long MAX_A = 1000000000LL;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 35);
    long long m = rnd.next(1LL, MAX_A);
    vector<long long> a(n);

    if (mode == 0) {
        n = rnd.next(1, 8);
        m = rnd.next(1LL, 20LL);
        a.assign(n, 1);
        for (long long& x : a) x = rnd.next(1LL, 20LL);
    } else if (mode == 1) {
        n = rnd.next(3, 20);
        m = rnd.next(5LL, 80LL);
        a.assign(n, 1);
        int len = rnd.next(1, min(n, 8));
        int start = rnd.next(0, n - len);
        long long remaining = m;
        for (int i = 0; i < len; ++i) {
            long long minLeft = len - i - 1;
            long long value = (i + 1 == len) ? remaining : rnd.next(1LL, remaining - minLeft);
            a[start + i] = value;
            remaining -= value;
        }
        for (int i = 0; i < n; ++i) {
            if (i < start || i >= start + len) a[i] = rnd.next(1LL, min(20LL, m));
        }
    } else if (mode == 2) {
        n = rnd.next(5, 30);
        m = rnd.next(10LL, 100LL);
        a.assign(n, 1);
        for (int i = 0; i < n; ++i) {
            if (i % rnd.next(2, 5) == 0) {
                a[i] = m + rnd.next(1LL, 50LL);
            } else {
                a[i] = rnd.next(1LL, min(15LL, m));
            }
        }
    } else if (mode == 3) {
        n = rnd.next(1, 25);
        m = rnd.next(1LL, 100LL);
        a.assign(n, 1);
        for (long long& x : a) x = rnd.next(m + 1, min(MAX_A, m + 1000));
    } else if (mode == 4) {
        n = rnd.next(20, 80);
        m = rnd.next(30LL, 300LL);
        int upper = rnd.next(1, 12);
        a.assign(n, 1);
        for (long long& x : a) x = rnd.next(1, upper);
    } else if (mode == 5) {
        n = rnd.next(2, 25);
        m = MAX_A - rnd.next(0LL, 1000LL);
        a.assign(n, 1);
        for (long long& x : a) x = rnd.next(max(1LL, m - 2000), MAX_A);
    } else {
        n = rnd.next(2, 40);
        vector<long long> budgets = {1LL, 2LL, 10LL, 1000000000LL};
        m = rnd.any(budgets);
        a.assign(n, 1);
        for (long long& x : a) {
            if (m <= 2) {
                x = rnd.next(1LL, 3LL);
            } else {
                x = rnd.next(1LL, min(MAX_A, m + 2));
            }
        }
    }

    println(n, m);
    println(a);
    return 0;
}
