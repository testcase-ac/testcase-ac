#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static vector<int> makeCase(int n, int mode) {
    vector<int> a(n);

    if (mode == 0) {
        fill(a.begin(), a.end(), 0);
    } else if (mode == 1) {
        static const int values[] = {0, 1, 4, 9, 16, 25, 36};
        for (int& x : a) {
            x = values[rnd.next(0, 6)];
        }
    } else if (mode == 2) {
        int lo = rnd.next(-10, 0);
        int hi = rnd.next(0, 10);
        for (int& x : a) {
            x = rnd.next(lo, hi);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int magnitude = rnd.next(0, 20);
            a[i] = (i % 2 == 0 ? magnitude : -magnitude);
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        for (int& x : a) {
            x = rnd.next(-100, -1);
        }
    } else {
        for (int& x : a) {
            int bucket = rnd.next(0, 4);
            if (bucket == 0) {
                x = 0;
            } else if (bucket == 1) {
                x = rnd.next(1, 10) * rnd.next(1, 10);
            } else if (bucket == 2) {
                x = -rnd.next(1, 100);
            } else {
                x = rnd.next(-100, 100);
            }
            x = max(-100, min(100, x));
        }
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 16);
    println(t);

    bool usedLarge = false;
    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int mode = caseIndex % 6;
        int n;
        if (!usedLarge && rnd.next(0, 9) == 0) {
            n = rnd.next(1001, 1400);
            usedLarge = true;
        } else if (mode == 0) {
            n = rnd.next(1, 12);
        } else if (mode == 4) {
            n = rnd.next(3, 25);
        } else {
            n = rnd.next(2, 40);
        }

        vector<int> a = makeCase(n, mode);
        println(n);
        println(a);
    }

    return 0;
}
