#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int a;
    int b;
    int c;

    if (mode == 0) {
        int value = rnd.next(1, 10000);
        a = b = c = value;
    } else if (mode == 1) {
        a = rnd.next(1, 12);
        b = rnd.next(1, 12);
        c = rnd.next(1, 12);
    } else if (mode == 2) {
        a = rnd.next(9980, 10000);
        b = rnd.next(9980, 10000);
        c = rnd.next(9980, 10000);
    } else if (mode == 3) {
        int bBase = rnd.next(1, 100);
        int aMul = rnd.next(1, 100);
        int cMul = rnd.next(1, 100);
        b = bBase;
        a = min(10000, bBase * aMul);
        c = min(10000, bBase * cMul);
    } else if (mode == 4) {
        vector<int> values = {1, 2, 3, 9998, 9999, 10000};
        shuffle(values.begin(), values.end());
        a = values[0];
        b = values[1];
        c = values[2];
    } else if (mode == 5) {
        b = rnd.next(1, 5);
        a = rnd.next(9000, 10000);
        c = rnd.next(9000, 10000);
    } else if (mode == 6) {
        b = rnd.next(9000, 10000);
        a = rnd.next(1, 50);
        c = rnd.next(1, 50);
    } else {
        a = rnd.next(1, 10000);
        b = rnd.next(1, 10000);
        c = rnd.next(1, 10000);
    }

    println(a, b, c);
    return 0;
}
