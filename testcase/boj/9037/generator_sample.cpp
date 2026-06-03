#include "testlib.h"

#include <vector>

using namespace std;

vector<int> makeCase(int n, int mode) {
    vector<int> c(n);

    if (mode == 0) {
        int value = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) c[i] = value;
    } else if (mode == 1) {
        int value = rnd.next(1, 15) * 2 - 1;
        for (int i = 0; i < n; ++i) c[i] = value;
        c[rnd.next(n)] = rnd.next(1, 30);
    } else if (mode == 2) {
        int low = rnd.next(1, 8);
        int high = rnd.next(23, 30);
        for (int i = 0; i < n; ++i) c[i] = (i % 2 == 0 ? low : high);
    } else if (mode == 3) {
        int center = rnd.next(5, 26);
        for (int i = 0; i < n; ++i) c[i] = max(1, min(30, center + rnd.next(-4, 4)));
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) c[i] = rnd.next(0, 1) ? 1 : 30;
    } else {
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, 30);
        for (int i = 0; i < n; ++i) c[i] = rnd.next(lo, hi);
    }

    if (rnd.next(0, 1)) shuffle(c.begin(), c.end());
    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 20);
    println(t);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int n;
        if (caseIndex == 0) {
            n = 1;
        } else if (caseIndex == 1) {
            n = 10;
        } else {
            n = rnd.next(1, 10);
        }

        int mode = caseIndex < 6 ? caseIndex : rnd.next(0, 5);
        vector<int> c = makeCase(n, mode);

        println(n);
        println(c);
    }

    return 0;
}
