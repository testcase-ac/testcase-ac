#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

long long chooseMultiplier(int mode) {
    if (mode == 0) {
        return rnd.any(vector<long long>{0, 1, 2, 3, 1000000000LL});
    }
    if (mode == 1) {
        return rnd.next(0, 12);
    }
    if (mode == 2) {
        return rnd.next(999999990, 1000000000);
    }
    return rnd.next(0, 1000000000);
}

int chooseIndex(int limit, bool preferBoundary) {
    if (preferBoundary) {
        return rnd.any(vector<int>{1, limit, rnd.next(1, limit)});
    }
    return rnd.next(1, limit);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);
    int k = rnd.next(1, 20);

    if (mode == 1) {
        n = 1;
        m = rnd.next(1, 20);
    } else if (mode == 2) {
        n = rnd.next(1, 20);
        m = 1;
    } else if (mode == 3) {
        n = rnd.any(vector<int>{999999, 1000000});
        m = rnd.next(1, 10);
    } else if (mode == 4) {
        n = rnd.next(1, 10);
        m = rnd.any(vector<int>{999999, 1000000});
    } else if (mode == 5) {
        n = rnd.next(500000, 1000000);
        m = rnd.next(500000, 1000000);
        k = rnd.next(25, 80);
    }

    vector<string> type(k);
    vector<int> index(k);
    vector<long long> multiplier(k);

    int repeatedRow = rnd.next(1, n);
    int repeatedCol = rnd.next(1, m);
    int multiplierMode = rnd.next(0, 3);
    bool preferBoundary = rnd.next(0, 1);

    for (int i = 0; i < k; ++i) {
        bool useRow = rnd.next(0, 1);
        if (mode == 1) {
            useRow = rnd.next(0, 3) == 0;
        } else if (mode == 2) {
            useRow = rnd.next(0, 3) != 0;
        }

        type[i] = useRow ? "R" : "S";
        if (useRow) {
            index[i] = (rnd.next(0, 3) == 0 ? repeatedRow : chooseIndex(n, preferBoundary));
        } else {
            index[i] = (rnd.next(0, 3) == 0 ? repeatedCol : chooseIndex(m, preferBoundary));
        }
        multiplier[i] = chooseMultiplier(multiplierMode);
    }

    if (k >= 2) {
        type[0] = "R";
        index[0] = chooseIndex(n, true);
        multiplier[0] = rnd.any(vector<long long>{0, 1, 1000000000LL});
        type[1] = "S";
        index[1] = chooseIndex(m, true);
        multiplier[1] = rnd.any(vector<long long>{0, 1, 1000000000LL});
    }

    println(n, m, k);
    for (int i = 0; i < k; ++i) {
        println(type[i], index[i], multiplier[i]);
    }

    return 0;
}
