#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 35);
    vector<int> s(n);

    if (mode == 0) {
        int value = rnd.next(-5, 5);
        fill(s.begin(), s.end(), value);
    } else if (mode == 1) {
        vector<int> pool = {-1000000, -1, 0, 1, 1000000};
        for (int i = 0; i < n; ++i) s[i] = rnd.any(pool);
    } else if (mode == 2) {
        int alphabet = rnd.next(1, min(n, 8));
        int base = rnd.next(-20, 20);
        for (int i = 0; i < n; ++i) s[i] = base + rnd.next(0, alphabet - 1);
    } else if (mode == 3) {
        int start = rnd.next(-100, 100);
        for (int i = 0; i < n; ++i) s[i] = start + i;
        shuffle(s.begin(), s.end());
    } else if (mode == 4) {
        int first = rnd.next(-1000, 1000);
        int second = rnd.next(-1000, 1000);
        for (int i = 0; i < n; ++i) s[i] = (i % 2 == 0 ? first : second);
        if (rnd.next(0, 1)) shuffle(s.begin(), s.end());
    } else {
        int lo = rnd.next(-1000000, 999900);
        int hi = rnd.next(lo, min(1000000, lo + rnd.next(0, 100)));
        for (int i = 0; i < n; ++i) s[i] = rnd.next(lo, hi);
    }

    int mMode = rnd.next(0, 4);
    int m;
    if (mMode == 0) {
        m = rnd.next(1, n);
    } else if (mMode == 1) {
        m = n + rnd.next(1, 20);
    } else if (mMode == 2) {
        m = rnd.next(1, 1000);
    } else if (mMode == 3) {
        m = rnd.next(1000000, 1000000000);
    } else {
        m = 1000000000;
    }

    println(n);
    println(s);
    println(m);
    return 0;
}
