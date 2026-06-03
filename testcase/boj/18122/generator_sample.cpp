#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int kMaxN = 1000000;
    vector<int> candidates;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        candidates = {1, 2, 3, 4, 5, 6, 7, 8};
    } else if (mode == 1) {
        int base = 1 << rnd.next(0, 19);
        int delta = rnd.next(-3, 3);
        candidates.push_back(base + delta);
    } else if (mode == 2) {
        int base = rnd.any(vector<int>{99991, 100000, 123457, 500000, 999983});
        int delta = rnd.next(-20, 20);
        candidates.push_back(base + delta);
    } else if (mode == 3) {
        candidates = {kMaxN - rnd.next(0, 200)};
    } else if (mode == 4) {
        int lo = rnd.next(1, 2000);
        int hi = rnd.next(lo, min(kMaxN, lo + rnd.next(0, 20000)));
        candidates.push_back(rnd.next(lo, hi));
    } else {
        candidates.push_back(rnd.next(1, kMaxN));
    }

    int n = rnd.any(candidates);
    n = max(1, min(kMaxN, n));
    println(n);

    return 0;
}
