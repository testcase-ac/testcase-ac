#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000;
    int mode = rnd.next(6);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(13, 200);
    } else if (mode == 2) {
        n = rnd.next(201, 10000);
    } else if (mode == 3) {
        int k = rnd.next(2, 1414);
        int center = k * (k + 1) / 2;
        int delta = rnd.next(-3, 3);
        n = center + delta;
    } else if (mode == 4) {
        int k = rnd.next(1, 1000);
        int center = k * k;
        int delta = rnd.next(-5, 5);
        n = center + delta;
    } else {
        n = maxN - rnd.wnext(50000, 2);
    }

    n = max(1, min(maxN, n));
    println(n);
    return 0;
}
