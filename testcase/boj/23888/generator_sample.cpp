#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int pickEndpointBiasedIndex() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return 1;
    if (mode == 1) return 1000000;
    if (mode == 2) return rnd.next(1, 20);
    if (mode == 3) return rnd.next(999980, 1000000);
    return rnd.next(1, 1000000);
}

pair<int, int> pickRange() {
    int l = pickEndpointBiasedIndex();
    int r = pickEndpointBiasedIndex();
    if (l > r) swap(l, r);

    if (rnd.next(0, 4) == 0) r = l;
    if (rnd.next(0, 4) == 0) {
        int width = rnd.next(0, 20);
        r = min(1000000, l + width);
    }

    return {l, r};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int a;
    int d;
    if (mode == 0) {
        a = rnd.next(1, 20);
        d = 0;
    } else if (mode == 1) {
        a = rnd.next(999980, 1000000);
        d = rnd.next(0, 20);
    } else if (mode == 2) {
        int g = rnd.next(1, 1000);
        a = g * rnd.next(1, 1000000 / g);
        d = g * rnd.next(0, 1000000 / g);
    } else if (mode == 3) {
        a = rnd.next(1, 1000000);
        d = 1000000;
    } else {
        a = rnd.next(1, 1000000);
        d = rnd.next(0, 1000000);
    }

    int q = rnd.next(1, 20);
    println(a, d);
    println(q);

    bool sawSum = false;
    bool sawGcd = false;
    for (int i = 0; i < q; ++i) {
        int type;
        if (i == q - 1 && !sawSum) {
            type = 1;
        } else if (i == q - 1 && !sawGcd) {
            type = 2;
        } else {
            type = rnd.next(1, 2);
        }

        sawSum |= type == 1;
        sawGcd |= type == 2;

        pair<int, int> range = pickRange();
        println(type, range.first, range.second);
    }

    return 0;
}
