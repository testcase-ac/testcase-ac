#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

static void addRandom(vector<int> &a, int count, int lo, int hi) {
    for (int i = 0; i < count; ++i) {
        a.push_back(rnd.next(lo, hi));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a;
    int mode = rnd.next(6);

    if (mode == 0) {
        int n = rnd.next(2, 18);
        int mn = rnd.next(1, 40);
        a.push_back(mn);
        addRandom(a, n - 1, mn + 1, min(100000, mn + 200));
    } else if (mode == 1) {
        int n = rnd.next(3, 22);
        int mn = rnd.next(2, 80);
        a.push_back(mn);
        a.push_back(mn);
        for (int i = 2; i < n; ++i) {
            int q = rnd.next(1, 40);
            int r = rnd.next(0, mn - 1);
            a.push_back(min(100000, q * mn + r));
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 25);
        int x = rnd.next(1, 100000);
        a.assign(n, x);
    } else if (mode == 3) {
        int n = rnd.next(4, 20);
        int mn = rnd.next(2, 60);
        a.push_back(mn);
        a.push_back(mn);
        for (int i = 2; i < n; ++i) {
            int r = (i % 3 == 0) ? mn - 1 : rnd.next(0, mn - 1);
            int base = rnd.next(1, 100000 / mn) * mn;
            a.push_back(min(100000, base + r));
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 16);
        addRandom(a, n, 99900, 100000);
        if (rnd.next(2) == 0) {
            a[rnd.next(n)] = 1;
        }
    } else {
        int n = rnd.next(2, 40);
        int lo = rnd.next(1, 90000);
        int hi = rnd.next(lo, min(100000, lo + rnd.next(20, 1000)));
        addRandom(a, n, lo, hi);
    }

    shuffle(a.begin(), a.end());

    println((int)a.size());
    println(a);

    return 0;
}
