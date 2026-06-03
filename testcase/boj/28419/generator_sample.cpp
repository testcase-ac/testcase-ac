#include "testlib.h"

#include <vector>
using namespace std;

int clampValue(int x) {
    if (x < -100000) return -100000;
    if (x > 100000) return 100000;
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(3, 9);
        a.assign(n, 0);
        int oddSum = 0;
        int evenSum = 0;
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(-20, 20);
            if (i % 2 == 0) {
                oddSum += a[i];
            } else {
                evenSum += a[i];
            }
        }
        vector<int> candidates;
        for (int i = 0; i < n; ++i) {
            if ((i % 2 == 0 && oddSum > evenSum) || (i % 2 == 1 && evenSum > oddSum)) {
                candidates.push_back(i);
            }
        }
        if (!candidates.empty()) {
            int idx = rnd.any(candidates);
            a[idx] = clampValue(a[idx] - abs(oddSum - evenSum));
        }
    } else if (mode == 1) {
        n = 3;
        a = {rnd.next(1, 30), rnd.next(-10, 10), rnd.next(1, 30)};
    } else if (mode == 2) {
        n = 3;
        int edge = rnd.any(vector<int>{-100000, -1000, -10, 0, 10, 1000, 100000});
        a = {edge, rnd.next(-100000, 100000), -edge};
    } else {
        if (mode == 3) {
            n = rnd.next(4, 12);
        } else if (mode == 4) {
            n = rnd.next(13, 40);
        } else if (mode == 5) {
            n = rnd.next(99990, 100000);
        } else if (mode == 6) {
            n = rnd.next(3, 30) * 2 + 1;
        } else {
            n = rnd.next(2, 30) * 2;
        }

        int pattern = rnd.next(0, 4);
        int lo = rnd.next(-100000, 0);
        int hi = rnd.next(0, 100000);
        int base = rnd.next(-50, 50);
        int step = rnd.next(-7, 7);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            if (pattern == 0) {
                a[i] = rnd.next(lo, hi);
            } else if (pattern == 1) {
                a[i] = (i % 2 == 0 ? hi : lo);
            } else if (pattern == 2) {
                a[i] = clampValue(base + step * i + rnd.next(-3, 3));
            } else if (pattern == 3) {
                a[i] = rnd.any(vector<int>{-100000, -1, 0, 1, 100000});
            } else {
                a[i] = (i % 3 == 0 ? rnd.next(-100000, -99950) : rnd.next(99950, 100000));
            }
        }
    }

    println(n);
    println(a);
    return 0;
}
