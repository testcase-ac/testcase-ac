#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;

    if (mode == 0) {
        n = rnd.next(3, 10);
    } else if (mode == 1) {
        n = rnd.next(11, 100);
    } else if (mode == 2) {
        int base = 1 << rnd.next(2, 16);
        int delta = rnd.next(-2, 2);
        n = base + delta;
    } else if (mode == 3) {
        int base = (1 << rnd.next(2, 16)) - 1;
        n = base + rnd.next(0, 2);
    } else if (mode == 4) {
        n = rnd.next(1000, 100000);
    } else if (mode == 5) {
        vector<int> edges = {3, 4, 5, 6, 7, 8, 15, 16, 17, 31, 32, 33,
                             99999, 100000};
        n = rnd.any(edges);
    } else {
        n = rnd.wnext(100000 - 3 + 1, -3) + 3;
    }

    n = max(3, min(100000, n));
    println(n);

    return 0;
}
