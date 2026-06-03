#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int pickNearBoundary(int n) {
    vector<int> candidates;

    for (int value = 0; value <= min(n, 5); ++value) {
        candidates.push_back(value);
    }
    for (int delta = 0; delta <= min(n, 5); ++delta) {
        candidates.push_back(n - delta);
    }
    candidates.push_back(n / 2);
    if (n > 1) {
        candidates.push_back((n - 1) / 2);
        candidates.push_back((n + 1) / 2);
    }

    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
    return rnd.any(candidates);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(9, 30);
    } else if (mode == 2) {
        n = rnd.any(vector<int>{1, 2, 3, 4, 5, 99991, 99999, 100000});
    } else if (mode == 3) {
        n = rnd.next(99900, 100000);
    } else if (mode == 4) {
        n = 2 * rnd.next(1, 50);
    } else if (mode == 5) {
        n = 2 * rnd.next(1, 50) - 1;
    } else {
        n = rnd.next(1, 100000);
    }

    int k;
    if (mode <= 3) {
        k = pickNearBoundary(n);
    } else if (mode <= 5) {
        int base = pickNearBoundary(n);
        int shift = rnd.next(-3, 3);
        k = max(0, min(n, base + shift));
    } else {
        k = rnd.next(0, n);
    }

    println(n, k);
    return 0;
}
