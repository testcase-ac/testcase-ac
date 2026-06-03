#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k = rnd.next(1, 200);
    long long w = 1;
    long long m = 1;

    if (mode == 0) {
        w = rnd.next(1, k);
        m = rnd.next(1, 1000000000);
    } else if (mode == 1) {
        w = rnd.next(k + 1, min(1000000000, k + 50));
        m = rnd.next(1, 60);
    } else if (mode == 2) {
        m = rnd.next(1, 1000000);
        long long hits = rnd.next(1, 1000);
        w = k + hits * m;
        if (w > 1000000000) w = k + ((1000000000LL - k) / m) * m;
        if (w <= k) w = k + m;
    } else if (mode == 3) {
        m = rnd.next(2, 1000000);
        long long hits = rnd.next(1, 1000);
        w = k + hits * m - rnd.next(1, (int)min(m - 1, 1000LL));
        if (w <= k) w = k + 1;
        if (w > 1000000000) w = 1000000000;
    } else if (mode == 4) {
        w = rnd.next(max(201, 1000000000 - 1000000), 1000000000);
        m = rnd.next(1, 1000000);
    } else {
        w = rnd.next(1, 1000000000);
        m = rnd.next(max(1, (int)min(1000000000LL, w)), 1000000000);
    }

    println(k, w, m);
    return 0;
}
