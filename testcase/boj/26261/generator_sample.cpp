#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int x;
    int k;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(3, 12);
        x = rnd.next(2, n - 1);
        k = rnd.next(1, x - 1);
        a.assign(n, 1);
    } else if (mode == 1) {
        n = rnd.next(3, 14);
        x = rnd.next(2, n - 1);
        k = rnd.next(1, x - 1);
        a.assign(n, 0);
    } else if (mode == 2) {
        n = rnd.next(6, 24);
        x = rnd.next(2, min(n - 1, 8));
        k = rnd.next(1, x - 1);
        int onePercent = rnd.next(10, 90);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 100) <= onePercent);
        }
    } else if (mode == 3) {
        n = rnd.next(8, 28);
        x = rnd.next(3, min(n - 1, 10));
        k = rnd.next(1, x - 1);
        a.assign(n, 1);
        int runs = rnd.next(1, 4);
        for (int run = 0; run < runs; ++run) {
            int len = rnd.next(k, min(n, k + 4));
            int start = rnd.next(0, n - len);
            fill(a.begin() + start, a.begin() + start + len, 0);
        }
    } else if (mode == 4) {
        k = rnd.next(1, 5);
        x = k + 1;
        n = rnd.next(x + 1, x + 12);
        for (int i = 0; i < n; ++i) {
            int pattern = (i + rnd.next(0, 2)) % (k + 2);
            a.push_back(pattern == 0 ? 1 : 0);
        }
    } else {
        n = rnd.next(12, 30);
        x = rnd.next(max(2, n / 3), n - 1);
        k = rnd.next(1, x - 1);
        a.assign(n, 0);
        int notes = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < notes; ++i) {
            a[rnd.next(0, n - 1)] = 1;
        }
    }

    println(n, x, k);
    println(a);

    return 0;
}
