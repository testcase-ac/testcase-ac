#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedB(int value, int a) {
    return max(a + 1, min(value, 1000000));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int a = 1;
    int b = 2;

    if (mode == 0) {
        a = rnd.next(1, 999999);
        b = boundedB(a + rnd.next(1, min(50, 1000000 - a)), a);
    } else if (mode == 1) {
        a = rnd.next(1, 500000);
        int steps = rnd.next(1, 6);
        b = a;
        for (int i = 0; i < steps && b <= 500000; ++i) b *= 2;
        b = boundedB(b + rnd.next(0, 20), a);
    } else if (mode == 2) {
        a = rnd.next(1, 100000);
        b = boundedB(a * 10 + rnd.next(0, 80), a);
    } else if (mode == 3) {
        a = rnd.next(1, 1000);
        int base = a;
        int doubleSteps = rnd.next(0, 4);
        for (int i = 0; i < doubleSteps && base <= 50000; ++i) base *= 2;
        b = boundedB(base * 10 + rnd.next(0, 200), a);
    } else if (mode == 4) {
        vector<int> anchors = {1, 2, 3, 9, 10, 99, 100, 999, 1000, 999999};
        a = rnd.any(anchors);
        if (a == 999999) {
            b = 1000000;
        } else {
            b = boundedB(rnd.next(a + 1, 1000000), a);
        }
    } else {
        a = rnd.next(1, 999999);
        b = rnd.next(a + 1, 1000000);
    }

    println(a, b);
    return 0;
}
