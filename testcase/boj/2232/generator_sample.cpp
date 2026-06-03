#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampPower(int x) {
    return min(10000, max(1, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 35);
    vector<int> p(n);

    if (mode == 0) {
        int value = rnd.next(1, 10000);
        int delta = rnd.next(0, 60);
        bool increasing = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            int offset = i * delta + rnd.next(0, 3);
            p[i] = increasing ? clampPower(value + offset) : clampPower(value - offset);
        }
    } else if (mode == 1) {
        int value = rnd.next(1, 10000);
        for (int i = 0; i < n; ++i) p[i] = value;
    } else if (mode == 2) {
        int low = rnd.next(1, 100);
        int high = rnd.next(9000, 10000);
        for (int i = 0; i < n; ++i) {
            int jitter = rnd.next(0, 20);
            p[i] = (i % 2 == 0) ? clampPower(high - jitter) : clampPower(low + jitter);
        }
    } else if (mode == 3) {
        int value = rnd.next(1, 10000);
        for (int i = 0; i < n; ++i) {
            value = clampPower(value + rnd.next(-350, 350));
            p[i] = value;
        }
    } else if (mode == 4) {
        int base = rnd.next(100, 9900);
        int block = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            int wave = ((i / block) % 2 == 0) ? rnd.next(0, 700) : -rnd.next(0, 700);
            p[i] = clampPower(base + wave);
        }
    } else {
        for (int i = 0; i < n; ++i) p[i] = rnd.next(1, 10000);
        if (n >= 3 && rnd.next(0, 1)) {
            int pos = rnd.next(1, n - 2);
            p[pos] = 10000;
            p[pos - 1] = rnd.next(1, 9999);
            p[pos + 1] = rnd.next(1, 9999);
        }
    }

    println(n);
    for (int x : p) println(x);

    return 0;
}
