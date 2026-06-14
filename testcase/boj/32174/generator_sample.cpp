#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long randomMoveValue(int n, int mode) {
    const long long limit = 1000000000000000000LL;
    if (mode == 0) {
        return rnd.next(1, max(1, n * 2));
    }
    if (mode == 1) {
        long long base = rnd.next(0, 1000000);
        long long residue = rnd.next(0, max(0, n - 1));
        long long value = base * n + residue;
        return max(1LL, min(limit, value));
    }
    long long nearLimit = limit - rnd.next(0, 1000000);
    return max(1LL, nearLimit);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 25);
    } else if (mode == 1) {
        n = rnd.next(2, 5);
        m = rnd.next(1, 35);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        m = rnd.next(20, 80);
    } else if (mode == 3) {
        n = rnd.next(20, 100);
        m = rnd.next(30, 100);
    } else {
        n = rnd.next(2, 30);
        m = rnd.next(1, 100);
    }

    println(n, m);

    vector<int> resetTargets;
    resetTargets.push_back(0);

    for (int i = 1; i <= m; ++i) {
        int type;
        if (mode == 0) {
            type = rnd.next(1, 3);
        } else if (mode == 2) {
            type = rnd.wnext(3, 2) + 1;
        } else if (mode == 3) {
            type = rnd.next(1, 10) <= 7 ? rnd.next(1, 2) : 3;
        } else {
            type = rnd.next(1, 3);
        }

        if (type == 3) {
            int z;
            if (mode == 2 && rnd.next(1, 100) <= 70) {
                z = rnd.any(resetTargets);
            } else if (rnd.next(1, 100) <= 30) {
                z = 0;
            } else {
                z = rnd.next(0, i - 1);
            }
            println(type, z);
            resetTargets.push_back(i);
        } else {
            int valueMode = mode == 3 ? rnd.next(1, 2) : rnd.next(0, 2);
            println(type, randomMoveValue(n, valueMode));
        }
    }

    return 0;
}
