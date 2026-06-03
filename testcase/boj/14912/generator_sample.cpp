#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> landmarks = {1, 9, 10, 11, 19, 20, 99, 100, 101,
                             999, 1000, 1001, 9999, 10000, 100000};

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 25);
    } else if (mode == 1) {
        n = rnd.any(landmarks);
    } else if (mode == 2) {
        int base = rnd.any(landmarks);
        n = base + rnd.next(-3, 3);
        n = max(1, min(100000, n));
    } else if (mode == 3) {
        n = rnd.next(90000, 100000);
    } else {
        n = rnd.next(1, 100000);
    }

    int d;
    if (mode == 0) {
        d = rnd.next(0, min(9, n));
    } else if (rnd.next(0, 3) == 0) {
        d = rnd.any(vector<int>{0, 1, 9});
    } else {
        d = rnd.next(0, 9);
    }

    println(n, d);
    return 0;
}
