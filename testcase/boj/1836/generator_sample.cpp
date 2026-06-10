#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = 1;
        k = rnd.next(2, 99);
    } else if (mode == 1) {
        n = 2 * rnd.next(1, 99);
        k = rnd.next(2, 99);
    } else if (mode == 2) {
        k = rnd.next(2, 12);
        int maxNodes = min(199, (1 << k) - 1);
        vector<int> candidates;
        for (int nodes = 2 * k - 1; nodes <= maxNodes; nodes += 2) {
            candidates.push_back(nodes);
        }
        n = rnd.any(candidates);
    } else if (mode == 3) {
        n = 2 * rnd.next(1, 99) + 1;
        k = rnd.next(2, 99);
    } else if (mode == 4) {
        n = rnd.next(180, 199);
        k = rnd.next(85, 99);
    } else {
        n = rnd.next(1, 199);
        k = rnd.next(2, 99);
    }

    println(n, k);
    return 0;
}
