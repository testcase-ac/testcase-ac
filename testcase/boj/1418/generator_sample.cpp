#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> interestingK = {1, 2, 3, 4, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 47, 53, 71, 97, 100};
    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 30);
        k = rnd.next(1, 10);
    } else if (mode == 1) {
        n = rnd.next(1, 200);
        k = rnd.any(interestingK);
    } else if (mode == 2) {
        n = rnd.next(90000, 100000);
        k = rnd.next(1, 100);
    } else if (mode == 3) {
        n = rnd.next(1, 100000);
        k = rnd.next(1, 3);
    } else if (mode == 4) {
        n = rnd.next(1, 100000);
        k = rnd.next(80, 100);
    } else {
        k = rnd.any(interestingK);
        int radius = rnd.next(0, 25);
        n = min(100000, max(1, k * rnd.next(1, 40) + rnd.next(-radius, radius)));
    }

    println(n);
    println(k);

    return 0;
}
