#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 4) {
        n = rnd.next(20, 80);
    } else if (mode == 5) {
        n = rnd.next(1, 12);
    } else {
        n = rnd.next(1, 15);
    }

    vector<int> xs(n);
    if (mode == 0) {
        fill(xs.begin(), xs.end(), 1);
    } else if (mode == 1) {
        int hi = rnd.next(2, 25);
        for (int& x : xs) x = rnd.next(1, hi);
    } else if (mode == 2) {
        int cur = rnd.next(1, 8);
        for (int& x : xs) {
            cur = min(1000000, cur + rnd.next(0, 7));
            x = cur;
        }
        if (rnd.next(0, 1)) reverse(xs.begin(), xs.end());
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                xs[i] = rnd.next(1, 3);
            } else {
                xs[i] = rnd.next(999990, 1000000);
            }
        }
    } else if (mode == 4) {
        for (int& x : xs) x = rnd.next(1, 1000);
        int specialCount = rnd.next(1, min(n, 6));
        for (int i = 0; i < specialCount; ++i) {
            xs[rnd.next(0, n - 1)] = rnd.next(999900, 1000000);
        }
    } else {
        vector<int> pool = {1, 2, 3, 999998, 999999, 1000000};
        for (int& x : xs) x = rnd.any(pool);
    }

    println(n);
    println(xs);
    return 0;
}
