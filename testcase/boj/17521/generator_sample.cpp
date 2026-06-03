#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 15);
    int w = rnd.next(1, 100000);
    vector<int> s(n);

    if (mode == 0) {
        int cur = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            s[i] = cur;
            cur = rnd.next(cur, 50);
        }
    } else if (mode == 1) {
        int cur = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            s[i] = cur;
            cur = rnd.next(1, cur);
        }
    } else if (mode == 2) {
        int low = rnd.next(1, 10);
        int high = rnd.next(40, 50);
        for (int i = 0; i < n; ++i) {
            s[i] = (i % 2 == 0 ? low : high);
            if (rnd.next(0, 3) == 0) {
                s[i] = rnd.next(1, 50);
            }
        }
    } else if (mode == 3) {
        int price = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            if (i > 0 && rnd.next(0, 2) == 0) {
                price = rnd.next(1, 50);
            }
            s[i] = price;
        }
    } else if (mode == 4) {
        int a = rnd.next(20, 50);
        int b = rnd.next(1, a);
        int c = rnd.next(b, 50);
        for (int i = 0; i < n; ++i) {
            int part = (3 * i) / max(1, n);
            s[i] = (part == 0 ? a : (part == 1 ? b : c));
            if (rnd.next(0, 4) == 0) {
                s[i] = rnd.next(1, 50);
            }
        }
    } else if (mode == 5) {
        n = 15;
        w = rnd.next(90000, 100000);
        s.resize(n);
        for (int i = 0; i < n; ++i) {
            s[i] = (i % 2 == 0 ? rnd.next(1, 3) : rnd.next(48, 50));
        }
    } else {
        int lo = rnd.next(1, 50);
        int hi = rnd.next(lo, 50);
        for (int i = 0; i < n; ++i) {
            s[i] = rnd.next(lo, hi);
        }
    }

    println(n, w);
    for (int price : s) {
        println(price);
    }

    return 0;
}
