#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 25);
    int maxValue = rnd.next(0, 1000);
    vector<int> a(n);

    if (mode == 0) {
        int value = rnd.next(0, 1000);
        fill(a.begin(), a.end(), value);
    } else if (mode == 1) {
        int cur = rnd.next(0, maxValue);
        for (int i = 0; i < n; ++i) {
            cur = rnd.next(cur, maxValue);
            a[i] = cur;
        }
    } else if (mode == 2) {
        int cur = rnd.next(0, maxValue);
        for (int i = 0; i < n; ++i) {
            cur = rnd.next(0, cur);
            a[i] = cur;
        }
    } else if (mode == 3) {
        int peak = rnd.next(0, n - 1);
        int height = rnd.next(0, 1000);
        for (int i = 0; i <= peak; ++i) {
            a[i] = (peak == 0 ? height : rnd.next(0, height));
        }
        sort(a.begin(), a.begin() + peak + 1);
        for (int i = peak + 1; i < n; ++i) {
            a[i] = rnd.next(0, a[i - 1]);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                a[i] = rnd.next(0, 5);
            } else {
                a[i] = rnd.next(995, 1000);
            }
        }
    } else if (mode == 5) {
        int blockCount = rnd.next(1, min(n, 8));
        int pos = 0;
        for (int block = 0; block < blockCount; ++block) {
            int remaining = n - pos;
            int length = (block == blockCount - 1) ? remaining : rnd.next(1, remaining - (blockCount - block - 1));
            int value = rnd.next(0, 1000);
            for (int i = 0; i < length; ++i) {
                a[pos++] = value;
            }
        }
    } else if (mode == 6) {
        n = rnd.next(1, 120);
        a.assign(n, 0);
        int intervals = rnd.next(0, 40);
        for (int k = 0; k < intervals; ++k) {
            int l = rnd.next(0, n - 1);
            int r = rnd.next(l, n - 1);
            for (int i = l; i <= r; ++i) {
                if (a[i] < 1000) {
                    ++a[i];
                }
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 4);
            if (bucket == 0) {
                a[i] = 0;
            } else if (bucket == 1) {
                a[i] = rnd.next(1, 10);
            } else if (bucket == 2) {
                a[i] = rnd.next(990, 1000);
            } else {
                a[i] = rnd.next(0, 1000);
            }
        }
    }

    println(n);
    println(a);
    return 0;
}
