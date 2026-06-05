#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int minN = 3;
    const int maxN = 2000000;

    vector<int> anchors = {
        3, 4, 5, 6, 7, 8, 9, 10, 15, 16, 17, 31, 32, 33,
        63, 64, 65, 99, 100, 101, 999, 1000, 1001, maxN - 1, maxN
    };

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(minN, 30);
    } else if (mode == 1) {
        int r = rnd.next(0, 3);
        int k = rnd.next(0, 25);
        n = 4 * k + r;
        if (n < minN) n += 4;
    } else if (mode == 2) {
        int base = rnd.any(anchors);
        int delta = rnd.next(-2, 2);
        n = min(max(base + delta, minN), maxN);
    } else if (mode == 3) {
        int block = rnd.next(1, 5000);
        n = 4 * block + rnd.next(0, 3);
    } else if (mode == 4) {
        n = rnd.next(100000, maxN);
    } else {
        n = rnd.any(anchors);
    }

    println(n);
    return 0;
}
