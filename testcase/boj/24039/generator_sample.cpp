#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 10000;
    vector<int> special = {
        6, 15, 35, 77, 143, 221, 323, 437, 667, 899, 1147, 1517,
        1763, 2021, 2491, 3127, 3599, 4087, 4757, 5183, 5767, 6557,
        7387, 8633, 9797, 10403
    };

    vector<int> candidates;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        candidates.push_back(1);
        candidates.push_back(rnd.next(1, 20));
    } else if (mode == 1) {
        int x = rnd.any(special);
        for (int delta = -2; delta <= 2; ++delta) {
            int n = x + delta;
            if (1 <= n && n <= maxN) candidates.push_back(n);
        }
    } else if (mode == 2) {
        int index = rnd.next(0, (int)special.size() - 2);
        int low = max(1, special[index] + 1);
        int high = min(maxN, special[index + 1] - 1);
        if (low <= high) candidates.push_back(rnd.next(low, high));
    } else if (mode == 3) {
        candidates.push_back(rnd.next(9000, maxN));
        candidates.push_back(maxN);
    } else {
        candidates.push_back(rnd.next(1, maxN));
        candidates.push_back(rnd.wnext(maxN, 3) + 1);
        candidates.push_back(rnd.wnext(maxN, -3) + 1);
    }

    println(rnd.any(candidates));
    return 0;
}
