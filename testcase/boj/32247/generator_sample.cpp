#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

struct Trap {
    int c;
    int x;
    int h;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    int hLow;
    int hHigh;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(0, n - 1);
        hLow = -3;
        hHigh = 3;
    } else if (mode == 1) {
        n = rnd.next(5, 12);
        m = rnd.next(0, n - 1);
        hLow = -10;
        hHigh = 10;
    } else if (mode == 2) {
        n = rnd.next(8, 18);
        m = n - 1;
        hLow = -20;
        hHigh = 20;
    } else if (mode == 3) {
        n = rnd.next(6, 16);
        m = rnd.next(max(0, n / 2 - 1), n - 1);
        hLow = -1000000;
        hHigh = 1000000;
    } else if (mode == 4) {
        n = rnd.next(10, 25);
        m = rnd.next(1, n - 1);
        hLow = -2;
        hHigh = 2;
    } else {
        n = rnd.next(100, 400);
        m = rnd.next(0, min(n - 1, 40));
        hLow = -50;
        hHigh = 50;
    }

    vector<int> xs(n - 1);
    iota(xs.begin(), xs.end(), 1);
    shuffle(xs.begin(), xs.end());
    xs.resize(m);
    sort(xs.begin(), xs.end());

    vector<Trap> traps;
    traps.reserve(m);
    for (int i = 0; i < m; ++i) {
        int c = rnd.next(0, 1);
        int h;
        if (mode == 4 && i > 0) {
            h = traps.back().h + rnd.next(-1, 1);
            h = max(-1000000, min(1000000, h));
        } else {
            h = rnd.next(hLow, hHigh);
        }
        traps.push_back({c, xs[i], h});
    }

    if (rnd.next(0, 1) == 1) {
        shuffle(traps.begin(), traps.end());
    }

    println(n, m);
    for (const Trap& trap : traps) {
        println(trap.c, trap.x, trap.h);
    }

    return 0;
}
