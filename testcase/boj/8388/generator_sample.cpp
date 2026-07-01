#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
    } else if (mode == 2) {
        n = rnd.next(31, 120);
    } else if (mode == 3) {
        n = rnd.next(121, 500);
    } else if (mode == 4) {
        std::vector<int> boundaryN = {2, 3, 4, 10, 50, 499, 500};
        n = rnd.any(boundaryN);
    } else {
        n = rnd.next(1, 500);
    }

    int maxK = n * (n - 1) / 2;
    int k;
    if (mode == 0) {
        k = rnd.next(0, maxK);
    } else if (mode == 1) {
        int edge = min(maxK, rnd.next(0, 10));
        k = rnd.next(0, 1) ? edge : maxK - edge;
    } else if (mode == 2) {
        int middle = maxK / 2;
        int radius = min(maxK, max(1, n));
        k = rnd.next(max(0, middle - radius), min(maxK, middle + radius));
    } else if (mode == 3) {
        int cap = min(maxK, 62500);
        k = rnd.next(0, cap);
        if (rnd.next(0, 1)) k = maxK - k;
    } else if (mode == 4) {
        std::vector<int> boundaryK = {0, maxK, maxK / 2};
        k = rnd.any(boundaryK);
    } else {
        k = rnd.next(0, maxK);
    }

    println(n, k);
    return 0;
}
