#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int minN = 2;
    const int maxN = 100000;
    vector<int> anchors = {
        minN, 3, 4, 5, 10, 16, 31, 32, 33, 64, 100, 1000, 9999, 10000, 99999, maxN,
    };

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(minN, 30);
    } else if (mode == 1) {
        int anchor = rnd.any(anchors);
        n = anchor + rnd.next(-3, 3);
    } else if (mode == 2) {
        int power = 1 << rnd.next(1, 16);
        n = power + rnd.next(-5, 5);
    } else if (mode == 3) {
        n = rnd.next(90000, maxN);
    } else if (mode == 4) {
        n = rnd.next(minN, 1000);
    } else {
        n = rnd.next(minN, maxN);
    }

    n = max(minN, min(maxN, n));
    println(n);
    return 0;
}
