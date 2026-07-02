#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000000000LL;

void addValue(set<long long>& values, long long x) {
    if (1 <= x && x <= LIMIT) {
        values.insert(x);
    }
}

void fillRandomDistinct(set<long long>& values, int targetSize, long long lo, long long hi) {
    while ((int)values.size() < targetSize) {
        addValue(values, rnd.next(lo, hi));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 5 ? rnd.next(60, 120) : rnd.next(1, 30));
    set<long long> values;

    if (mode == 0) {
        fillRandomDistinct(values, n, 1, 80);
    } else if (mode == 1) {
        long long start = rnd.next(1, 20);
        long long step = rnd.next(1, 15);
        for (int i = 0; (int)values.size() < n; ++i) {
            addValue(values, start + step * i);
        }
    } else if (mode == 2) {
        long long base = rnd.next(1, 25);
        for (int i = 0; (int)values.size() < n; ++i) {
            addValue(values, base + i);
            addValue(values, 2 * (base + i));
        }
    } else if (mode == 3) {
        long long x = rnd.next(1, 1000);
        while ((int)values.size() < n && x <= LIMIT) {
            addValue(values, x);
            if (x > LIMIT / 2) {
                break;
            }
            x *= 2;
        }
        fillRandomDistinct(values, n, 1, 1000000);
    } else if (mode == 4) {
        addValue(values, 1);
        addValue(values, 2);
        addValue(values, LIMIT - 1);
        addValue(values, LIMIT);
        while ((int)values.size() < n) {
            long long delta = rnd.next(0LL, 1000000LL);
            addValue(values, LIMIT - delta);
            addValue(values, rnd.next(1LL, 1000000LL));
        }
    } else {
        long long lo = rnd.next(1LL, LIMIT - 1000000000LL);
        fillRandomDistinct(values, n, lo, lo + 1000000000LL);
    }

    vector<long long> a(values.begin(), values.end());
    shuffle(a.begin(), a.end());

    println((int)a.size());
    println(a);

    return 0;
}
