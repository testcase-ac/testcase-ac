#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeCase(int n, int mode) {
    vector<int> a(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) a[i] = i + 1;
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) a[i] = n - i;
    } else if (mode == 2) {
        int value = rnd.next(1, n);
        fill(a.begin(), a.end(), value);
    } else if (mode == 3) {
        int lo = rnd.next(1, n);
        int hi = rnd.next(lo, n);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) a[i] = i + 1;
        shuffle(a.begin(), a.end());
    } else if (mode == 5) {
        int block = rnd.next(1, min(n, 5));
        for (int i = 0; i < n; ++i) {
            int base = (i / block) * block + 1;
            a[i] = min(n, base + rnd.next(0, block - 1));
        }
    } else {
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                a[i] = rnd.next(1, min(n, 3));
            } else {
                a[i] = rnd.next(max(1, n - 2), n);
            }
        }
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 6);
        int n;
        if (rnd.next(0, 9) == 0) {
            n = rnd.next(30, 80);
        } else {
            n = rnd.next(2, 18);
        }

        vector<int> a = makeCase(n, mode);
        println(n);
        println(a);
    }

    return 0;
}
