#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 12);
    } else {
        n = rnd.next(8, 35);
    }

    int q = rnd.next(n == 1 ? 1 : n, min(80, max(n, 2 * n + 20)));
    vector<int> heights(n + 1);

    if (mode == 0) {
        int base = rnd.next(1, 1000000);
        for (int i = 1; i <= n; ++i) {
            heights[i] = rnd.next(max(1, base - 3), min(1000000, base + 3));
        }
    } else if (mode == 1) {
        int cur = rnd.next(1, 20);
        for (int i = 1; i <= n; ++i) {
            cur += rnd.next(0, 7);
            heights[i] = min(cur, 1000000);
        }
        if (rnd.next(0, 1)) {
            reverse(heights.begin() + 1, heights.end());
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            heights[i] = (i % 2 == 0) ? rnd.next(999900, 1000000) : rnd.next(1, 100);
        }
    } else if (mode == 3) {
        vector<int> values;
        int count = rnd.next(2, 5);
        for (int i = 0; i < count; ++i) {
            values.push_back(rnd.next(1, 1000000));
        }
        for (int i = 1; i <= n; ++i) {
            heights[i] = rnd.any(values);
        }
    } else {
        int lo = rnd.next(1, 999000);
        int hi = rnd.next(lo, min(1000000, lo + rnd.next(0, 1000)));
        for (int i = 1; i <= n; ++i) {
            heights[i] = rnd.next(lo, hi);
        }
    }

    println(n, q);
    for (int i = 1; i <= n; ++i) {
        println(heights[i]);
    }

    for (int i = 0; i < q; ++i) {
        int type = rnd.next(0, 4);
        int a = 1;
        int b = n;

        if (type == 0) {
            a = b = rnd.next(1, n);
        } else if (type == 1) {
            a = 1;
            b = n;
        } else if (type == 2 && n > 1) {
            int len = rnd.next(2, min(n, 5));
            a = rnd.next(1, n - len + 1);
            b = a + len - 1;
        } else {
            a = rnd.next(1, n);
            b = rnd.next(a, n);
        }

        println(a, b);
    }

    return 0;
}
