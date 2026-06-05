#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int A_MAX = 2000000;
    int mode = rnd.next(0, 5);
    vector<int> a;

    if (mode == 0) {
        int n = rnd.next(1, 25);
        int zeroCount = rnd.next(1, n);
        a.assign(zeroCount, 0);
        while ((int)a.size() < n) {
            a.push_back(rnd.next(0, 12));
        }
    } else if (mode == 1) {
        int hi = rnd.next(1, 18);
        for (int i = 0; i <= hi; ++i) {
            a.push_back(i);
            if (rnd.next(0, 3) == 0) {
                a.push_back(i);
            }
        }
    } else if (mode == 2) {
        int n = rnd.next(1, 40);
        int value = rnd.next(0, 20);
        a.assign(n, value);
        if (n > 1 && rnd.next(0, 1)) {
            a[rnd.next(0, n - 1)] = rnd.next(0, 20);
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 30);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 4);
            if (pick == 0) {
                a.push_back(A_MAX);
            } else if (pick == 1) {
                a.push_back(A_MAX - rnd.next(0, 12));
            } else {
                a.push_back(rnd.next(0, 8));
            }
        }
    } else if (mode == 4) {
        int n = rnd.next(5, 50);
        vector<int> pool = {0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 16, 18, 20, 24, 25, 30, 36};
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else {
        int n = rnd.next(1, 60);
        int lo = rnd.next(0, 15);
        int hi = rnd.next(lo, min(A_MAX, lo + rnd.next(0, 35)));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    }

    shuffle(a.begin(), a.end());
    println((int)a.size());
    println(a);

    return 0;
}
