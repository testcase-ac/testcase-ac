#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static vector<int> makeIdentityPermutation(int n) {
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i + 1;
    }
    return p;
}

static vector<int> makePermutation(int n, int mode) {
    vector<int> p = makeIdentityPermutation(n);

    if (mode == 0) {
        return p;
    }

    if (mode == 1) {
        reverse(p.begin(), p.end());
        return p;
    }

    if (mode == 2) {
        for (int i = 0; i + 1 < n; i += 2) {
            swap(p[i], p[i + 1]);
        }
        return p;
    }

    if (mode == 3) {
        int shifts = rnd.next(1, n - 1);
        rotate(p.begin(), p.begin() + shifts, p.end());
        return p;
    }

    if (mode == 4) {
        int swaps = rnd.next(1, min(4, n));
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 1);
            swap(p[a], p[b]);
        }
        return p;
    }

    shuffle(p.begin(), p.end());
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0) {
            n = rnd.next(1, 2);
        } else if (rnd.next(100) < 25) {
            n = 10;
        } else {
            n = rnd.next(2, 9);
        }

        int mode = (n == 1) ? 0 : rnd.next(0, 5);
        vector<int> p = makePermutation(n, mode);

        println(n);
        println(p);
    }

    return 0;
}
