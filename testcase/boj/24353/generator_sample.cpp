#include "testlib.h"

#include <vector>

using namespace std;

int chooseN() {
    int mode = rnd.next(0, 8);
    if (mode == 0) return 23;
    if (mode == 1) return rnd.next(24, 35);
    if (mode == 2) return rnd.next(36, 99);
    if (mode == 3) return rnd.next(90, 150);
    if (mode == 4) return rnd.next(151, 999);
    if (mode == 5) return rnd.next(900, 1100);
    if (mode == 6) return rnd.next(1101, 9998);
    if (mode == 7) return 9999;

    vector<int> thresholds = {23, 24, 30, 99, 100, 101, 999, 1000, 9999};
    return rnd.any(thresholds);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = chooseN();
    int s = rnd.next(1, 9);
    int m = rnd.next(1, 12);

    println(n, s, m);
    return 0;
}
