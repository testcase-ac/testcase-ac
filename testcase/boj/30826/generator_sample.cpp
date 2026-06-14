#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

using int64 = long long;

const int64 MIN_K = 1;
const int64 MAX_K = 10000000000000000LL;

vector<int64> buildBlockEnds() {
    vector<int64> ends;
    int64 total = 0;
    int64 count = 9;
    for (int len = 1; total < MAX_K; ++len) {
        int64 add = count * len;
        if (MAX_K - total <= add) {
            total = MAX_K;
        } else {
            total += add;
        }
        ends.push_back(total);
        if (len % 2 == 0) count *= 10;
    }
    return ends;
}

int64 clampK(int64 k) {
    return max(MIN_K, min(MAX_K, k));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int64> blockEnds = buildBlockEnds();
    int mode = rnd.next(0, 5);
    int64 k;

    if (mode == 0) {
        k = rnd.next(MIN_K, 200LL);
    } else if (mode == 1) {
        int idx = rnd.next(0, (int)blockEnds.size() - 1);
        int64 boundary = blockEnds[idx];
        k = clampK(boundary + rnd.next(-20LL, 20LL));
    } else if (mode == 2) {
        int exp = rnd.next(0, 16);
        int64 p = 1;
        for (int i = 0; i < exp; ++i) p *= 10;
        k = clampK(p + rnd.next(-1000LL, 1000LL));
    } else if (mode == 3) {
        k = MAX_K - rnd.next(0LL, 100000LL);
    } else if (mode == 4) {
        int idx = rnd.next(0, (int)blockEnds.size() - 1);
        int64 lo = idx == 0 ? MIN_K : blockEnds[idx - 1] + 1;
        int64 hi = blockEnds[idx];
        k = rnd.next(lo, hi);
    } else {
        k = rnd.next(MIN_K, MAX_K);
    }

    println(k);
    return 0;
}
