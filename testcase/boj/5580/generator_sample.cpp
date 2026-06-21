#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 3);
    } else if (mode == 2) {
        n = rnd.next(4, 5);
    } else if (mode == 3) {
        n = rnd.next(6, 7);
    } else {
        n = rnd.next(1, 7);
    }

    int cells = n * n;
    int minM = cells;
    int m;
    if (mode == 0) {
        m = rnd.next(1, 20);
    } else if (mode == 1) {
        m = rnd.next(minM, minM + 20);
    } else if (mode == 2) {
        m = rnd.next(minM, 120);
    } else if (mode == 3) {
        m = rnd.next(1500, 2000);
    } else {
        m = rnd.next(minM, 2000);
    }

    int minSum = cells * (cells + 1) / 2;
    int maxSum = cells * (2 * m - cells + 1) / 2;
    if (maxSum > 3000) {
        maxSum = 3000;
    }

    int s;
    int sumMode = rnd.next(0, 5);
    if (sumMode == 0) {
        s = minSum;
    } else if (sumMode == 1) {
        s = maxSum;
    } else if (sumMode == 2) {
        int hi = minSum + rnd.next(0, 30);
        if (hi > maxSum) {
            hi = maxSum;
        }
        s = rnd.next(minSum, hi);
    } else if (sumMode == 3) {
        int lo = maxSum - rnd.next(0, 30);
        if (lo < minSum) {
            lo = minSum;
        }
        s = rnd.next(lo, maxSum);
    } else {
        s = rnd.next(minSum, maxSum);
    }

    println(n, m, s);
    return 0;
}
