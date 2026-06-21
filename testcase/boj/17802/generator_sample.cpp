#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int x;

    if (mode == 0) {
        n = rnd.next(1, 20);
        int threshold = 1 << (n - 1);
        x = threshold;
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        int threshold = 1 << (n - 1);
        x = rnd.next(1, threshold - 1);
    } else if (mode == 2) {
        n = rnd.next(1, 20);
        int threshold = 1 << (n - 1);
        int slack = rnd.next(0, min(1000, 1000000000 - threshold));
        x = threshold + slack;
    } else if (mode == 3) {
        n = rnd.next(1, 10);
        x = rnd.next(1, 2000);
    } else if (mode == 4) {
        n = rnd.next(15, 20);
        int threshold = 1 << (n - 1);
        int lo = max(1, threshold - 1000);
        int hi = min(1000000000, threshold + 1000);
        x = rnd.next(lo, hi);
    } else {
        vector<int> ns = {1, 2, 3, 19, 20};
        n = rnd.any(ns);
        x = rnd.next(1, 1000000000);
    }

    println(n, x);
    return 0;
}
