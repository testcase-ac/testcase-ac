#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k;
    int d1;
    int d2;

    if (mode == 0) {
        k = rnd.next(1, 100);
        d1 = d2 = rnd.next(1, 100);
    } else if (mode == 1) {
        d2 = rnd.next(1, 33);
        d1 = 3 * d2;
        k = rnd.next(d2 + 1, 100);
    } else if (mode == 2) {
        k = rnd.next(1, 50);
        int diff = 2 * k - 1;
        d2 = rnd.next(1, 100 - diff);
        d1 = d2 + diff;
    } else if (mode == 3) {
        k = rnd.next(1, 100);
        d2 = rnd.next(1, 100);
        int maxDiff = min(100 - d2, 2 * k - 1);
        d1 = d2 + rnd.next(0, maxDiff);
    } else {
        vector<int> candidates;
        k = rnd.next(1, 100);
        d2 = rnd.next(1, 100);
        for (int diff = 0; diff <= 100 - d2; ++diff) {
            if (diff < 2 * k) {
                candidates.push_back(diff);
            }
        }
        d1 = d2 + rnd.any(candidates);
    }

    println(k);
    println(d1, d2);
    return 0;
}
