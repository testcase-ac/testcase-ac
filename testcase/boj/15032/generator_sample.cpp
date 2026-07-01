#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampBound(int value) {
    return max(1, min(400, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 1;
    int k = 1;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        k = n;
    } else if (mode == 2) {
        n = rnd.next(2, 40);
        k = rnd.next(1, n - 1);
    } else if (mode == 3) {
        n = rnd.next(1, 40);
        k = rnd.next(n, 120);
    } else if (mode == 4) {
        n = rnd.next(1, 30);
        int multiplier = rnd.next(2, 12);
        k = clampBound(n * multiplier + rnd.next(-3, 3));
    } else if (mode == 5) {
        n = rnd.next(300, 400);
        k = rnd.next(1, 80);
    } else if (mode == 6) {
        n = rnd.next(300, 400);
        k = rnd.next(300, 400);
    } else {
        vector<int> nAnchors = {1, 2, 3, 6, 10, 50, 200, 399, 400};
        vector<int> kAnchors = {1, 2, 3, 10, 50, 200, 399, 400};
        n = rnd.any(nAnchors);
        k = rnd.any(kAnchors);
    }

    println(n, k);
    return 0;
}
