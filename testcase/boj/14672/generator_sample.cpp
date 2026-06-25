#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    int mode = rnd.next(0, 5);
    vector<int> a;
    int n = 0;

    if (mode == 0) {
        n = rnd.next(2, 80);
        int m = rnd.next(1, 12);
        for (int i = 0; i < m; ++i) {
            int x = rnd.next(2, n);
            a.push_back(x);
            if (rnd.next(0, 3) == 0 && (int)a.size() < 15) a.push_back(x);
        }
    } else if (mode == 1) {
        n = rnd.next(12, 300);
        int base = rnd.any(smallPrimes);
        int m = rnd.next(4, 14);
        for (int i = 0; i < m; ++i) {
            int other = rnd.any(smallPrimes);
            long long x = base;
            if (rnd.next(0, 1)) x *= other;
            if (rnd.next(0, 2) == 0) x *= base;
            while (x > n) x /= base;
            a.push_back((int)max(2LL, x));
        }
    } else if (mode == 2) {
        n = rnd.next(30, 1000);
        vector<int> values;
        for (int p : smallPrimes) {
            if (p <= n) values.push_back(p);
            if (p * p <= n) values.push_back(p * p);
        }
        shuffle(values.begin(), values.end());
        int m = rnd.next(1, min(12, (int)values.size()));
        a.assign(values.begin(), values.begin() + m);
    } else if (mode == 3) {
        n = rnd.next(100, 5000);
        int m = rnd.next(4, 14);
        for (int i = 0; i < m; ++i) {
            int x = 1;
            int factors = rnd.next(1, 4);
            for (int j = 0; j < factors; ++j) {
                int p = rnd.any(smallPrimes);
                if ((long long)x * p <= n) x *= p;
            }
            a.push_back(max(2, x));
        }
    } else if (mode == 4) {
        n = 100000000;
        vector<int> values = {2, 2, 3, 6, 99999989, 99999990, 100000000};
        int extra = rnd.next(0, 6);
        for (int i = 0; i < extra; ++i) {
            int p = rnd.any(smallPrimes);
            int q = rnd.next(2, 1000);
            values.push_back(min(n, p * q));
        }
        shuffle(values.begin(), values.end());
        a = values;
    } else {
        n = rnd.next(2, 20);
        int m = rnd.next(1, 10);
        int x = rnd.next(2, n);
        a.assign(m, x);
    }

    println(n, (int)a.size());
    println(a);
    return 0;
}
