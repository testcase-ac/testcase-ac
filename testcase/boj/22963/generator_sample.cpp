#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<long long> increasingArray(int n, long long start, long long maxStep) {
    vector<long long> a(n);
    a[0] = start;
    for (int i = 1; i < n; ++i) {
        a[i] = min(1000000000LL, a[i - 1] + rnd.next(0LL, maxStep));
    }
    return a;
}

void forceUnsorted(vector<long long>& a) {
    for (int i = 1; i < (int)a.size(); ++i) {
        if (a[i - 1] > a[i]) return;
    }

    int pos = rnd.next(1, (int)a.size() - 1);
    if (a[pos - 1] > 1) {
        a[pos] = rnd.next(1LL, a[pos - 1] - 1);
    } else {
        a[pos - 1] = 2;
        a[pos] = 1;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(2, 30);
    vector<long long> a;

    if (mode == 0) {
        a = increasingArray(n, rnd.next(1LL, 20LL), rnd.next(0LL, 8LL));
        int pos = rnd.next(1, n - 1);
        a[pos] = rnd.next(1LL, max(1LL, a[pos - 1] - 1));
    } else if (mode == 1) {
        a = increasingArray(n, rnd.next(1LL, 30LL), rnd.next(1LL, 10LL));
        int changes = rnd.next(2, min(3, n));
        for (int t = 0; t < changes; ++t) {
            int pos = rnd.next(n);
            a[pos] = rnd.next(1LL, 100LL);
        }
    } else if (mode == 2) {
        n = rnd.next(5, 24);
        long long start = rnd.next(4LL * n + 1, 200LL);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = start - i * rnd.next(1LL, 4LL);
    } else if (mode == 3) {
        n = rnd.next(8, 30);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? rnd.next(500LL, 900LL) : rnd.next(1LL, 400LL);
        }
    } else if (mode == 4) {
        a = increasingArray(n, rnd.next(999999800LL, 999999900LL), rnd.next(0LL, 20LL));
        int pos = rnd.next(1, n - 1);
        a[pos] = rnd.next(1LL, a[pos - 1] - 1);
    } else {
        n = rnd.next(4, 28);
        a = increasingArray(n, rnd.next(1LL, 10LL), rnd.next(0LL, 3LL));
        int l = rnd.next(0, n - 2);
        int r = rnd.next(l + 1, n - 1);
        reverse(a.begin() + l, a.begin() + r + 1);
    }

    forceUnsorted(a);

    println((int)a.size());
    println(a);

    return 0;
}
