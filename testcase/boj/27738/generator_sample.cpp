#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 1000000000000LL;
    const int maxV = 1000000;

    int mode = rnd.next(0, 5);
    long long n;
    vector<int> values(6);

    if (mode == 0) {
        n = rnd.next(1, 10);
        for (int i = 0; i < 6; ++i) values[i] = rnd.next(1, 10);
    } else if (mode == 1) {
        n = rnd.next(1LL, 2000LL);
        int base = rnd.next(1, 200);
        for (int i = 0; i < 6; ++i) values[i] = base + rnd.next(0, 3);
    } else if (mode == 2) {
        n = rnd.next(1LL, maxN);
        int p = 1 << rnd.next(0, 19);
        for (int i = 0; i < 6; ++i) {
            int shift = rnd.next(0, 19);
            values[i] = min(maxV, p + (1 << shift) - 1);
        }
    } else if (mode == 3) {
        n = maxN - rnd.next(0LL, 1000000LL);
        int start = rnd.next(1, maxV);
        for (int i = 0; i < 6; ++i) values[i] = rnd.next(start, maxV);
    } else if (mode == 4) {
        int f = rnd.next(1, maxV);
        n = rnd.next(1LL, maxN / f) * f + rnd.next(0, min(f - 1, 1000));
        for (int i = 0; i < 6; ++i) values[i] = rnd.next(1, f);
        values[5] = f;
    } else {
        n = rnd.next(1LL, 5000000LL);
        for (int i = 0; i < 6; ++i) values[i] = rnd.next(1, maxV);
    }

    sort(values.begin(), values.end());
    println(n);
    println(values);

    return 0;
}
