#include "testlib.h"

#include <vector>

using namespace std;

int nextNotParallel(int x, int y, int ga) {
    while (true) {
        int gb = rnd.next(1, 1000000);
        if ((long long)ga * y != (long long)gb * x) return gb;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 12);
    } else if (mode == 2) {
        n = rnd.next(2, 8);
    } else {
        n = rnd.next(20, 60);
    }

    int x = rnd.next(1, 50);
    int y = rnd.next(1, 50);

    vector<int> ga(n), gb(n), w(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 2) {
            int scale = rnd.next(1, 20);
            ga[i] = x * scale;
            int delta = rnd.any(vector<int>{-2, -1, 1, 2});
            long long candidate = (long long)y * scale + delta;
            if (candidate < 1 || candidate > 1000000) candidate = (long long)y * scale - delta;
            gb[i] = (int)candidate;
            if ((long long)ga[i] * y == (long long)gb[i] * x) {
                gb[i] = nextNotParallel(x, y, ga[i]);
            }
        } else {
            int hi = (mode == 3 ? 1000000 : 100);
            ga[i] = rnd.next(1, hi);
            gb[i] = nextNotParallel(x, y, ga[i]);
        }

        int wHi = (mode == 3 ? 1000000 : 300);
        w[i] = rnd.next(1, wHi);
    }

    println(n, x, y);
    println(ga);
    println(gb);
    println(w);

    return 0;
}
