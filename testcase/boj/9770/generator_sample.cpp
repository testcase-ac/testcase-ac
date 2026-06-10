#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int boundedMultiple(int base, int maxMultiplier) {
    return base * rnd.next(1, maxMultiplier);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(2, 6);
        int value = rnd.next(1, 200);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, 2) == 0 ? value : rnd.next(1, 300));
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 12);
        int base = rnd.next(2, 500);
        int maxMultiplier = 999999 / base;
        for (int i = 0; i < n; ++i) {
            a.push_back(boundedMultiple(base, min(maxMultiplier, 40)));
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 15);
        int lo = rnd.next(1, 40);
        int hi = rnd.next(lo, min(999999, lo + rnd.next(20, 200)));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 10);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(999000, 999999));
        }
    } else if (mode == 4) {
        int n = rnd.next(20, 100);
        int step = rnd.next(1, 11);
        int start = rnd.next(1, step);
        for (int i = 0; i < n; ++i) {
            a.push_back(start + i * step);
        }
    } else {
        int n = rnd.next(2, 20);
        vector<int> special = {1, 2, 3, 4, 5, 6, 12, 30, 60, 90, 100, 210};
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                a.push_back(rnd.any(special));
            } else {
                a.push_back(rnd.next(1, 500));
            }
        }
    }

    shuffle(a.begin(), a.end());
    println(a);
    return 0;
}
