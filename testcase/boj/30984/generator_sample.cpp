#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int pickValue(const vector<int>& anchors) {
    if (rnd.next(100) < 55) {
        return rnd.any(anchors);
    }
    return rnd.next(1, 1000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases = {
        {1, 1},       {1, 2},       {2, 1},       {2, 2},
        {2, 5},       {5, 2},       {999, 1000},  {1000, 999},
        {1000, 1000},
    };

    int mode = rnd.next(5);
    int n = 1;
    int k = 1;

    if (mode == 0) {
        tie(n, k) = rnd.any(cases);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        k = rnd.next(1, 12);
    } else if (mode == 2) {
        int base = rnd.next(1, 1000);
        int delta = rnd.next(-8, 8);
        n = base;
        k = max(1, min(1000, base + delta));
    } else if (mode == 3) {
        vector<int> anchors = {1, 2, 3, 10, 50, 100, 500, 999, 1000};
        n = pickValue(anchors);
        k = pickValue(anchors);
    } else {
        n = rnd.next(1, 1000);
        k = rnd.next(1, 1000);
    }

    if (rnd.next(2)) {
        swap(n, k);
    }

    println(n, k);
    return 0;
}
