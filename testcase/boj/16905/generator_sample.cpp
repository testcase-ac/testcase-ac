#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_VALUE = (1 << 29) - 1;

vector<int> makeValues(int n, int mode) {
    vector<int> a(n);

    if (mode == 0) {
        int hi = rnd.next(0, 31);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, hi);
    } else if (mode == 1) {
        vector<int> pool;
        int poolSize = rnd.next(1, min(6, n));
        for (int i = 0; i < poolSize; ++i) pool.push_back(rnd.next(0, MAX_VALUE));
        for (int i = 0; i < n; ++i) a[i] = rnd.any(pool);
    } else if (mode == 2) {
        int base = 1 << rnd.next(0, 29);
        int noiseMask = (1 << rnd.next(0, 10)) - 1;
        for (int i = 0; i < n; ++i) a[i] = (base ^ rnd.next(0, noiseMask)) & MAX_VALUE;
    } else if (mode == 3) {
        int x = rnd.next(0, MAX_VALUE);
        int y = rnd.next(0, MAX_VALUE);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? x : y);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) a[i] = rnd.next(0, MAX_VALUE);
        }
    } else {
        int bitLimit = rnd.next(1, 29);
        int hi = (1 << bitLimit) - 1;
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, hi);
    }

    if (rnd.next(0, 1)) shuffle(a.begin(), a.end());
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n, m;
    if (sizeMode == 0) {
        n = rnd.next(2, 3);
        m = rnd.next(2, 3);
    } else if (sizeMode == 1) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
    } else if (sizeMode == 2) {
        n = rnd.next(20, 60);
        m = rnd.next(2, 8);
        if (rnd.next(0, 1)) swap(n, m);
    } else if (sizeMode == 3) {
        n = rnd.next(15, 45);
        m = rnd.next(15, 45);
    } else {
        n = rnd.next(80, 160);
        m = rnd.next(80, 160);
    }

    int vMode = rnd.next(0, 4);
    int uMode = rnd.next(0, 4);
    vector<int> v = makeValues(n, vMode);
    vector<int> u = makeValues(m, uMode);

    if (rnd.next(0, 5) == 0) {
        fill(v.begin(), v.end(), 0);
    }
    if (rnd.next(0, 5) == 0) {
        fill(u.begin(), u.end(), 0);
    }

    println(n, m);
    println(v);
    println(u);

    return 0;
}
