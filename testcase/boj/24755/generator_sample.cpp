#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int oddInRange(int lo, int hi) {
    int x = rnd.next(lo / 2, (hi - 1) / 2);
    return 2 * x + 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    vector<int> p;

    if (mode == 0) {
        n = oddInRange(3, 15);
        int value = oddInRange(1, 31);
        p.assign(n, value);
    } else if (mode == 1) {
        n = oddInRange(3, 19);
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            p[i] = oddInRange(1, 41);
        }
    } else if (mode == 2) {
        n = oddInRange(3, 21);
        p.resize(n);
        p[0] = oddInRange(501, 999);
        for (int i = 1; i < n; ++i) {
            p[i] = oddInRange(1, 21);
        }
    } else if (mode == 3) {
        n = oddInRange(5, 31);
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            p[i] = oddInRange(899, 999);
        }
    } else if (mode == 4) {
        n = oddInRange(5, 25);
        p.resize(n);
        int lowMax = oddInRange(5, 99);
        int highMin = oddInRange(401, 899);
        for (int i = 0; i < n; ++i) {
            p[i] = (rnd.next(2) == 0) ? oddInRange(1, lowMax) : oddInRange(highMin, 999);
        }
    } else {
        n = oddInRange(3, 35);
        p.resize(n);
        int start = oddInRange(2 * n + 1, 999);
        for (int i = 0; i < n; ++i) {
            p[i] = max(1, start - 2 * i);
        }
    }

    shuffle(p.begin(), p.end());

    println(n);
    println(p);

    return 0;
}
