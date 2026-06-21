#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

vector<int> makeSequence(int n, int mode) {
    vector<int> v(n);

    if (mode == 0) {
        fill(v.begin(), v.end(), 1);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            v[i] = rnd.next(0, 3) == 0 ? rnd.next(900, 1000) : 1;
        }
    } else if (mode == 2) {
        int start = rnd.next(1, 20);
        int step = rnd.next(1, 60);
        for (int i = 0; i < n; ++i) {
            v[i] = min(1000, start + i * step);
        }
        if (rnd.next(2) == 0) {
            reverse(v.begin(), v.end());
        }
    } else if (mode == 3) {
        int lo = rnd.next(1, 20);
        int mid = rnd.next(21, 200);
        int hi = rnd.next(700, 1000);
        vector<int> choices = {lo, mid, hi};
        for (int i = 0; i < n; ++i) {
            v[i] = rnd.any(choices);
        }
    } else {
        int hi = rnd.any(vector<int>{3, 10, 50, 1000});
        for (int i = 0; i < n; ++i) {
            v[i] = rnd.next(1, hi);
        }
    }

    return v;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(5);
    int n;
    int m;
    if (sizeMode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 3);
    } else if (sizeMode == 1) {
        n = 1;
        m = rnd.next(2, 12);
    } else if (sizeMode == 2) {
        n = rnd.next(2, 12);
        m = 1;
    } else {
        n = rnd.next(2, 14);
        m = rnd.next(2, 14);
    }

    int modeA = rnd.next(5);
    int modeB = rnd.next(5);
    if (rnd.next(4) == 0) {
        modeB = modeA;
    }

    println(n, m);
    println(makeSequence(n, modeA));
    println(makeSequence(m, modeB));

    return 0;
}
