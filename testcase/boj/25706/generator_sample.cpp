#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> h;

    if (mode == 0) {
        n = rnd.next(1, 8);
        h.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            int remaining = n - i - 1;
            h[i] = rnd.next(0, remaining + 3);
        }
    } else if (mode == 1) {
        n = rnd.next(8, 30);
        h.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            int remaining = n - i - 1;
            if (rnd.next(0, 99) < 65) {
                h[i] = 0;
            } else {
                h[i] = rnd.next(1, min(200000, max(1, remaining + rnd.next(0, 6))));
            }
        }
    } else if (mode == 2) {
        n = rnd.next(10, 45);
        h.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            int remaining = n - i - 1;
            if (remaining == 0 || rnd.next(0, 2) == 0) {
                h[i] = 0;
            } else if (rnd.next(0, 1) == 0) {
                h[i] = remaining;
            } else {
                h[i] = rnd.next(1, remaining);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(12, 60);
        h.assign(n, 0);
        int block = rnd.next(2, 7);
        for (int i = 0; i < n; ++i) {
            int pos = i % block;
            if (pos == 0) {
                h[i] = 0;
            } else if (pos == block - 1) {
                h[i] = rnd.next(n - i, min(200000, n - i + 20));
            } else {
                h[i] = rnd.next(0, min(200000, block + 2));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(2, 25);
        h.assign(n, 200000);
        int zeros = rnd.next(0, n / 2);
        for (int i = 0; i < zeros; ++i) {
            h[rnd.next(0, n - 1)] = 0;
        }
        int smalls = rnd.next(0, n / 2);
        for (int i = 0; i < smalls; ++i) {
            h[rnd.next(0, n - 1)] = rnd.next(1, min(10, n));
        }
    } else {
        n = rnd.next(50, 120);
        h.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            int remaining = n - i - 1;
            int choice = rnd.next(0, 99);
            if (choice < 35) {
                h[i] = 0;
            } else if (choice < 70 && remaining > 0) {
                h[i] = rnd.next(1, remaining);
            } else {
                h[i] = rnd.next(remaining + 1, min(200000, remaining + 50));
            }
        }
    }

    println(n);
    println(h);

    return 0;
}
