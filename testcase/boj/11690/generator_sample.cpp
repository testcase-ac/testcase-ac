#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampN(int n) {
    return max(2, min(100000000, n));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {
        2, 3, 4, 5, 8, 9, 16, 25, 27, 32, 49, 64, 81, 121,
        1000, 9876, 10203040, 20151204, 99999989, 100000000
    };

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(2, 80);
    } else if (mode == 1) {
        int anchor = rnd.any(anchors);
        n = clampN(anchor + rnd.next(-5, 5));
    } else if (mode == 2) {
        n = rnd.next(81, 10000);
    } else if (mode == 3) {
        n = rnd.next(10001, 2000000);
    } else if (mode == 4) {
        n = rnd.next(2000001, 50000000);
    } else {
        n = rnd.next(50000001, 100000000);
    }

    println(n);
    return 0;
}
