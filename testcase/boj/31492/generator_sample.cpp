#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int chooseRank(int mode, int step, int remaining) {
    if (mode == 0) {
        return 1;
    }
    if (mode == 1) {
        return remaining;
    }
    if (mode == 2) {
        return step % 2 == 0 ? 1 : remaining;
    }
    if (mode == 3) {
        int window = min(remaining, 4);
        return rnd.next(1, window);
    }
    if (mode == 4) {
        int window = min(remaining, 4);
        return remaining - rnd.next(0, window - 1);
    }
    return rnd.next(1, remaining);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int half;
    if (mode == 0) {
        half = rnd.next(1, 4);
    } else if (mode == 1) {
        half = rnd.next(3, 8);
    } else {
        half = rnd.next(1, 14);
    }

    int n = half * 2;
    vector<int> a(half), b(half);
    for (int i = 0; i < half; ++i) {
        int firstRemaining = n - 2 * i;
        int secondRemaining = firstRemaining - 1;
        a[i] = chooseRank(mode, 2 * i, firstRemaining);
        b[i] = chooseRank(mode, 2 * i + 1, secondRemaining);
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
