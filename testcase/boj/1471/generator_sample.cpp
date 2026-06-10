#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {
        1, 2, 3, 4, 5, 9, 10, 11, 17, 18, 19, 20,
        49, 50, 89, 90, 98, 99, 100, 101, 109, 110,
        499, 500, 565, 566, 567, 899, 900, 998, 999,
        1000, 1001, 9999, 10000, 10001, 199990, 199999, 200000
    };

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 30);
    } else if (mode == 1) {
        int base = rnd.any(anchors);
        n = base + rnd.next(-3, 3);
    } else if (mode == 2) {
        int power = 1;
        int exponent = rnd.next(1, 5);
        for (int i = 0; i < exponent; ++i) power *= 10;
        n = power + rnd.next(-12, 12);
    } else if (mode == 3) {
        n = rnd.next(31, 2000);
    } else if (mode == 4) {
        n = rnd.next(2001, 50000);
    } else {
        n = rnd.next(150000, 200000);
    }

    n = max(1, min(200000, n));
    println(n);
    return 0;
}
