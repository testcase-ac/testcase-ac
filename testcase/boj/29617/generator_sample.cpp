#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int nearValue(int center, int radius, int lo, int hi) {
    return max(lo, min(hi, center + rnd.next(-radius, radius)));
}

int randomK(int mode) {
    if (mode == 0) return rnd.next(-5, 5);
    if (mode == 1) return rnd.next(-30, 30);
    if (mode == 2) return rnd.any(vector<int>{-2000, -1999, -1000, 0, 1000, 1999, 2000});
    if (mode == 3) return rnd.next(-2000, -1500);
    return rnd.next(1500, 2000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int a;
    int b;
    int k;

    if (mode == 0) {
        a = rnd.next(0, 8);
        b = rnd.next(0, 8);
        k = randomK(0);
    } else if (mode == 1) {
        int total = rnd.next(1, 30);
        a = rnd.next(0, total);
        b = total - a;
        k = randomK(rnd.next(0, 1));
    } else if (mode == 2) {
        int base = rnd.next(1, 80);
        a = nearValue(base, 3, 0, 1000);
        b = nearValue(base, 3, 0, 1000);
        k = randomK(rnd.next(0, 2));
    } else if (mode == 3) {
        int heavy = rnd.next(800, 1000);
        int light = rnd.next(0, 12);
        if (rnd.next(0, 1) == 0) {
            a = heavy;
            b = light;
        } else {
            a = light;
            b = heavy;
        }
        k = randomK(rnd.next(2, 4));
    } else if (mode == 4) {
        a = rnd.any(vector<int>{0, 1, 999, 1000});
        b = rnd.any(vector<int>{0, 1, 999, 1000});
        k = randomK(rnd.next(2, 4));
    } else if (mode == 5) {
        a = rnd.next(100, 1000);
        b = rnd.next(100, 1000);
        k = rnd.next(-2 * max(a, b), 2 * max(a, b));
    } else {
        a = rnd.next(0, 1000);
        b = rnd.next(0, 1000);
        k = rnd.next(-2000, 2000);
    }

    if (a + b == 0) {
        if (rnd.next(0, 1) == 0) {
            a = 1;
        } else {
            b = 1;
        }
    }

    println(a, b, k);
    return 0;
}
