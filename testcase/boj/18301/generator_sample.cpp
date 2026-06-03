#include "testlib.h"
using namespace std;

int boundedValue(int maxValue, int bias) {
    return rnd.wnext(maxValue + 1, bias);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n1;
    int n2;
    int n12;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n1 = boundedValue(40, -2);
        n2 = boundedValue(40, -2);
        n12 = 0;
    } else if (mode == 1) {
        n1 = boundedValue(10000, 2);
        n2 = boundedValue(10000, 2);
        n12 = min(n1, n2);
    } else if (mode == 2) {
        n1 = rnd.next(1, 10000);
        n2 = rnd.next(1, 10000);
        n12 = rnd.next(1, min(n1, n2));
    } else if (mode == 3) {
        int cap = rnd.next(1, 80);
        n1 = rnd.next(0, cap);
        n2 = rnd.next(0, cap);
        n12 = rnd.next(0, min(n1, n2));
    } else if (mode == 4) {
        n1 = boundedValue(10000, -3);
        n2 = boundedValue(10000, 3);
        n12 = rnd.next(0, min(n1, n2));
    } else {
        n1 = rnd.next(0, 10000);
        n2 = rnd.next(0, 10000);
        n12 = rnd.next(0, min(n1, n2));
    }

    println(n1, n2, n12);
    return 0;
}
