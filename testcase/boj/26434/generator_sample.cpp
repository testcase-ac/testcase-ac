#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeCase(int n, int mode) {
    vector<int> a(n);

    if (mode == 0) {
        int hi = rnd.next(0, 800);
        for (int& x : a) {
            x = rnd.next(0, hi);
        }
    } else if (mode == 1) {
        int lo = rnd.next(-800, 0);
        for (int& x : a) {
            x = rnd.next(lo, 0);
        }
    } else if (mode == 2) {
        int positive = rnd.next(1, 800);
        int negative = rnd.next(-800, -1);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? positive : negative;
        }
        if (rnd.next(2) == 1) {
            reverse(a.begin(), a.end());
        }
    } else if (mode == 3) {
        for (int& x : a) {
            int pick = rnd.next(100);
            if (pick < 55) {
                x = 0;
            } else if (pick < 78) {
                x = rnd.next(1, 20);
            } else {
                x = rnd.next(-20, -1);
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            if (i % 5 == 0) {
                a[i] = rnd.next(-800, -200);
            } else {
                a[i] = rnd.next(1, 300);
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            int block = i % 6;
            if (block < 2) {
                a[i] = rnd.next(-30, -1);
            } else if (block < 5) {
                a[i] = rnd.next(0, 30);
            } else {
                a[i] = rnd.next(-5, 5);
            }
        }
    } else {
        int lo = rnd.next(-800, 200);
        int hi = rnd.next(max(lo, -200), 800);
        for (int& x : a) {
            x = rnd.next(lo, hi);
        }
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 18);
    if (rnd.next(5) == 0) {
        t = rnd.next(20, 35);
    }
    println(t);

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        bool largeCase = caseIndex == t && rnd.next(4) == 0;
        int n;
        if (largeCase) {
            n = rnd.next(201, 450);
        } else if (rnd.next(4) == 0) {
            n = rnd.next(1, 5);
        } else {
            n = rnd.next(6, 40);
        }

        int mode = rnd.next(7);
        vector<int> a = makeCase(n, mode);

        println(n);
        println(a);
    }

    return 0;
}
