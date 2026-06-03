#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int randomXForGroups(int groups) {
    int total = 3 * groups;
    int lo = max(0, total - 3000);
    int hi = min(3000, total);
    return rnd.next(lo, hi);
}

int randomXWithParity(int groups, int parity) {
    int total = 3 * groups;
    int lo = max(0, total - 3000);
    int hi = min(3000, total);
    vector<int> candidates;
    for (int x = lo; x <= hi; ++x) {
        if (x % 2 == parity) candidates.push_back(x);
    }
    return rnd.any(candidates);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int groups = 1;
    int x = 0;

    if (mode == 0) {
        groups = rnd.next(1, 8);
        x = randomXForGroups(groups);
    } else if (mode == 1) {
        groups = rnd.next(1, 20);
        x = randomXWithParity(groups, rnd.next(0, 1));
    } else if (mode == 2) {
        groups = rnd.next(1, 1000);
        x = rnd.next(0, 1) ? 0 : 3 * groups;
    } else if (mode == 3) {
        groups = rnd.next(900, 2000);
        x = randomXForGroups(groups);
    } else if (mode == 4) {
        groups = rnd.next(1, 1000);
        int total = 3 * groups;
        int edge = rnd.next(0, min(12, total));
        x = rnd.next(0, 1) ? edge : total - edge;
    } else {
        groups = rnd.any(vector<int>{1, 2, 3, 10, 100, 999, 1000, 1999, 2000});
        x = randomXForGroups(groups);
    }

    int y = 3 * groups - x;
    println(x, y);
    return 0;
}
