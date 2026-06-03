#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long genValue(int mode) {
    if (mode == 0) {
        return rnd.next(1, 20);
    }
    if (mode == 1) {
        return rnd.any(vector<long long>{1, 2, 3, 999999999LL, 1000000000LL});
    }
    return rnd.next(1LL, 1000000000LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    int m = rnd.next(1, 30);

    if (mode == 0) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 8);
    } else if (mode == 1 || mode == 2) {
        n = rnd.next(8, 30);
        m = rnd.next(8, 30);
    }

    vector<int> a(n);
    if (mode == 0) {
        fill(a.begin(), a.end(), rnd.next(0, 1));
    } else if (mode == 1) {
        fill(a.begin(), a.end(), 0);
    } else if (mode == 2) {
        fill(a.begin(), a.end(), 1);
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            a[i] = i % 2;
        }
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
    } else if (mode == 4) {
        int queueCount = rnd.next(1, n);
        fill(a.begin(), a.end(), 1);
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) {
            pos[i] = i;
        }
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < queueCount; ++i) {
            a[pos[i]] = 0;
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 100) < 70 ? 1 : 0;
        }
        if (find(a.begin(), a.end(), 0) == a.end()) {
            a[rnd.next(0, n - 1)] = 0;
        }
    }

    int valueMode = rnd.next(0, 2);
    vector<long long> b(n), c(m);
    for (int i = 0; i < n; ++i) {
        b[i] = genValue(valueMode);
    }
    for (int i = 0; i < m; ++i) {
        c[i] = genValue(valueMode);
    }

    println(n);
    println(a);
    println(b);
    println(m);
    println(c);

    return 0;
}
