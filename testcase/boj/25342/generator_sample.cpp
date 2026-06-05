#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int nearUpperBound() {
    int offset = rnd.wnext(200, -2);
    return 100000 - offset;
}

int gcdSensitiveValue() {
    int base = rnd.any(vector<int>{6, 12, 18, 24, 30, 36, 42, 60, 72, 84, 90});
    int delta = rnd.next(-3, 3);
    return max(3, min(100000, base + delta));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t;
    if (mode == 0) {
        t = rnd.next(1, 6);
    } else if (mode == 1) {
        t = rnd.next(8, 25);
    } else if (mode == 5) {
        t = rnd.next(200, 1000);
    } else {
        t = rnd.next(4, 16);
    }

    vector<int> values;
    values.reserve(t);

    for (int i = 0; i < t; ++i) {
        int caseMode = (i < 6 ? i : rnd.next(0, 5));
        int n;
        if (caseMode == 0) {
            n = rnd.next(3, 12);
        } else if (caseMode == 1) {
            n = gcdSensitiveValue();
        } else if (caseMode == 2) {
            n = rnd.next(3, 250);
            if (rnd.next(0, 1)) n = max(3, n - (n % 2));
        } else if (caseMode == 3) {
            n = rnd.next(900, 1200);
        } else if (caseMode == 4) {
            n = nearUpperBound();
        } else {
            n = rnd.next(3, 100000);
        }
        values.push_back(n);
    }

    shuffle(values.begin(), values.end());

    println(t);
    for (int n : values) {
        println(n);
    }

    return 0;
}
