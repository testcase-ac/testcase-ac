#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int kMax = 1000000000;
    int mode = rnd.next(0, 6);
    int k = 1;

    if (mode == 0) {
        k = rnd.next(1, 30);
    } else if (mode == 1) {
        k = rnd.next(31, 1000);
    } else if (mode == 2) {
        vector<int> anchors = {13, 100, 1234567};
        int anchor = rnd.any(anchors);
        k = max(1, min(kMax, anchor + rnd.next(-20, 20)));
    } else if (mode == 3) {
        int exponent = rnd.next(1, 9);
        int base = 1;
        for (int i = 0; i < exponent; ++i) base *= 10;
        k = max(1, min(kMax, base + rnd.next(-base / 10, base / 10)));
    } else if (mode == 4) {
        k = rnd.next(1000000, 50000000);
    } else if (mode == 5) {
        k = rnd.next(50000001, 500000000);
    } else {
        k = rnd.next(900000000, kMax);
    }

    println(k);
    return 0;
}
