#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> identityPermutation(int n) {
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i + 1;
    }
    return p;
}

static vector<int> makePermutation(int n, int mode) {
    vector<int> p = identityPermutation(n);

    if (mode == 0) {
        return p;
    }

    if (mode == 1) {
        reverse(p.begin(), p.end());
        return p;
    }

    if (mode == 2) {
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 1);
            swap(p[a], p[b]);
        }
        return p;
    }

    if (mode == 3) {
        int l = rnd.next(0, n - 1);
        int r = rnd.next(l, n - 1);
        reverse(p.begin() + l, p.begin() + r + 1);
        return p;
    }

    if (mode == 4) {
        int block = rnd.next(1, max(1, n / 3));
        for (int l = 0; l < n; l += block) {
            int r = min(n, l + block);
            shuffle(p.begin() + l, p.begin() + r);
        }
        return p;
    }

    shuffle(p.begin(), p.end());
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0 && rnd.next(0, 3) == 0) {
            n = 1;
        } else {
            n = rnd.next(2, 40);
        }

        int mode = rnd.next(0, 5);
        vector<int> p = makePermutation(n, mode);

        println(n);
        for (int value : p) {
            println(value);
        }
    }

    return 0;
}
