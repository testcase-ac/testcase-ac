#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 20 : 14);
    int m = rnd.next(2, 36);

    vector<int> line(n);
    iota(line.begin(), line.end(), 1);

    if (mode == 1) {
        reverse(line.begin(), line.end());
    } else if (mode == 2) {
        shuffle(line.begin(), line.end());
    } else if (mode == 3) {
        int block = rnd.next(2, min(n, 5));
        for (int l = 0; l < n; l += block) {
            int r = min(n, l + block);
            shuffle(line.begin() + l, line.begin() + r);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; i += 2) {
            if (i + 1 < n) {
                swap(line[i], line[i + 1]);
            }
        }
    } else if (mode == 5) {
        int shifts = rnd.next(1, n - 1);
        rotate(line.begin(), line.begin() + shifts, line.end());
        if (rnd.next(0, 1)) {
            reverse(line.begin(), line.end());
        }
    }

    println(n, m);
    println(line);

    for (int step = 0; step < m; ++step) {
        bool mustQuery = (step == m - 1);
        bool doSwap = !mustQuery && rnd.next(0, 99) < 45;

        if (doSwap) {
            int x = rnd.next(1, n);
            int y = rnd.next(1, n - 1);
            if (y >= x) {
                ++y;
            }
            if (rnd.next(0, 99) < 35 && x < n) {
                y = x + 1;
            }
            println(1, x, y);

            swap(line[x - 1], line[y - 1]);
        } else {
            int a, b;
            int qmode = rnd.next(0, 5);
            if (qmode == 0) {
                a = 1;
                b = n;
            } else if (qmode == 1) {
                a = b = rnd.next(1, n);
            } else if (qmode == 2) {
                a = rnd.next(1, n - 1);
                b = a + 1;
            } else if (qmode == 3) {
                int l = rnd.next(1, n);
                int r = rnd.next(l, min(n, l + rnd.next(0, 4)));
                a = n;
                b = 1;
                for (int i = l; i <= r; ++i) {
                    a = min(a, line[i - 1]);
                    b = max(b, line[i - 1]);
                }
            } else {
                a = rnd.next(1, n);
                b = rnd.next(a, min(n, a + rnd.next(0, 7)));
            }
            println(2, a, b);
        }
    }

    return 0;
}
