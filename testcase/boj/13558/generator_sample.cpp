#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampValue(int x) {
    return max(1, min(30000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(3, 30);
        int value = rnd.next(1, 30000);
        a.assign(n, value);
    } else if (mode == 1) {
        n = rnd.next(3, 45);
        vector<int> pool = {1, 30000, rnd.next(1, 10), rnd.next(29990, 30000)};
        a.resize(n);
        for (int& x : a) {
            x = rnd.any(pool);
        }
    } else if (mode == 2) {
        n = rnd.next(6, 80);
        int lo = rnd.next(1, 29980);
        int width = rnd.next(2, min(20, 30000 - lo));
        a.resize(n);
        for (int& x : a) {
            x = rnd.next(lo, lo + width);
        }
    } else if (mode == 3) {
        n = rnd.next(5, 60);
        int first = rnd.next(1, 29950);
        int diff = rnd.next(0, min(25, (30000 - first) / max(1, n - 1)));
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = first + diff * i;
        }
        if (rnd.next(0, 1) == 0) {
            shuffle(a.begin(), a.end());
        }
    } else if (mode == 4) {
        n = rnd.next(3, 70);
        int center = rnd.next(5, 29996);
        a.resize(n);
        for (int& x : a) {
            x = clampValue(center + rnd.next(-4, 4) * rnd.next(0, 3));
        }
    } else {
        n = rnd.next(20, 90);
        a.resize(n);
        for (int& x : a) {
            x = rnd.next(1, 30000);
        }
        if (rnd.next(0, 1) == 0) {
            sort(a.begin(), a.end());
        }
    }

    println(n);
    println(a);
    return 0;
}
