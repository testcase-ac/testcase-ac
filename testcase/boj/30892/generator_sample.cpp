#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    int k = rnd.next(1, n);
    int t = rnd.next(1, 1000000000);
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 20);
        k = rnd.next(1, n);
        t = rnd.next(1, 1000000000);
        int lo = t == 1000000000 ? t : t + 1;
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, 1000000000));
    } else if (mode == 1) {
        n = rnd.next(3, 25);
        k = rnd.next(1, n);
        t = rnd.next(2, 50);
        long long cur = t;
        for (int i = 0; i < n; ++i) {
            int value;
            if (i < k + rnd.next(0, 3)) {
                value = rnd.next(1, (int)min<long long>(cur - 1, 1000000000));
                cur += value;
            } else {
                value = rnd.next((int)min<long long>(cur, 1000000000), 1000000000);
            }
            a.push_back(value);
        }
    } else if (mode == 2) {
        n = rnd.next(5, 30);
        k = rnd.next(1, n);
        t = rnd.next(2, 200);
        int below = rnd.next(1, t - 1);
        int atLeast = rnd.next(t, min(1000000000, t + 20));
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 3);
            if (pick == 0) a.push_back(below);
            else if (pick == 1) a.push_back(t);
            else if (pick == 2) a.push_back(atLeast);
            else a.push_back(rnd.next(1, 1000000000));
        }
    } else if (mode == 3) {
        n = rnd.next(6, 30);
        k = rnd.next(1, n);
        t = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) a.push_back(rnd.next(900000000, 1000000000));
            else a.push_back(rnd.next(1, 150));
        }
    } else if (mode == 4) {
        n = rnd.next(1, 12);
        k = rnd.next(1, n);
        t = rnd.any(vector<int>{1, 2, 999999999, 1000000000});
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(vector<int>{1, 2, 999999999, 1000000000}));
        }
    } else {
        n = rnd.next(10, 40);
        k = rnd.next(1, n);
        t = rnd.next(2, 1000);
        int hi = rnd.next(t, min(1000000000, t + 1000));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, hi));
    }

    shuffle(a.begin(), a.end());
    println(n, k, t);
    println(a);

    return 0;
}
