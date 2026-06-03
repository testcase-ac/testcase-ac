#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int clampValue(int x) {
    return max(2, min(1000000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(2, 20);
        k = rnd.next(2, 20);
    } else if (mode == 1) {
        n = rnd.next(2, 200);
        k = rnd.next(n, min(1000000, n + rnd.next(0, 200)));
    } else if (mode == 2) {
        n = rnd.next(3, 300);
        k = rnd.next(max(2, n - 10), n - 1);
    } else if (mode == 3) {
        vector<int> bases = {2, 3, 4, 5, 8, 16, 31, 32, 63, 64, 127, 128,
                             255, 256, 511, 512, 999, 1000, 4096, 1000000};
        n = rnd.any(bases);
        int delta = rnd.next(-5, 5);
        k = clampValue(n + delta);
    } else if (mode == 4) {
        n = rnd.next(900000, 1000000);
        k = rnd.any(vector<int>{2, 3, 4, 5, 999999, 1000000});
    } else if (mode == 5) {
        n = rnd.next(2, 1000000);
        k = rnd.next(2, 12);
    } else {
        n = rnd.next(2, 1000000);
        k = rnd.next(2, 1000000);
    }

    println(n, k);
    return 0;
}
