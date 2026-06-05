#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int limit = 100000;
    const int digitLimitBoundary = 14284;

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(max(1, digitLimitBoundary - 20), digitLimitBoundary);
    } else if (mode == 2) {
        n = rnd.next(digitLimitBoundary + 1, digitLimitBoundary + 20);
    } else if (mode == 3) {
        n = rnd.next(1, 2000);
    } else if (mode == 4) {
        n = rnd.next(2001, 50000);
    } else {
        n = rnd.next(limit - 1000, limit);
    }

    println(n);
    return 0;
}
