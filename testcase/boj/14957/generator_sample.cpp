#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

namespace {

int uniqueInRange(set<int>& used, int lo, int hi) {
    for (int attempt = 0; attempt < 200; ++attempt) {
        int value = rnd.next(lo, hi);
        if (used.insert(value).second) return value;
    }
    for (int value = lo; value <= hi; ++value) {
        if (used.insert(value).second) return value;
    }
    ensuref(false, "no unused coordinate in range");
    return lo;
}

vector<int> sortedUniqueCoordinates(int count, set<int>& used, int lo, int hi) {
    vector<int> values;
    values.reserve(count);
    for (int i = 0; i < count; ++i) {
        values.push_back(uniqueInRange(used, lo, hi));
    }
    sort(values.begin(), values.end());
    return values;
}

vector<int> ySequence(int steps, set<int>& usedY, int lo, int hi, bool increasing) {
    vector<int> y = sortedUniqueCoordinates(steps + 1, usedY, lo, hi);
    if (!increasing) reverse(y.begin(), y.end());
    return y;
}

void printStaircase(const vector<int>& x, const vector<int>& y) {
    printf("%d", y[0]);
    for (int i = 0; i < (int)x.size(); ++i) {
        printf(" %d %d", x[i], y[i + 1]);
    }
    printf("\n");
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;
    if (mode == 0) {
        n = m = 1;
    } else if (mode == 1) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 3);
    } else {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
    }

    set<int> usedX;
    set<int> usedY;
    vector<int> lx;
    vector<int> ux;

    if (mode == 2) {
        lx = sortedUniqueCoordinates(n, usedX, 0, 80);
        ux = sortedUniqueCoordinates(m, usedX, 0, 80);
    } else if (mode == 3) {
        lx = sortedUniqueCoordinates(n, usedX, 0, 200);
        ux = sortedUniqueCoordinates(m, usedX, 150, 420);
    } else if (mode == 4) {
        lx = sortedUniqueCoordinates(n, usedX, 49500, 50000);
        ux = sortedUniqueCoordinates(m, usedX, 0, 500);
    } else {
        lx = sortedUniqueCoordinates(n, usedX, 0, 50000);
        ux = sortedUniqueCoordinates(m, usedX, 0, 50000);
    }

    bool lIncreasing = rnd.next(0, 1);
    bool uIncreasing = rnd.next(0, 1);
    vector<int> ly;
    vector<int> uy;

    if (mode == 0) {
        if (rnd.next(0, 1)) {
            usedY.insert(0);
            usedY.insert(1);
            usedY.insert(49999);
            usedY.insert(50000);
            ly = {50000, 1};
            uy = {0, 49999};
        } else {
            ly = ySequence(n, usedY, 0, 12, lIncreasing);
            uy = ySequence(m, usedY, 13, 30, uIncreasing);
        }
    } else if (mode == 1) {
        ly = ySequence(n, usedY, 0, 60, lIncreasing);
        uy = ySequence(m, usedY, 0, 60, uIncreasing);
    } else if (mode == 2) {
        ly = ySequence(n, usedY, 0, 120, false);
        uy = ySequence(m, usedY, 0, 120, true);
    } else if (mode == 3) {
        ly = ySequence(n, usedY, 0, 200, true);
        uy = ySequence(m, usedY, 100, 320, true);
    } else if (mode == 4) {
        ly = ySequence(n, usedY, 49000, 50000, false);
        uy = ySequence(m, usedY, 0, 1000, true);
    } else {
        ly = ySequence(n, usedY, 0, 50000, lIncreasing);
        uy = ySequence(m, usedY, 0, 50000, uIncreasing);
    }

    println(n, m);
    printStaircase(lx, ly);
    printStaircase(ux, uy);

    return 0;
}
