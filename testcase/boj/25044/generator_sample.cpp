#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 0;
    } else if (mode == 1) {
        n = 1000;
    } else if (mode == 2) {
        n = rnd.next(0, 10);
    } else if (mode == 3) {
        n = rnd.next(990, 1000);
    } else if (mode == 4) {
        n = rnd.next(0, 1000);
    } else {
        int block = rnd.next(0, 20);
        n = rnd.next(block * 50, block * 50 + 49);
    }

    int kMode = rnd.next(0, 5);
    int k;
    if (kMode == 0) {
        k = 0;
    } else if (kMode == 1) {
        k = 59;
    } else if (kMode == 2) {
        k = rnd.next(1, 5);
    } else if (kMode == 3) {
        k = rnd.next(54, 59);
    } else if (kMode == 4) {
        k = rnd.next(0, 59);
    } else {
        const std::vector<int> interestingDelays = {0, 1, 2, 3, 5, 10, 15, 20, 30, 45, 58, 59};
        k = rnd.any(interestingDelays);
    }

    println(n, k);
    return 0;
}
