#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 2000000000;

    vector<int> powers;
    long long value = 1;
    while (value <= maxN) {
        powers.push_back(static_cast<int>(value));
        value *= 3;
    }

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(2, 20);
    } else if (mode == 1) {
        int p = rnd.any(powers);
        int delta = rnd.next(-2, 2);
        n = max(2, min(maxN, p + delta));
    } else if (mode == 2) {
        int p = rnd.any(powers);
        int delta = rnd.next(0, 5);
        n = max(2, min(maxN, 2 * p + delta));
    } else if (mode == 3) {
        n = rnd.next(1000000000, maxN);
    } else if (mode == 4) {
        vector<int> special = {2, 3, 4, 8, 9, 10, 27, 28, maxN - 1, maxN};
        n = rnd.any(special);
    } else {
        n = rnd.next(2, maxN);
    }

    println(n);
    return 0;
}
