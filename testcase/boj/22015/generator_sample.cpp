#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> a(3);

    if (mode == 0) {
        int x = rnd.next(1, 100);
        a = {x, x, x};
    } else if (mode == 1) {
        a[0] = rnd.next(1, 98);
        a[1] = rnd.next(a[0] + 1, 99);
        a[2] = rnd.next(a[1] + 1, 100);
    } else if (mode == 2) {
        int high = rnd.next(2, 100);
        int low = rnd.next(1, high - 1);
        a = {high, high, low};
        shuffle(a.begin(), a.end());
    } else if (mode == 3) {
        int low = rnd.next(1, 99);
        int high = rnd.next(low + 1, 100);
        a = {low, low, high};
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        vector<int> pool = {1, 2, 3, 50, 99, 100};
        for (int i = 0; i < 3; ++i) a[i] = rnd.any(pool);
    } else {
        int lo = rnd.next(1, 100);
        int hi = rnd.next(lo, 100);
        for (int i = 0; i < 3; ++i) a[i] = rnd.next(lo, hi);
    }

    println(a);
    return 0;
}
