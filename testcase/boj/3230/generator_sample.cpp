#include "testlib.h"
#include <vector>
using namespace std;

int pickPosition(int i, int mode) {
    if (mode == 0) return 1;
    if (mode == 1) return i;
    if (mode == 2) return rnd.next(1, min(i, 3));
    if (mode == 3) return rnd.next(max(1, i - 2), i);
    if (mode == 4) return rnd.next(1, i);

    if (i == 1) return 1;
    if (rnd.next(0, 99) < 70) return rnd.any(vector<int>{1, i, rnd.next(1, i)});
    return rnd.next(1, i);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) {
        n = rnd.next(3, 7);
    } else if (sizeMode == 1) {
        n = rnd.next(8, 20);
    } else if (sizeMode == 2) {
        n = rnd.next(21, 60);
    } else {
        n = rnd.next(61, 100);
    }

    int mMode = rnd.next(0, 3);
    int m;
    if (mMode == 0) {
        m = 3;
    } else if (mMode == 1) {
        m = n;
    } else {
        m = rnd.next(3, n);
    }

    int firstMode = rnd.next(0, 5);
    int secondMode = rnd.next(0, 5);

    println(n, m);
    for (int i = 1; i <= n; ++i) {
        println(pickPosition(i, firstMode));
    }
    for (int i = 1; i <= m; ++i) {
        println(pickPosition(i, secondMode));
    }

    return 0;
}
