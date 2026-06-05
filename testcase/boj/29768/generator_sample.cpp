#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    int k = 1;

    if (mode == 0) {
        n = rnd.next(1, 3);
        k = rnd.next(1, n);
    } else if (mode == 1) {
        n = rnd.next(1, 100);
        k = 1;
    } else if (mode == 2) {
        k = rnd.next(1, 26);
        n = k;
    } else if (mode == 3) {
        k = rnd.next(2, 26);
        n = rnd.next(k, min(100, k + 20));
    } else if (mode == 4) {
        n = rnd.next(27, 1000);
        k = rnd.next(1, 26);
    } else if (mode == 5) {
        vector<int> sizes = {99990, 99999, 100000};
        n = rnd.any(sizes);
        k = rnd.next(1, 26);
    } else {
        k = rnd.next(1, 26);
        int extra = rnd.wnext(100000 - k + 1, -3);
        n = k + extra;
    }

    println(n, k);
    return 0;
}
