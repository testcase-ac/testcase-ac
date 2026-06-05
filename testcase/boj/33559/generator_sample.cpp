#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long pickValue(int poolIndex, bool useLargeValues) {
    if (useLargeValues && rnd.next(4) == 0) {
        return 1000000000LL - rnd.next(0, 20);
    }
    return 1LL + poolIndex;
}

vector<long long> makeArray(int n, const vector<long long>& pool, int concentration) {
    vector<long long> result;
    result.reserve(n);

    for (int i = 0; i < n; ++i) {
        int index;
        if (concentration > 0) {
            index = rnd.wnext((int)pool.size(), -concentration);
        } else {
            index = rnd.next((int)pool.size());
        }
        result.push_back(pool[index]);
    }

    shuffle(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = (mode == 4 ? rnd.next(20, 60) : rnd.next(1, 18));
    int poolSize = rnd.next(1, min(12, max(1, n + 4)));
    bool useLargeValues = rnd.next(5) == 0;

    vector<long long> basePool;
    basePool.reserve(poolSize + 6);
    for (int i = 0; i < poolSize; ++i) {
        basePool.push_back(pickValue(i, useLargeValues));
    }

    vector<long long> a;
    vector<long long> b;

    if (mode == 0) {
        a = makeArray(n, basePool, rnd.next(0, 3));
        b = a;
        shuffle(b.begin(), b.end());
    } else if (mode == 1) {
        a = makeArray(n, basePool, rnd.next(0, 4));

        vector<long long> disjointPool;
        disjointPool.reserve(poolSize);
        for (int i = 0; i < poolSize; ++i) {
            disjointPool.push_back(pickValue(100 + i, useLargeValues));
        }
        b = makeArray(n, disjointPool, rnd.next(0, 4));
    } else {
        int sharedCount = rnd.next(1, poolSize);

        vector<long long> poolA = basePool;
        vector<long long> poolB(basePool.begin(), basePool.begin() + sharedCount);
        for (int i = sharedCount; i < poolSize; ++i) {
            poolB.push_back(pickValue(200 + i, useLargeValues));
        }

        int concentration = (mode == 3 ? rnd.next(2, 5) : rnd.next(0, 3));
        a = makeArray(n, poolA, concentration);
        b = makeArray(n, poolB, concentration);

        if (mode == 4 && n >= 4) {
            a[0] = 1;
            b[0] = 1;
            a[1] = 1000000000LL;
            b[1] = 1000000000LL;
            a[2] = 2;
            b[2] = 999999999LL;
        }
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
