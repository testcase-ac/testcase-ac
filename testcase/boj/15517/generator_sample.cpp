#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

vector<long long> makeRanks(int n) {
    vector<long long> values(n);
    int base = rnd.next(-1000000, 1000000);
    int step = rnd.next(1, 1000);
    for (int i = 0; i < n; ++i) {
        values[i] = base + 1LL * i * step;
    }
    return values;
}

vector<long long> makeBoundaryValues(int n) {
    vector<long long> pool = {
        -2000000000LL, -1999999999LL, -1000000000LL, -1LL, 0LL,
        1LL, 999999999LL, 1999999999LL, 2000000000LL,
    };
    shuffle(pool.begin(), pool.end());

    vector<long long> values;
    for (long long value : pool) {
        if ((int)values.size() == n) break;
        values.push_back(value);
    }

    set<long long> used(values.begin(), values.end());
    while ((int)values.size() < n) {
        long long value = rnd.next(-2000000000LL, 2000000000LL);
        if (used.insert(value).second) {
            values.push_back(value);
        }
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 40);
    if (mode == 5) {
        n = rnd.next(1, 12);
    }

    vector<long long> values = (mode == 5) ? makeBoundaryValues(n) : makeRanks(n);

    if (mode == 0) {
        // Increasing order.
    } else if (mode == 1) {
        reverse(values.begin(), values.end());
    } else if (mode == 2) {
        shuffle(values.begin(), values.end());
    } else if (mode == 3) {
        int swaps = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < swaps; ++i) {
            swap(values[rnd.next(n)], values[rnd.next(n)]);
        }
    } else if (mode == 4) {
        vector<long long> arranged;
        int lo = 0;
        int hi = n - 1;
        while (lo <= hi) {
            if (rnd.next(0, 1) == 0) {
                arranged.push_back(values[lo++]);
                if (lo <= hi) arranged.push_back(values[hi--]);
            } else {
                arranged.push_back(values[hi--]);
                if (lo <= hi) arranged.push_back(values[lo++]);
            }
        }
        values = arranged;
    } else {
        shuffle(values.begin(), values.end());
    }

    println(n);
    for (long long value : values) {
        println(value);
    }

    return 0;
}
