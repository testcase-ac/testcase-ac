#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace {

__int128 validCountWithLength(int length) {
    __int128 total = 1;
    for (int i = 0; i < length; ++i) {
        total *= 3;
    }

    __int128 allCountsEven = 0;
    if (length % 2 == 0) {
        allCountsEven = (total + 3) / 4;
    }
    return total - allCountsEven;
}

long long totalValidCount(int n) {
    __int128 result = 0;
    for (int length = 1; length <= n; ++length) {
        result += validCountWithLength(length);
    }
    return static_cast<long long>(result);
}

long long randomLongLong(long long lo, long long hi) {
    return rnd.next(lo, hi);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> interestingN = {1, 2, 3, 4, 5, 9, 10, 15, 20, 25, 29, 30};

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.any(interestingN);
    } else if (mode == 1) {
        n = rnd.next(1, 6);
    } else if (mode == 2) {
        n = rnd.next(7, 15);
    } else if (mode == 3) {
        n = rnd.next(16, 29);
    } else {
        n = 30;
    }

    long long maxK = totalValidCount(n);
    vector<long long> boundaryK = {1, maxK};
    if (maxK >= 2) {
        boundaryK.push_back(2);
        boundaryK.push_back(maxK - 1);
    }
    if (maxK >= 3) {
        boundaryK.push_back(3);
    }

    long long k;
    int kMode = rnd.next(0, 4);
    if (kMode == 0) {
        k = rnd.any(boundaryK);
    } else if (kMode == 1) {
        long long hi = min<long long>(maxK, 1000);
        k = randomLongLong(1, hi);
    } else if (kMode == 2) {
        long long span = min<long long>(maxK, 1000);
        k = maxK - randomLongLong(0, span - 1);
    } else {
        k = randomLongLong(1, maxK);
    }

    println(n, k);
    return 0;
}
