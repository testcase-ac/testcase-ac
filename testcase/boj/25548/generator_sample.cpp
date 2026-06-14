#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int limit = 1000000000;
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 80);
    } else if (mode == 1) {
        int base = rnd.next(1, 100000);
        int delta = rnd.next(-3, 3);
        long long value = 1LL * base * base + delta;
        n = static_cast<int>(max(1LL, min<long long>(limit, value)));
    } else if (mode == 2) {
        vector<int> anchors = {
            10, 100, 1000, 10000, 100000,
            1000000, 10000000, 100000000, limit
        };
        int anchor = rnd.any(anchors);
        int span = min(2000, anchor - 1);
        n = anchor - rnd.next(0, span);
    } else if (mode == 3) {
        int q = rnd.next(1, 100000);
        int k = rnd.next(1, 10000);
        long long value = 1LL * q * k + rnd.next(0, max(0, q - 1));
        n = static_cast<int>(min<long long>(limit, value));
    } else if (mode == 4) {
        n = limit - rnd.next(0, 1000000);
    } else {
        n = rnd.next(1, limit);
    }

    println(n);
    return 0;
}
