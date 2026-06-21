#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 5000;
    const int maxM = 10000;

    int n = 1;
    int m = 1;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 30);
    } else if (mode == 1) {
        vector<int> costs = {1, 3, 7, 15};
        n = rnd.next(1, 20);
        m = rnd.any(costs);
        if (rnd.next(2) == 1) {
            m += rnd.next(0, min(20, maxM - m));
        }
    } else if (mode == 2) {
        n = rnd.next(1, 30);
        int fullSlots = rnd.next(0, n);
        int remainingSlots = n - fullSlots;
        m = fullSlots * 15;
        while (remainingSlots-- > 0 && m < maxM) {
            vector<int> costs = {0, 1, 3, 7};
            m += rnd.any(costs);
        }
        m = max(1, min(m, maxM));
    } else if (mode == 3) {
        n = rnd.next(1, 20);
        m = min(maxM, 15 * n + rnd.next(1, 20));
    } else if (mode == 4) {
        n = rnd.next(1, 500);
        m = rnd.next(max(1, n - 10), min(maxM, n + 40));
    } else if (mode == 5) {
        n = rnd.next(1, maxN);
        m = rnd.next(max(1, maxM - 250), maxM);
    } else if (mode == 6) {
        vector<pair<int, int>> corners = {
            {1, 1}, {1, 2}, {1, 15}, {2, 30}, {maxN, 1}, {maxN, maxM}
        };
        auto choice = rnd.any(corners);
        n = choice.first;
        m = choice.second;
    } else {
        n = rnd.next(1, maxN);
        m = rnd.next(1, maxM);
    }

    println(n, m);
    return 0;
}
