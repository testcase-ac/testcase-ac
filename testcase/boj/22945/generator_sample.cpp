#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int boundedAbility(int value) {
    return min(10000, max(1, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 40);
    if (rnd.next(0, 9) == 0) n = rnd.next(41, 90);

    vector<int> x(n);

    if (mode == 0) {
        int lo = rnd.next(1, 9500);
        int hi = rnd.next(lo, min(10000, lo + rnd.next(0, 500)));
        for (int& value : x) value = rnd.next(lo, hi);
    } else if (mode == 1) {
        int start = rnd.next(1, 10000);
        int step = rnd.next(0, max(1, (10000 - start) / max(1, n - 1)));
        for (int i = 0; i < n; ++i) x[i] = boundedAbility(start + i * step);
    } else if (mode == 2) {
        int start = rnd.next(1, 10000);
        int step = rnd.next(0, max(1, (start - 1) / max(1, n - 1)));
        for (int i = 0; i < n; ++i) x[i] = boundedAbility(start - i * step);
    } else if (mode == 3) {
        int low = rnd.next(1, 50);
        int high = rnd.next(5000, 10000);
        for (int i = 0; i < n; ++i) x[i] = (i % 2 == 0 ? high : low + rnd.next(0, 200));
    } else if (mode == 4) {
        int base = rnd.next(1, 10000);
        fill(x.begin(), x.end(), base);
        int changes = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < changes; ++i) x[rnd.next(0, n - 1)] = rnd.next(1, 10000);
    } else if (mode == 5) {
        int edge = rnd.next(5000, 10000);
        int innerLow = rnd.next(1, 200);
        for (int i = 0; i < n; ++i) x[i] = rnd.next(innerLow, min(10000, innerLow + 500));
        x[0] = edge;
        x[n - 1] = rnd.next(edge, 10000);
    } else {
        int peakPos = rnd.next(0, n - 1);
        int peak = rnd.next(5000, 10000);
        for (int i = 0; i < n; ++i) {
            int drop = abs(i - peakPos) * rnd.next(1, 200);
            x[i] = boundedAbility(peak - drop + rnd.next(-20, 20));
        }
    }

    if (rnd.next(0, 3) == 0) shuffle(x.begin(), x.end());

    println(n);
    println(x);
    return 0;
}
