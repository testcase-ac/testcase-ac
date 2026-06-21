#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int randomValue(int lo, int hi) {
    return rnd.next(lo, hi);
}

void addTriple(vector<int>& values, int x) {
    values.push_back(x);
    values.push_back(x);
    values.push_back(x);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 12);
    vector<int> values;
    values.reserve(3 * n);

    if (mode == 0) {
        int lo = rnd.next(-20, 0);
        int hi = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            addTriple(values, randomValue(lo, hi));
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int base = randomValue(-30, 30);
            addTriple(values, base);
        }
        int pos = rnd.next(0, 3 * n - 1);
        int replacement = values[pos];
        while (replacement == values[pos]) {
            replacement = randomValue(-30, 30);
        }
        values[pos] = replacement;
    } else if (mode == 2) {
        int kinds = rnd.next(1, min(6, 3 * n));
        vector<int> pool;
        for (int i = 0; i < kinds; ++i) {
            pool.push_back(randomValue(-10, 10));
        }
        for (int i = 0; i < 3 * n; ++i) {
            values.push_back(pool[rnd.next(0, kinds - 1)]);
        }
    } else if (mode == 3) {
        vector<int> pool = {-100000, -99999, -1, 0, 1, 99999, 100000};
        for (int i = 0; i < 3 * n; ++i) {
            values.push_back(pool[rnd.next(0, int(pool.size()) - 1)]);
        }
    } else {
        int lo = rnd.next(-100, 50);
        int hi = rnd.next(lo, 100);
        for (int i = 0; i < 3 * n; ++i) {
            values.push_back(randomValue(lo, hi));
        }
    }

    shuffle(values.begin(), values.end());

    println(n);
    println(values);

    return 0;
}
