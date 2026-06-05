#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> boundaryValues = {
        2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 16, 17, 31, 32, 33, 63, 64, 65, 98, 99,
    };

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 12);
    } else if (mode == 1) {
        n = rnd.any(boundaryValues);
    } else if (mode == 2) {
        int base = 1 << rnd.next(1, 7);
        n = base + rnd.next(-1, 1);
        n = max(2, min(99, n));
    } else if (mode == 3) {
        n = rnd.next(13, 50);
    } else if (mode == 4) {
        n = rnd.next(51, 98);
    } else {
        n = rnd.wnext(98, 3) + 2;
    }

    println(n);
    return 0;
}
