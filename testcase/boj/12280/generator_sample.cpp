#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int randomValueWithParity(int parity) {
    vector<int> candidates;
    for (int x = -100; x <= 100; ++x) {
        if ((abs(x) % 2) == parity) candidates.push_back(x);
    }
    return rnd.any(candidates);
}

int randomBoundaryValue() {
    static const vector<int> values = {
        -100, -99, -98, -3, -2, -1, 0, 1, 2, 3, 98, 99, 100
    };
    return rnd.any(values);
}

vector<int> makeCase(int mode) {
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 20);
    } else if (mode == 2) {
        n = rnd.next(2, 25);
    } else if (mode == 3) {
        n = rnd.next(8, 40);
    } else if (mode == 4) {
        n = rnd.next(5, 35);
    } else if (mode == 5) {
        n = rnd.next(10, 60);
    } else {
        n = rnd.next(40, 100);
    }

    vector<int> a(n);
    if (mode == 0) {
        a[0] = rnd.next(-100, 100);
    } else if (mode == 1) {
        int parity = rnd.next(0, 1);
        for (int& x : a) x = randomValueWithParity(parity);
    } else if (mode == 2) {
        int firstParity = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) a[i] = randomValueWithParity((firstParity + i) % 2);
    } else if (mode == 3) {
        for (int& x : a) x = randomBoundaryValue();
    } else if (mode == 4) {
        vector<int> pool;
        int poolSize = rnd.next(2, 6);
        for (int i = 0; i < poolSize; ++i) pool.push_back(rnd.next(-6, 6));
        for (int& x : a) x = rnd.any(pool);
    } else if (mode == 5) {
        int split = rnd.next(1, n - 1);
        for (int i = 0; i < n; ++i) {
            int parity = i < split ? 0 : 1;
            a[i] = randomValueWithParity(parity);
        }
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else {
        int lo = rnd.next(-100, 50);
        int hi = rnd.next(lo, 100);
        for (int& x : a) x = rnd.next(lo, hi);
    }

    if (rnd.next(0, 2) == 0) shuffle(a.begin(), a.end());
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 30);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int mode = tc < 7 ? tc : rnd.next(0, 6);
        vector<int> a = makeCase(mode);
        println(static_cast<int>(a.size()));
        println(a);
    }

    return 0;
}
