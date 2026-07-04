#include "testlib.h"
#include <vector>
using namespace std;

struct Case {
    int h, a, b, c, va, vb, vc;
};

int smallValue() {
    return rnd.next(1, 40);
}

int wideValue() {
    if (rnd.next(3) == 0) return rnd.next(50000, 100000);
    return rnd.next(1, 100000);
}

Case randomCase() {
    int mode = rnd.next(6);

    if (mode == 0) {
        int v = rnd.next(1, 100000);
        return {smallValue(), smallValue(), smallValue(), smallValue(), v, v, v};
    }

    if (mode == 1) {
        return {
            rnd.next(1, 8),
            wideValue(),
            wideValue(),
            wideValue(),
            rnd.next(1, 100000),
            rnd.next(1, 100000),
            rnd.next(1, 100000),
        };
    }

    if (mode == 2) {
        return {
            rnd.next(50000, 100000),
            smallValue(),
            smallValue(),
            smallValue(),
            rnd.next(1, 100000),
            rnd.next(1, 100000),
            rnd.next(1, 100000),
        };
    }

    if (mode == 3) {
        vector<int> speeds = {1, rnd.next(2, 20), rnd.next(50000, 100000)};
        shuffle(speeds.begin(), speeds.end());
        return {smallValue(), smallValue(), wideValue(), smallValue(), speeds[0], speeds[1], speeds[2]};
    }

    if (mode == 4) {
        int h = rnd.next(1, 100000);
        int edge = rnd.next(2) == 0 ? 1 : 100000;
        return {h, edge, rnd.next(1, 100000), 100001 - edge, rnd.next(1, 100000), 1, 100000};
    }

    return {
        rnd.next(1, 100000),
        rnd.next(1, 100000),
        rnd.next(1, 100000),
        rnd.next(1, 100000),
        rnd.next(1, 100000),
        rnd.next(1, 100000),
        rnd.next(1, 100000),
    };
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int z = rnd.next(8, 16);
    println(z);
    for (int i = 0; i < z; ++i) {
        Case tc = randomCase();
        println(tc.h, tc.a, tc.b, tc.c, tc.va, tc.vb, tc.vc);
    }

    return 0;
}
