#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int nextSize(int lo, int hi) {
    return rnd.next(lo, hi);
}

vector<int> makeStrictlyIncreasing(int n, int lo, int hi) {
    vector<int> values;
    values.reserve(n);

    int cur = lo;
    for (int i = 0; i < n; ++i) {
        int remaining = n - i - 1;
        int upper = hi - remaining;
        cur = rnd.next(cur, upper);
        values.push_back(cur);
        ++cur;
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    vector<int> boats;

    if (mode == 0) {
        boats.push_back(nextSize(1, 100000));
    } else if (mode == 1) {
        int n = rnd.next(2, 20);
        int x = nextSize(1, 100000);
        boats.assign(n, x);
    } else if (mode == 2) {
        int n = rnd.next(3, 30);
        int small = nextSize(1, 200);
        int large = nextSize(small + 1, 100000);
        boats.assign(rnd.next(2, n - 1), small);
        while ((int)boats.size() < n) {
            boats.push_back(nextSize(small + 1, large));
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 40);
        vector<int> bases = makeStrictlyIncreasing(rnd.next(2, 6), 1, 1000);
        for (int i = 0; i < n; ++i) {
            boats.push_back(rnd.any(bases));
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 25);
        boats = makeStrictlyIncreasing(n, 1, 100000);
    } else if (mode == 5) {
        int n = rnd.next(2, 30);
        int start = rnd.next(99900, 100000 - n + 1);
        for (int i = 0; i < n; ++i) {
            boats.push_back(start + i);
        }
    } else {
        int n = rnd.next(3, 18);
        int base = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int exponent = rnd.next(0, 12);
            int value = base;
            for (int j = 0; j < exponent && value <= 50000; ++j) {
                value *= 2;
            }
            boats.push_back(min(value, 100000));
        }
    }

    shuffle(boats.begin(), boats.end());

    println((int)boats.size());
    println(boats);

    return 0;
}
