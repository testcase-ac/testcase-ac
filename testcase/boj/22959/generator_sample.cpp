#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long chooseValue(int mode, int index, int n) {
    if (mode == 0) return rnd.next(1, 12);
    if (mode == 1) return index + 1;
    if (mode == 2) return n - index;
    if (mode == 3) return (index % 2 == 0) ? rnd.next(1, 3) : rnd.next(8, 15);
    if (mode == 4) return rnd.any(vector<long long>{1, 2, 3, 1000000000LL});
    return rnd.next(1, 1000000000);
}

long long chooseThreshold(long long value) {
    int mode = rnd.next(0, 4);
    if (mode == 0) return 1;
    if (mode == 1) return value;
    if (mode == 2) return rnd.next(1LL, min(value, 10LL));
    if (mode == 3) return rnd.next(max(1LL, value - 5), value);
    return rnd.next(1LL, value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 15);
    int m = rnd.next(1, 40);
    int mode = rnd.next(0, 5);

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) a[i] = chooseValue(mode, i, n);

    println(n);
    println(a);
    println(m);

    bool wroteQuery = false;
    for (int q = 0; q < m; ++q) {
        bool forceQuery = !wroteQuery && q == m - 1;
        bool doUpdate = !forceQuery && rnd.next(0, 99) < 45;
        int i = rnd.next(1, n);

        if (doUpdate) {
            long long value;
            int updateMode = rnd.next(0, 4);
            if (updateMode == 0) value = rnd.next(1, 15);
            else if (updateMode == 1) value = a[i - 1];
            else if (updateMode == 2) value = rnd.any(vector<long long>{1, 1000000000LL});
            else if (updateMode == 3) value = rnd.next(max(1LL, a[i - 1] - 3), min(1000000000LL, a[i - 1] + 3));
            else value = rnd.next(1LL, 1000000000LL);

            a[i - 1] = value;
            println(1, i, value);
        } else {
            long long threshold = chooseThreshold(a[i - 1]);
            wroteQuery = true;
            println(2, i, threshold);
        }
    }

    return 0;
}
