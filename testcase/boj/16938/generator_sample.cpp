#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

long long sumAll(const vector<int>& a) {
    return accumulate(a.begin(), a.end(), 0LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 10);
    vector<int> a(n);
    long long l;
    long long r;
    int x;

    if (mode == 0) {
        n = rnd.next(2, 6);
        a.resize(n);
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, lo + rnd.next(0, 30));
        for (int& value : a) value = rnd.next(lo, hi);
        x = rnd.next(1, max(1, hi - lo + 3));
        long long total = sumAll(a);
        l = rnd.next(1LL, max(1LL, total));
        r = rnd.next(l, max(l, total + rnd.next(0, 20)));
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        a.resize(n);
        int low = rnd.next(1, 30);
        int high = rnd.next(low + 1, min(1000000, low + rnd.next(10, 200)));
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? low : high;
        }
        int tweaks = rnd.next(0, n / 3);
        for (int i = 0; i < tweaks; ++i) {
            a[rnd.next(0, n - 1)] = rnd.next(low, high);
        }
        x = rnd.next(1, high - low);
        l = rnd.next(1LL, (long long)low + high);
        r = rnd.next(max(l, (long long)low + high), sumAll(a));
    } else if (mode == 2) {
        n = rnd.next(5, 15);
        a.resize(n);
        int base = rnd.next(1, 40);
        int step = rnd.next(1, 15);
        for (int i = 0; i < n; ++i) {
            a[i] = min(1000000, base + i * step);
        }
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
        x = rnd.next(1, min(1000000, step * rnd.next(1, max(1, n - 1))));
        int left = rnd.next(0, n - 2);
        int right = rnd.next(left + 1, n - 1);
        long long target = a[left] + a[right];
        l = max(1LL, target - rnd.next(0, 10));
        r = target + rnd.next(0, 30);
    } else if (mode == 3) {
        n = 15;
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            if (i < 5) {
                a[i] = rnd.next(1, 20);
            } else if (i < 10) {
                a[i] = rnd.next(200, 5000);
            } else {
                a[i] = rnd.next(900000, 1000000);
            }
        }
        x = rnd.any(vector<int>{1, 10, 100000, 1000000});
        l = rnd.any(vector<long long>{1LL, 1000LL, 1000000LL, 1000000000LL - 1000});
        r = rnd.next(l, 1000000000LL);
    } else if (mode == 4) {
        n = rnd.next(2, 8);
        a.assign(n, rnd.next(1, 1000000));
        int different = rnd.next(0, n - 1);
        a[different] = rnd.next(1, 1000000);
        x = rnd.next(1, 1000000);
        long long pairSum = (long long)a[0] + a[min(1, n - 1)];
        l = rnd.next(1LL, min(pairSum, 1000000000LL));
        r = rnd.next(l, min(1000000000LL, sumAll(a)));
    } else {
        n = rnd.next(2, 15);
        a.resize(n);
        for (int& value : a) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) {
                value = rnd.next(1, 10);
            } else if (bucket == 1) {
                value = rnd.next(11, 1000);
            } else if (bucket == 2) {
                value = rnd.next(1001, 100000);
            } else {
                value = rnd.next(100000, 1000000);
            }
        }
        x = rnd.next(1, 1000000);
        l = rnd.next(1LL, 1000000000LL);
        r = rnd.next(l, 1000000000LL);
    }

    shuffle(a.begin(), a.end());

    println(n, l, r, x);
    println(a);
    return 0;
}
