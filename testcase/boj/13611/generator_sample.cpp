#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int evenInRange(int lo, int hi) {
    lo += lo % 2;
    hi -= hi % 2;
    return rnd.next(lo / 2, hi / 2) * 2;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int p;

    if (mode == 0) {
        p = evenInRange(2, 40);
    } else if (mode == 1) {
        p = evenInRange(2, 200000);
    } else if (mode == 2) {
        p = evenInRange(190000, 200000);
    } else if (mode == 3) {
        int exponent = rnd.next(1, 16);
        p = 1 << exponent;
        if (rnd.next(0, 1) && p + 2 <= 200000) p += 2;
    } else if (mode == 4) {
        vector<int> anchors = {4, 6, 100002, 200000};
        int anchor = rnd.any(anchors);
        int delta = evenInRange(-20, 20);
        p = anchor + delta;
        p = max(2, min(200000, p));
        if (p % 2 != 0) --p;
    } else {
        int half = rnd.next(1, 100000);
        p = 2 * half;
    }

    println(p);
    return 0;
}
