#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    int s;
    int e;
};

TestCase makeCase(int mode) {
    int n;
    int s;
    int e;

    if (mode == 0) {
        n = rnd.next(2, 25);
        if (rnd.next(2) == 0) {
            s = 1;
            e = n;
        } else {
            s = n;
            e = 1;
        }
    } else if (mode == 1) {
        n = rnd.next(2, 25);
        s = rnd.next(1, n - 1);
        e = s + 1;
        if (rnd.next(2) == 0) swap(s, e);
    } else if (mode == 2) {
        n = rnd.next(3, 60);
        if (rnd.next(2) == 0) {
            s = 1;
            e = rnd.next(2, n);
        } else {
            s = n;
            e = rnd.next(1, n - 1);
        }
    } else if (mode == 3) {
        n = rnd.next(6, 100);
        s = rnd.next(2, n - 1);
        if (s + 2 <= n - 1) {
            e = rnd.next(s + 2, n - 1);
        } else {
            e = rnd.next(2, s - 2);
        }
    } else if (mode == 4) {
        n = rnd.next(999999900, 1000000000);
        int side = rnd.next(4);
        if (side == 0) {
            s = 1;
            e = n;
        } else if (side == 1) {
            s = n;
            e = 1;
        } else if (side == 2) {
            s = rnd.next(1, 100);
            e = n - rnd.next(0, 100);
            if (s == e) e = n;
        } else {
            s = n - rnd.next(0, 100);
            e = rnd.next(1, 100);
            if (s == e) e = 1;
        }
    } else {
        n = rnd.next(2, 1000000000);
        s = rnd.next(1, n);
        int offset = rnd.next(1, n - 1);
        e = s + offset;
        if (e > n) e -= n;
    }

    return {n, s, e};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(12, 35);
    vector<TestCase> cases;
    cases.reserve(t);

    for (int mode = 0; mode < 6 && static_cast<int>(cases.size()) < t; ++mode) {
        cases.push_back(makeCase(mode));
    }
    while (static_cast<int>(cases.size()) < t) {
        cases.push_back(makeCase(rnd.next(0, 5)));
    }

    shuffle(cases.begin(), cases.end());

    println(static_cast<int>(cases.size()));
    for (const TestCase& tc : cases) {
        println(tc.n, tc.s, tc.e);
    }

    return 0;
}
