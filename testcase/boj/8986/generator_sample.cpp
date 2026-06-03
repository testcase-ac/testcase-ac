#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> x;

    if (mode == 0) {
        n = 1;
        x = {0};
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int d = rnd.next(1, 20);
        x.resize(n);
        for (int i = 0; i < n; ++i) x[i] = i * d;
    } else if (mode == 2) {
        n = rnd.next(3, 18);
        int d = rnd.next(2, 50);
        x.resize(n);
        x[0] = 0;
        for (int i = 1; i < n; ++i) {
            int jitter = rnd.next(-d / 2, d / 2);
            x[i] = max(x[i - 1] + 1, i * d + jitter);
        }
    } else if (mode == 3) {
        n = rnd.next(4, 20);
        x.resize(n);
        x[0] = 0;
        int cur = 0;
        for (int i = 1; i < n; ++i) {
            int gap = rnd.next(1, 3);
            if (rnd.next(0, 4) == 0) gap = rnd.next(20, 200);
            cur += gap;
            x[i] = cur;
        }
    } else if (mode == 4) {
        n = rnd.next(5, 15);
        x.resize(n);
        x[0] = 0;
        int cur = 0;
        for (int i = 1; i < n; ++i) {
            cur += rnd.next(1, 1000);
            x[i] = cur;
        }
        x[n - 1] = 1000000000;
    } else {
        n = rnd.next(8, 30);
        x.resize(n);
        x[0] = 0;
        int cur = 0;
        for (int i = 1; i < n; ++i) {
            int remaining = n - 1 - i;
            int hi = 1000000000 - remaining;
            int gap = rnd.next(1, max(1, min(10000000, hi - cur)));
            cur += gap;
            x[i] = cur;
        }
    }

    println(n);
    println(x);

    return 0;
}
