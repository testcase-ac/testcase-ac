#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

static vector<int> makeIdentityPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    return p;
}

static vector<int> alternatingExtremes(int n) {
    vector<int> p;
    int lo = 1, hi = n;
    while (lo <= hi) {
        if (rnd.next(0, 1)) {
            p.push_back(hi--);
            if (lo <= hi) p.push_back(lo++);
        } else {
            p.push_back(lo++);
            if (lo <= hi) p.push_back(hi--);
        }
    }
    return p;
}

static vector<int> generatedByReversals(int n) {
    vector<int> p = makeIdentityPermutation(n);
    int rounds = rnd.next(1, min(n - 1, 8));
    for (int step = 0; step < rounds; ++step) {
        int left = rnd.next(0, n - 2);
        int right = rnd.next(left + 1, n - 1);
        reverse(p.begin() + left, p.begin() + right + 1);
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
        shuffle(p.begin(), p.end());
        return p;
    }
    if (mode == 3) {
        int shift = rnd.next(1, n - 1);
        rotate(p.begin(), p.begin() + shift, p.end());
        return p;
    }
    if (mode == 4) {
        int swaps = rnd.next(1, min(n - 1, 6));
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 1);
            swap(p[a], p[b]);
        }
        return p;
    }
    if (mode == 5) {
        return alternatingExtremes(n);
    }
    return generatedByReversals(n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t;
    if (rnd.next(0, 9) == 0) {
        t = rnd.next(25, 100);
    } else {
        t = rnd.next(1, 12);
    }

    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 6);
        int n;
        if (rnd.next(0, 9) == 0) {
            n = rnd.next(30, 100);
        } else {
            n = rnd.next(2, 20);
        }

        vector<int> p = makePermutation(n, mode);
        println(n);
        println(p);
    }

    return 0;
}
