#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MAX_ID = (1 << 30) - 1;

void addUnique(vector<int>& ids, set<int>& used, int n, int value) {
    if ((int)ids.size() >= n) {
        return;
    }
    if (value < 1 || value > MAX_ID) {
        return;
    }
    if (used.insert(value).second) {
        ids.push_back(value);
    }
}

void fillRandom(vector<int>& ids, set<int>& used, int n) {
    while ((int)ids.size() < n) {
        addUnique(ids, used, n, rnd.next(1, MAX_ID));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 2);
    } else if (mode == 6) {
        n = rnd.next(100, 2000);
    } else {
        n = rnd.next(3, 24);
    }

    vector<int> ids;
    set<int> used;

    if (mode == 0) {
        addUnique(ids, used, n, rnd.any(vector<int>{1, MAX_ID, rnd.next(1, MAX_ID)}));
    } else if (mode == 1) {
        int start = rnd.next(1, 1000);
        int step = rnd.next(1, 17);
        for (int i = 0; i < n; ++i) {
            addUnique(ids, used, n, start + i * step);
        }
    } else if (mode == 2) {
        int base = 1 << rnd.next(0, 29);
        for (int i = 0; i < n; ++i) {
            addUnique(ids, used, n, base ^ rnd.next(0, min(MAX_ID, 4095)));
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int bit = 1 << rnd.next(0, 29);
            addUnique(ids, used, n, bit);
            addUnique(ids, used, n, bit - 1);
        }
    } else if (mode == 4) {
        int mask = (1 << rnd.next(8, 30)) - 1;
        for (int i = 0; i < n; ++i) {
            addUnique(ids, used, n, mask ^ rnd.next(0, min(mask, 8191)));
        }
    } else if (mode == 5) {
        int lo = rnd.next(1, MAX_ID - 20000);
        int hi = min(MAX_ID, lo + rnd.next(100, 20000));
        for (int i = 0; i < n; ++i) {
            addUnique(ids, used, n, rnd.next(lo, hi));
        }
    } else {
        for (int i = 0; i < n / 3; ++i) {
            addUnique(ids, used, n, rnd.next(1, 100000));
            addUnique(ids, used, n, MAX_ID - rnd.next(0, 100000));
            addUnique(ids, used, n, rnd.next(1, MAX_ID));
        }
    }

    fillRandom(ids, used, n);
    shuffle(ids.begin(), ids.end());

    println(n);
    for (int id : ids) {
        println(id);
    }

    return 0;
}
