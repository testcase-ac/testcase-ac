#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeCase(int n, int mode) {
    vector<int> x(n);

    if (mode == 0) {
        int value = rnd.next(1, 200);
        fill(x.begin(), x.end(), value);
    } else if (mode == 1) {
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, min(200, lo + rnd.next(0, 30)));
        for (int& value : x) {
            value = rnd.next(lo, hi);
        }
    } else if (mode == 2) {
        int lo = rnd.next(170, 200);
        for (int& value : x) {
            value = rnd.next(lo, 200);
        }
    } else if (mode == 3) {
        int start = rnd.next(1, 200);
        int step = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            x[i] = min(200, start + i * step);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            x[i] = (i % 2 == 0 ? rnd.next(1, 8) : rnd.next(193, 200));
        }
    } else {
        for (int& value : x) {
            value = rnd.next(1, 200);
        }
    }

    if (rnd.next(2) == 0) {
        sort(x.begin(), x.end());
    } else {
        shuffle(x.begin(), x.end());
    }

    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        if (mode == 0) {
            n = rnd.any(vector<int>{1, 2, 3, 10, 50, 200});
        } else if (mode == 3) {
            n = rnd.next(2, 25);
        } else if (rnd.next(5) == 0) {
            n = rnd.next(80, 200);
        } else {
            n = rnd.next(1, 20);
        }

        vector<int> x = makeCase(n, mode);
        println(n);
        println(x);
    }

    return 0;
}
