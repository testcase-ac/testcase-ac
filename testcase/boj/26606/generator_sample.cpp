#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

static void addUnique(vector<int>& values, set<int>& used, int x) {
    if (1 <= x && x <= 100 && used.insert(x).second) {
        values.push_back(x);
    }
}

static void fillRandom(vector<int>& values, set<int>& used, int target) {
    while ((int)values.size() < target) {
        addUnique(values, used, rnd.next(1, 100));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    vector<int> values;
    set<int> used;

    if (mode == 0) {
        n = rnd.next(1, 12) * 2;
        int start = rnd.next(1, 100);
        int step = rnd.next(1, 9);
        for (int i = 0; (int)values.size() < n && i < 140; ++i) {
            int x = ((start + i * step - 1) % 100) + 1;
            addUnique(values, used, x);
        }
    } else if (mode == 1) {
        n = rnd.next(2, 20) * 2;
        int base = rnd.next(11, 90);
        for (int offset = -30; offset <= 30; offset += 10) {
            addUnique(values, used, base + offset);
        }
        fillRandom(values, used, n);
    } else if (mode == 2) {
        n = rnd.next(4, 30) * 2;
        int lo = rnd.next(1, 70);
        int hi = rnd.next(lo + 15, 100);
        while ((int)values.size() < n) {
            addUnique(values, used, rnd.next(lo, hi));
            if ((int)values.size() < n) addUnique(values, used, rnd.next(1, 100));
        }
    } else if (mode == 3) {
        n = rnd.next(25, 50) * 2;
        int block = rnd.next(0, 3);
        for (int x = block + 1; x <= 100; x += 4) {
            addUnique(values, used, x);
        }
        fillRandom(values, used, n);
    } else {
        n = rnd.next(1, 50) * 2;
        fillRandom(values, used, n);
    }

    fillRandom(values, used, n);

    if (rnd.next(2) == 0) {
        sort(values.begin(), values.end());
    } else {
        shuffle(values.begin(), values.end());
    }

    vector<pair<int, int>> pairs;
    for (int i = 0; i < n; i += 2) {
        pairs.push_back({values[i], values[i + 1]});
    }

    if (rnd.next(2) == 0) {
        shuffle(pairs.begin(), pairs.end());
    }

    for (auto& p : pairs) {
        if (rnd.next(2) == 0) swap(p.first, p.second);
    }

    println(n);
    for (auto [a, b] : pairs) {
        println(a, b);
    }

    return 0;
}
