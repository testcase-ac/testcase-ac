#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeCase(int n, int mode) {
    vector<int> a(n);
    int base = rnd.next(1, 40);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) a[i] = base + i;
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) a[i] = base + n - 1 - i;
    } else if (mode == 2) {
        int value = rnd.next(1, 1000000);
        fill(a.begin(), a.end(), value);
    } else if (mode == 3) {
        int low = rnd.next(1, 20);
        int high = rnd.next(21, 60);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? high - i / 2 : low + i / 2);
    } else if (mode == 4) {
        int width = rnd.next(2, 7);
        for (int i = 0; i < n; ++i) a[i] = base + rnd.next(width);
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            int block = i / rnd.next(2, 5);
            a[i] = base + block + rnd.next(0, 1);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int band = rnd.next(0, 3);
            if (band == 0) a[i] = rnd.next(1, 5);
            else if (band == 1) a[i] = rnd.next(999995, 1000000);
            else a[i] = rnd.next(1, 80);
        }
    }

    if (mode != 0 && mode != 1 && rnd.next(0, 4) == 0) {
        shuffle(a.begin(), a.end());
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 6);
        int n;
        if (tc == 0 && rnd.next(0, 5) == 0) {
            n = 1;
        } else if (rnd.next(0, 3) == 0) {
            n = rnd.next(2, 8);
        } else {
            n = rnd.next(9, 35);
        }

        vector<int> a = makeCase(n, mode);
        println(n);
        println(a);
    }

    return 0;
}
