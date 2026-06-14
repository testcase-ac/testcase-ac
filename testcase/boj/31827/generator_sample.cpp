#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n, k;

    if (mode == 0) {
        k = rnd.next(2, 9);
        n = k;
    } else if (mode == 1) {
        k = rnd.next(2, 9);
        n = rnd.next(k, min(20, k + 3));
    } else if (mode == 2) {
        k = rnd.next(2, 9);
        n = rnd.next(max(k, 9000), 10000);
    } else if (mode == 3) {
        k = 2;
        n = rnd.next(2, 10000);
    } else if (mode == 4) {
        k = 9;
        n = rnd.next(9, 10000);
    } else if (mode == 5) {
        k = rnd.next(2, 9);
        int blockCount = rnd.next(1, 20);
        n = min(10000, k * blockCount + rnd.next(0, k - 1));
    } else if (mode == 6) {
        vector<int> candidates = {2, 3, 4, 5, 6, 7, 8, 9};
        k = rnd.any(candidates);
        n = rnd.next(k, 100);
    } else {
        k = rnd.next(2, 9);
        n = rnd.next(k, 10000);
    }

    println(n, k);
    return 0;
}
