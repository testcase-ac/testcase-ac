#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 3);
        k = rnd.next(1, 10);
    } else if (mode == 1) {
        n = rnd.next(1, 10);
        vector<int> smallKs = {1, 2, 3, 4, 6, 8, 10, 12, 16, 24, 36};
        k = rnd.any(smallKs);
    } else if (mode == 2) {
        n = rnd.next(7, 10);
        k = rnd.next(20, 500);
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        int base = rnd.next(2, 17);
        int multiplier = rnd.next(1, 100000 / base);
        k = base * multiplier;
    } else if (mode == 4) {
        n = rnd.next(1, 10);
        k = rnd.next(90000, 100000);
    } else {
        n = rnd.next(1, 10);
        k = rnd.next(1, 100000);
    }

    println(n, k);
    return 0;
}
