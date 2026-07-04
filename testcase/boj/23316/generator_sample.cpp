#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace {
const int kMaxSkill = 50000;

vector<int> makeValues(int n, int mode) {
    vector<int> values;
    values.reserve(n);

    if (mode == 0) {
        int base = rnd.next(0, kMaxSkill);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-2, 2);
            values.push_back(max(0, min(kMaxSkill, base + delta)));
        }
    } else if (mode == 1) {
        int lo = rnd.next(0, 100);
        int hi = rnd.next(kMaxSkill - 100, kMaxSkill);
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.next(0, 1) == 0 ? lo + rnd.next(0, 100 - lo)
                                                 : hi - rnd.next(0, kMaxSkill - hi));
        }
    } else if (mode == 2) {
        vector<int> choices = {0, 1, 2, kMaxSkill / 2, kMaxSkill - 2, kMaxSkill - 1, kMaxSkill};
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.any(choices));
        }
    } else {
        int lo = rnd.next(0, kMaxSkill);
        int hi = rnd.next(lo, kMaxSkill);
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.next(lo, hi));
        }
    }

    shuffle(values.begin(), values.end());
    return values;
}
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 3);
    int n = 1;
    if (sizeMode == 0) {
        n = rnd.next(1, 3);
    } else if (sizeMode == 1) {
        n = rnd.next(4, 10);
    } else {
        n = rnd.next(11, 25);
    }

    int aMode = rnd.next(0, 3);
    int bMode = rnd.next(0, 3);
    vector<int> a = makeValues(n, aMode);
    vector<int> b = makeValues(n, bMode);

    if (rnd.next(0, 4) == 0) {
        int shared = rnd.next(0, kMaxSkill);
        a[rnd.next(n)] = shared;
        b[rnd.next(n)] = shared;
    }

    println(n);
    for (int value : a) {
        println(value);
    }
    for (int value : b) {
        println(value);
    }

    return 0;
}
