#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<long long> makeNondecreasing(int n) {
    vector<long long> a(n);
    long long cur = rnd.next(1, 20);
    for (int i = 0; i < n; ++i) {
        if (i > 0) cur += rnd.next(0, 5);
        a[i] = cur;
    }
    return a;
}

static vector<long long> makeNonincreasing(int n) {
    vector<long long> a = makeNondecreasing(n);
    reverse(a.begin(), a.end());
    return a;
}

static void rotateBy(vector<long long>& a, int k) {
    if (a.empty() || k == 0) return;
    rotate(a.begin(), a.begin() + k, a.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 35);
    if (mode == 6) n = rnd.next(36, 120);

    vector<long long> a;
    if (mode == 0) {
        a = makeNondecreasing(n);
    } else if (mode == 1) {
        a = makeNonincreasing(n);
    } else if (mode == 2) {
        a = makeNondecreasing(n);
        rotateBy(a, rnd.next(0, n - 1));
    } else if (mode == 3) {
        a = makeNonincreasing(n);
        rotateBy(a, rnd.next(0, n - 1));
    } else if (mode == 4) {
        a.resize(n);
        long long lo = rnd.next(1, 30);
        long long hi = rnd.next(lo, lo + rnd.next(0, 8));
        for (long long& x : a) x = rnd.next(lo, hi);
    } else {
        a.resize(n);
        long long lo = rnd.next(1, 40);
        long long hi = rnd.next(lo + 1, lo + 40);
        for (long long& x : a) x = rnd.next(lo, hi);
        if (n >= 4 && rnd.next(0, 1)) {
            int first = rnd.next(0, n - 2);
            int second = rnd.next(first + 1, n - 1);
            a[first] = hi;
            a[second] = lo;
        }
    }

    println(n);
    println(a);
    return 0;
}
