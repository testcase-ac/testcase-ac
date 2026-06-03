#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 5) {
        n = rnd.next(50, 100);
    } else {
        n = rnd.next(2, 20);
    }

    vector<int> a(n), b(n);
    iota(a.begin(), a.end(), 1);
    shuffle(a.begin(), a.end());
    b = a;

    if (mode == 0) {
        // Identity arrangement: no cow moves.
    } else if (mode == 1) {
        rotate(b.begin(), b.begin() + rnd.next(1, n - 1), b.end());
    } else if (mode == 2) {
        reverse(b.begin(), b.end());
    } else {
        vector<int> pos(n);
        iota(pos.begin(), pos.end(), 0);
        shuffle(pos.begin(), pos.end());

        int at = 0;
        while (at < n) {
            int remaining = n - at;
            int len;
            if (mode == 3) {
                len = min(remaining, rnd.next(2, 4));
            } else if (mode == 4) {
                len = remaining == 1 ? 1 : rnd.next(2, remaining);
            } else {
                len = remaining == 1 ? 1 : rnd.next(1, min(remaining, 10));
            }

            if (len > 1) {
                int first = b[pos[at]];
                for (int i = 0; i + 1 < len; ++i) {
                    b[pos[at + i]] = b[pos[at + i + 1]];
                }
                b[pos[at + len - 1]] = first;
            }
            at += len;
        }
    }

    println(n);
    for (int value : a) {
        println(value);
    }
    for (int value : b) {
        println(value);
    }

    return 0;
}
