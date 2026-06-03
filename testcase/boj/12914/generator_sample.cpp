#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 40);
    int d = rnd.next(1, 1000000);
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 12);
        d = rnd.any(vector<int>{1, 2, rnd.next(3, 20), 999999, 1000000});
        int value = rnd.next(1, 1000000);
        a.assign(n, value);
    } else if (mode == 1) {
        n = rnd.next(4, 40);
        d = rnd.next(1, 30);
        int base = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(0, min(2 * d, 1000000 - 1));
            a.push_back(min(1000000, base + delta));
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        n = rnd.next(8, 60);
        d = rnd.next(1, 1000);
        int start = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            int step = rnd.next(0, min(d + 5, 1000000 - 1));
            a.push_back(min(1000000, start + step));
        }
    } else if (mode == 3) {
        n = rnd.next(6, 50);
        d = rnd.next(900000, 1000000);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(vector<int>{1, rnd.next(1, 20), rnd.next(999980, 1000000), 1000000}));
        }
    } else if (mode == 4) {
        n = rnd.next(20, 80);
        d = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                a.push_back(rnd.next(1, 30));
            } else if (i % 3 == 1) {
                a.push_back(rnd.next(999971, 1000000));
            } else {
                a.push_back(rnd.next(1, 1000000));
            }
        }
    } else if (mode == 5) {
        n = rnd.next(1, 1000);
        d = rnd.any(vector<int>{1, 2, 999999, 1000000});
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 1000000));
        }
    } else if (mode == 6) {
        n = 1000;
        d = rnd.next(1, 1000000);
        int lo = rnd.next(1, 1000);
        int hi = rnd.next(999001, 1000000);
        for (int i = 0; i < n; ++i) {
            a.push_back(i % 2 == 0 ? rnd.next(lo, min(1000000, lo + 50)) : rnd.next(max(1, hi - 50), hi));
        }
    } else {
        n = rnd.next(1, 70);
        d = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 1000000));
        }
    }

    println(n, d);
    println(a);

    return 0;
}
