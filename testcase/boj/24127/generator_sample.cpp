#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxIndex = 1LL << 60;
    int mode = rnd.next(0, 5);
    int m;
    long long p;
    long long q;
    vector<int> a;

    if (mode == 0) {
        m = rnd.next(2, 6);
        p = rnd.next(1LL, 20LL);
        q = rnd.next(p + 1, p + rnd.next(1LL, 30LL));
        a.assign(m, 0);
    } else if (mode == 1) {
        m = rnd.next(2, 10);
        p = rnd.next(1LL, static_cast<long long>(m));
        q = rnd.next(p + 1, static_cast<long long>(m * rnd.next(2, 8)));
        a.resize(m);
        for (int i = 0; i < m; ++i) a[i] = i % 2;
    } else if (mode == 2) {
        m = rnd.next(2, 24);
        long long base = rnd.next(max(1LL, maxIndex - 2000), maxIndex - 1);
        p = base;
        q = rnd.next(p + 1, maxIndex);
        a.resize(m);
        for (int i = 0; i < m; ++i) a[i] = rnd.next(0, 1) ? 1999999999 : 0;
    } else if (mode == 3) {
        m = rnd.next(18, 24);
        p = rnd.next(1LL, 1000000LL);
        q = rnd.next(p + 1, p + rnd.next(1000LL, 1000000LL));
        a.resize(m);
        for (int i = 0; i < m; ++i) a[i] = rnd.next(0, 1999999999);
    } else if (mode == 4) {
        m = rnd.next(2, 24);
        p = rnd.next(1LL, 1000LL);
        q = rnd.next(p + 1, p + rnd.next(1LL, 1000LL));
        a.resize(m);
        int hot = rnd.next(0, m - 1);
        for (int i = 0; i < m; ++i) a[i] = (i == hot ? 1999999999 : rnd.next(0, 100) * 2);
    } else {
        m = rnd.next(2, 24);
        p = rnd.next(1LL, 1000000000000LL);
        q = rnd.next(p + 1, min(maxIndex, p + rnd.next(1LL, 1000000LL)));
        a.resize(m);
        int lo = rnd.next(0, 50);
        int hi = rnd.next(lo, 200);
        for (int i = 0; i < m; ++i) a[i] = rnd.next(lo, hi);
    }

    println(m);
    println(p);
    println(q);
    for (int x : a) println(x);

    return 0;
}
