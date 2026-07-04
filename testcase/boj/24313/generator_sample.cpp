#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Case {
    int a1;
    int a0;
    int c;
    int n0;
};

Case randomCase() {
    return {rnd.next(-100, 100), rnd.next(-100, 100), rnd.next(1, 100), rnd.next(1, 100)};
}

Case slopeFailure() {
    int c = rnd.next(1, 99);
    int a1 = rnd.next(c + 1, 100);
    int n0 = rnd.next(1, 100);
    int a0 = rnd.next(-100, 100);
    return {a1, a0, c, n0};
}

Case thresholdCase(int offset) {
    while (true) {
        int c = rnd.next(1, 100);
        int n0 = rnd.next(1, 100);
        int maxDelta = min(c + 100, 200);
        int delta = rnd.next(0, maxDelta);
        int a0 = delta * n0 + offset;
        if (-100 <= a0 && a0 <= 100) {
            return {c - delta, a0, c, n0};
        }
    }
}

Case boundaryCase() {
    vector<int> edges = {-100, -99, -1, 0, 1, 99, 100};
    int c = rnd.any(vector<int>{1, 2, 99, 100});
    int n0 = rnd.any(vector<int>{1, 2, 99, 100});
    int a1 = rnd.any(edges);
    int a0 = rnd.any(edges);
    return {a1, a0, c, n0};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    Case tc;
    if (mode == 0) {
        tc = randomCase();
    } else if (mode == 1) {
        tc = slopeFailure();
    } else if (mode == 2) {
        tc = thresholdCase(-1);
    } else if (mode == 3) {
        tc = thresholdCase(0);
    } else if (mode == 4) {
        tc = thresholdCase(1);
    } else {
        tc = boundaryCase();
    }

    println(tc.a1, tc.a0);
    println(tc.c);
    println(tc.n0);
    return 0;
}
