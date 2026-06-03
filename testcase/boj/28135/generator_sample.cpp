#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int clampN(int n) {
    return max(1, min(1000000, n));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(45, 55);
    } else if (mode == 1) {
        vector<int> values = {150, 250, 500, 501, 505, 950, 1050, 5000, 5050, 50123, 150000, 950000};
        n = rnd.any(values);
        n = clampN(n + rnd.next(-3, 3));
    } else if (mode == 2) {
        vector<int> bases = {10, 100, 1000, 10000, 100000, 1000000};
        n = clampN(rnd.any(bases) + rnd.next(-5, 5));
    } else if (mode == 3) {
        n = rnd.next(1, 200);
    } else if (mode == 4) {
        n = rnd.next(900000, 1000000);
    } else {
        n = rnd.next(1, 1000000);
    }

    println(n);
    return 0;
}
