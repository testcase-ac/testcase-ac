#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct TestCase {
    int r;
    int c;
    int n;
};

int randomNForMode(int cells, int mode) {
    if (mode == 0) return rnd.next(0, min(cells, 3));
    if (mode == 1) return max(0, cells - rnd.next(0, min(cells, 3)));

    int halfFloor = cells / 2;
    int halfCeil = (cells + 1) / 2;
    int lo = max(0, halfFloor - 2);
    int hi = min(cells, halfCeil + 3);
    return rnd.next(lo, hi);
}

TestCase makeCase(int mode) {
    int r;
    int c;

    if (mode == 0) {
        r = 1;
        c = rnd.next(1, 30);
    } else if (mode == 1) {
        r = rnd.next(1, 30);
        c = 1;
    } else if (mode == 2) {
        r = rnd.next(2, 8);
        c = rnd.next(2, 8);
    } else if (mode == 3) {
        r = rnd.next(2, 5);
        c = rnd.next(20, 60);
    } else if (mode == 4) {
        r = rnd.next(20, 60);
        c = rnd.next(2, 5);
    } else {
        r = rnd.next(1, 100);
        c = rnd.next(1, 100);
        while (r * c > 10000) {
            r = rnd.next(1, 100);
            c = rnd.next(1, 100);
        }
    }

    int cells = r * c;
    int nMode = rnd.next(0, 2);
    return {r, c, randomNForMode(cells, nMode)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<TestCase> cases = {
        {1, 1, rnd.next(0, 1)},
        {1, rnd.next(2, 30), rnd.next(0, 30)},
        {2, 2, rnd.next(0, 4)},
        {3, 3, rnd.next(4, 9)},
    };

    int target = rnd.next(8, 24);
    while ((int)cases.size() < target) {
        cases.push_back(makeCase(rnd.next(0, 5)));
    }

    for (TestCase& tc : cases) {
        int cells = tc.r * tc.c;
        tc.n = max(0, min(tc.n, cells));
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const TestCase& tc : cases) {
        println(tc.r, tc.c, tc.n);
    }

    return 0;
}
