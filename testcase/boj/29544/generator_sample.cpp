#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

long long boundedAround(long long k, long long delta) {
    return min(1000000000LL, max(1LL, k + delta));
}

void printCase(long long k, const vector<long long>& a) {
    println((int)a.size(), k);
    println(a);
}

vector<long long> zeroSumDeltas(int n, long long radius) {
    vector<long long> d;
    while ((int)d.size() + 1 < n) {
        long long x = rnd.next(1LL, radius);
        d.push_back(x);
        d.push_back(-x);
    }
    if ((int)d.size() < n) {
        d.push_back(0);
    }
    shuffle(d.begin(), d.end());
    return d;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 25);
        long long k = rnd.next(20LL, 1000000000LL - 20);
        vector<long long> d = zeroSumDeltas(n, 15);
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = k + d[i];
        }
        printCase(k, a);
        return 0;
    }

    if (mode == 1) {
        int n = rnd.next(6, 30);
        long long k = rnd.next(30LL, 1000000000LL - 30);
        vector<long long> a(n, k + rnd.next(1LL, 9LL));

        int len = rnd.next(2, min(12, n));
        int start = rnd.next(0, n - len);
        vector<long long> d = zeroSumDeltas(len, 20);
        for (int i = 0; i < len; ++i) {
            a[start + i] = k + d[i];
        }

        printCase(k, a);
        return 0;
    }

    if (mode == 2) {
        int n = rnd.next(1, 25);
        long long k = rnd.next(2LL, 1000000000LL - 1);
        vector<long long> a(n);
        bool above = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            long long step = rnd.next(1LL, 25LL);
            a[i] = above ? boundedAround(k, step) : boundedAround(k, -step);
        }
        printCase(k, a);
        return 0;
    }

    if (mode == 3) {
        int n = rnd.next(1, 80);
        long long k = rnd.next(1LL, 1000000000LL);
        vector<long long> a(n, k);
        printCase(k, a);
        return 0;
    }

    int n = rnd.next(2, 24);
    long long k = rnd.any(vector<long long>{1LL, 2LL, 999999999LL, 1000000000LL});
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        if (k <= 2) {
            a[i] = (i % 2 == 0 ? 1LL : min(1000000000LL, 2 * k - 1));
        } else {
            a[i] = (i % 2 == 0 ? 1000000000LL : max(1LL, 2 * k - 1000000000LL));
        }
    }
    if (rnd.next(0, 1)) {
        shuffle(a.begin(), a.end());
    }
    printCase(k, a);
    return 0;
}
