#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampN(long long n) {
    return static_cast<int>(max(3LL, min(1000000000LL, n)));
}

int withRemainder(int lo, int hi, int rem) {
    int first = lo;
    while (first % 3 != rem) ++first;
    int count = (hi - first) / 3 + 1;
    return first + 3 * rnd.next(0, count - 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(3, 80);
    } else if (mode == 1) {
        int rem = rnd.next(0, 2);
        n = withRemainder(3, 1000, rem);
    } else if (mode == 2) {
        int base = rnd.next(2, 500000000);
        n = 2 * base + rnd.next(0, 1);
        n = clampN(n);
    } else if (mode == 3) {
        int rem = rnd.any(vector<int>{0, 1, 2});
        n = withRemainder(999999001, 1000000000, rem);
    } else if (mode == 4) {
        vector<int> anchors = {6, 9, 10, 11, 12, 100, 101, 102, 999999937};
        int delta = rnd.next(-5, 5);
        n = clampN(static_cast<long long>(rnd.any(anchors)) + delta);
    } else {
        n = rnd.next(3, 1000000000);
    }

    println(n);
    return 0;
}
