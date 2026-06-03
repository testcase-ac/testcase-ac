#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> boundaryValues = {1, 2, 3, 10, 49999, 50000};
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.any(boundaryValues);
    } else if (mode == 1) {
        n = rnd.next(1, 30);
    } else if (mode == 2) {
        n = rnd.next(31, 1000);
    } else if (mode == 3) {
        int base = rnd.next(1, 223);
        n = min(50000, base * base + rnd.next(0, base - 1));
    } else if (mode == 4) {
        n = rnd.next(10000, 50000);
    } else {
        n = rnd.next(49000, 50000);
    }

    println(n);
    return 0;
}
