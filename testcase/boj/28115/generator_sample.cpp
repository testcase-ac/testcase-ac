#include "testlib.h"
#include <vector>
using namespace std;

const long long MIN_A = -1000000000LL;
const long long MAX_A = 1000000000LL;

long long clampA(long long x) {
    if (x < MIN_A) return MIN_A;
    if (x > MAX_A) return MAX_A;
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<long long> a;

    if (mode == 0) {
        n = rnd.next(1, 2);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.any(vector<long long>{MIN_A, -1, 0, 1, MAX_A});
    } else if (mode == 1) {
        n = rnd.next(3, 35);
        long long d = rnd.next(-1000000LL, 1000000LL);
        long long lo = MIN_A;
        long long hi = MAX_A - d * (n - 1);
        if (d < 0) lo = MIN_A - d * (n - 1);
        long long first = rnd.next(lo, hi);
        for (int i = 0; i < n; ++i) a.push_back(first + d * i);
    } else if (mode == 2) {
        n = rnd.next(3, 40);
        long long first = rnd.next(-10000LL, 10000LL);
        long long d = rnd.next(-1000LL, 1000LL);
        for (int i = 0; i < n; ++i) a.push_back(first + d * i);

        int pos = rnd.next(1, n - 1);
        long long delta = rnd.any(vector<long long>{-7, -3, -1, 1, 3, 7});
        a[pos] = clampA(a[pos] + delta);
        if (a[pos] == first + d * pos) a[pos] = clampA(a[pos] + (a[pos] == MAX_A ? -1 : 1));
    } else if (mode == 3) {
        n = rnd.next(3, 45);
        long long span = rnd.any(vector<long long>{5, 20, 1000, 1000000000LL});
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(-span, span));
    } else if (mode == 4) {
        n = rnd.next(3, 30);
        long long x = rnd.next(-1000LL, 1000LL);
        long long y = rnd.next(-1000LL, 1000LL);
        if (x == y) ++y;
        for (int i = 0; i < n; ++i) a.push_back(i % 2 == 0 ? x : y);
    } else {
        n = rnd.next(3, 25);
        vector<long long> pool = {MIN_A, MIN_A + 1, -1, 0, 1, MAX_A - 1, MAX_A};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    }

    println(n);
    println(a);
    return 0;
}
