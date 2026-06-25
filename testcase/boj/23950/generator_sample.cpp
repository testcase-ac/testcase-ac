#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeCase(int n, int mode) {
    vector<int> a(n);

    if (mode == 0) {
        int hi = rnd.next(1, min(5, n));
        for (int& x : a) x = rnd.next(1, hi);
    } else if (mode == 1) {
        int lo = rnd.next(max(1, n / 2), 100000);
        for (int& x : a) x = rnd.next(lo, 100000);
    } else if (mode == 2) {
        int center = rnd.next(1, min(20, n + 5));
        for (int& x : a) x = max(1, min(100000, center + rnd.next(-2, 2)));
    } else if (mode == 3) {
        for (int& x : a) x = rnd.next(0, 1) ? rnd.next(1, 3) : rnd.next(99990, 100000);
    } else {
        for (int i = 0; i < n; ++i) a[i] = min(100000, i + 1 + rnd.next(0, 3));
        shuffle(a.begin(), a.end());
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (rnd.next(0, 9) == 0) {
            n = rnd.next(31, 80);
        } else {
            n = rnd.next(1, 30);
        }

        int mode = rnd.next(0, 4);
        vector<int> a = makeCase(n, mode);

        println(n);
        println(a);
    }

    return 0;
}
