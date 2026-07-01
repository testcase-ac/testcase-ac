#include "testlib.h"

#include <vector>
using namespace std;

const int MAX_T = 1000;
const int MAX_K = 1000000000;

int nearValue(int base, int lo, int hi) {
    int delta = rnd.next(-5, 5);
    int value = base + delta;
    if (value < lo) value = lo;
    if (value > hi) value = hi;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t;
    int k;

    if (mode == 0) {
        t = rnd.next(2, 8);
        k = rnd.next(1, 12);
    } else if (mode == 1) {
        vector<int> tEdges = {2, 3, 4, 999, 1000};
        vector<int> kEdges = {1, 2, 3, 999999999, MAX_K};
        t = rnd.any(tEdges);
        k = rnd.any(kEdges);
    } else if (mode == 2) {
        t = rnd.next(2, 40);
        k = nearValue(t, 1, MAX_K);
    } else if (mode == 3) {
        t = rnd.next(50, MAX_T);
        k = rnd.next(1, 2000);
    } else if (mode == 4) {
        t = rnd.next(2, MAX_T);
        k = rnd.next(999000000, MAX_K);
    } else {
        t = rnd.next(2, MAX_T);
        k = rnd.next(1, MAX_K);
    }

    println(t, k);
    return 0;
}
