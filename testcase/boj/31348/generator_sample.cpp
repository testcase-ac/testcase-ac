#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

namespace {
const int MAX_A = 1000000;

void addGeometricChain(set<int>& values) {
    int ratio = rnd.next(2, 6);
    int start = rnd.next(1, 30);
    long long x = start;
    while (x <= MAX_A && static_cast<int>(values.size()) < 45) {
        values.insert(static_cast<int>(x));
        x *= ratio;
        if (rnd.next(3) == 0 && values.size() >= 3) {
            break;
        }
    }
}

void addSquareKernelFamily(set<int>& values) {
    int kernel = rnd.next(1, 20);
    int maxM = rnd.next(4, 35);
    for (int m = 1; m <= maxM && static_cast<int>(values.size()) < 45; ++m) {
        long long x = 1LL * kernel * m * m;
        if (x <= MAX_A && rnd.next(100) < 75) {
            values.insert(static_cast<int>(x));
        }
    }
}

void addSparseRandom(set<int>& values, int target) {
    int windowHigh = rnd.next(30, MAX_A);
    while (static_cast<int>(values.size()) < target) {
        values.insert(rnd.next(1, windowHigh));
    }
}

void addBoundaryValues(set<int>& values) {
    values.insert(1);
    values.insert(MAX_A);
    values.insert(MAX_A - rnd.next(0, 20));
    values.insert(rnd.next(2, 20));
}
}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    set<int> values;
    int mode = rnd.next(0, 4);
    int targetN = rnd.next(1, 40);

    if (mode == 0) {
        addGeometricChain(values);
        addSparseRandom(values, targetN);
    } else if (mode == 1) {
        addSquareKernelFamily(values);
        addSparseRandom(values, targetN);
    } else if (mode == 2) {
        addBoundaryValues(values);
        addSparseRandom(values, targetN);
    } else {
        int base = rnd.next(1, 100);
        int step = rnd.next(1, 200);
        for (int i = 0; i < targetN; ++i) {
            long long x = 1LL * base + 1LL * i * step + rnd.next(0, step / 2 + 1);
            if (x <= MAX_A) {
                values.insert(static_cast<int>(x));
            }
        }
        addSparseRandom(values, targetN);
    }

    vector<int> a(values.begin(), values.end());
    println(static_cast<int>(a.size()));
    println(a);

    return 0;
}
