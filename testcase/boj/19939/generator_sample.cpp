#include "testlib.h"

using namespace std;

int triangular(int k) {
    return k * (k + 1) / 2;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    int k;

    if (mode == 0) {
        k = rnd.next(2, 1000);
        int minSum = triangular(k);
        n = rnd.next(2, min(100000, max(2, minSum - 1)));
    } else if (mode == 1) {
        k = rnd.next(2, 446);
        n = triangular(k);
    } else if (mode == 2) {
        k = rnd.next(2, 446);
        int minSum = triangular(k);
        int extra = rnd.next(0, (100000 - minSum) / k) * k;
        n = minSum + extra;
    } else if (mode == 3) {
        k = rnd.next(2, 446);
        int minSum = triangular(k);
        int maxExtra = 100000 - minSum;
        int extra = rnd.next(1, maxExtra);
        if (extra % k == 0) {
            if (extra < maxExtra) {
                ++extra;
            } else {
                --extra;
            }
        }
        n = minSum + extra;
    } else {
        k = rnd.next(800, 1000);
        n = rnd.next(90000, 100000);
    }

    println(n, k);
    return 0;
}
