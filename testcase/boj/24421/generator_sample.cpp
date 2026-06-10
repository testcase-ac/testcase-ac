#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, mode == 5 ? 100 : 30);
    vector<int> a;
    a.reserve(n);

    if (mode == 0) {
        int value = rnd.next(1, 9);
        a.assign(n, value);
    } else if (mode == 1) {
        int x = rnd.next(1, 9);
        int y = rnd.next(1, 999 / x);
        int z = x * y;
        while ((int)a.size() < n) {
            int pick = rnd.next(0, 5);
            if (pick <= 1) {
                a.push_back(x);
            } else if (pick <= 3) {
                a.push_back(y);
            } else {
                a.push_back(z);
            }
        }
    } else if (mode == 2) {
        int cur = rnd.next(1, 3);
        while ((int)a.size() < n) {
            a.push_back(cur);
            int mul = rnd.next(2, 4);
            if (cur * mul <= 999 && rnd.next(0, 2) != 0) {
                cur *= mul;
            } else {
                cur = rnd.next(1, 12);
            }
        }
    } else if (mode == 3) {
        int base = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int mul = rnd.next(1, 999 / base);
            a.push_back(base * mul);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int lo = rnd.next(1, 40);
            int hi = rnd.next(lo, min(999, lo + rnd.next(0, 80)));
            a.push_back(rnd.next(lo, hi));
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 999));
        }
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);

    return 0;
}
