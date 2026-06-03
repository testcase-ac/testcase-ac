#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 2;
    vector<int> w;
    long long m = 1;

    if (mode == 0) {
        n = rnd.next(2, 12);
        w.assign(n, 1);
        int big = rnd.next(20, 200);
        m = rnd.next(1, big);
        for (int i = 0; i < n; ++i) w[i] = rnd.next(1, max(1, big / 3));
        w[rnd.next(n)] = rnd.next((int)m, big);
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        w.assign(n, 1);
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            w[i] = rnd.next(1, 30);
            sum += w[i];
        }
        m = sum + rnd.next(1, 30);
    } else if (mode == 2) {
        n = rnd.next(6, 22);
        w.assign(n, 1);
        int gap = rnd.next(1, min(5, n - 2));
        int base = rnd.next(1, 9);
        for (int i = 0; i < n; ++i) w[i] = rnd.next(1, base);

        long long chosen = 0;
        for (int i = rnd.next(0, gap); i < n; i += gap + 1) {
            w[i] = rnd.next(15, 40);
            chosen += w[i];
        }
        m = max(1LL, chosen - rnd.next(0, 10));
    } else if (mode == 3) {
        n = rnd.next(8, 30);
        w.assign(n, 1);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) w[i] = rnd.next(1, 5);
            else w[i] = rnd.next(20, 80);
        }
        m = rnd.next(30, min(100000000, accumulate(w.begin(), w.end(), 0) + 20));
    } else if (mode == 4) {
        n = rnd.next(2, 50);
        w.assign(n, 1);
        int hi = rnd.any(vector<int>{1, 2, 3, 9999999, 10000000});
        for (int i = 0; i < n; ++i) w[i] = rnd.next(1, hi);
        long long sum = accumulate(w.begin(), w.end(), 0LL);
        m = rnd.next(1LL, min(100000000LL, max(1LL, sum)));
    } else {
        n = rnd.next(2, 80);
        w.assign(n, 1);
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, 500);
        for (int i = 0; i < n; ++i) w[i] = rnd.next(lo, hi);
        long long sum = accumulate(w.begin(), w.end(), 0LL);
        m = rnd.next(1LL, min(100000000LL, sum + rnd.next(0, 100)));
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << w[i];
    }
    cout << '\n';
    return 0;
}
