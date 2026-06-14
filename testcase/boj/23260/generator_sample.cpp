#include "testlib.h"
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

static void addUnique(vector<int>& values, set<int>& used, int x) {
    if (1 <= x && x <= 1000000 && !used.count(x)) {
        values.push_back(x);
        used.insert(x);
    }
}

static void fillRandom(vector<int>& values, set<int>& used, int n, int lo, int hi) {
    while ((int)values.size() < n) {
        addUnique(values, used, rnd.next(lo, hi));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 1;
    int k = 1;
    vector<int> values;
    set<int> used;

    if (mode == 0) {
        n = rnd.next(1, 3);
        k = rnd.next(1, n);
        addUnique(values, used, rnd.next(1, 12));
        fillRandom(values, used, n, 1, 20);
    } else if (mode == 1) {
        n = rnd.next(4, 16);
        k = rnd.any(vector<int>{1, 2, n});
        int g = rnd.any(vector<int>{2, 3, 5, 6, 10});
        for (int i = 1; (int)values.size() < n; ++i) {
            addUnique(values, used, g * i);
        }
    } else if (mode == 2) {
        vector<int> pool = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        n = rnd.next(4, (int)pool.size());
        k = rnd.next(2, n);
        shuffle(pool.begin(), pool.end());
        for (int i = 0; i < n; ++i) {
            addUnique(values, used, pool[i]);
        }
    } else if (mode == 3) {
        n = rnd.next(8, 30);
        k = rnd.next(2, min(n, 8));
        int g = rnd.any(vector<int>{2, 3, 4, 6});
        for (int i = 1; (int)values.size() < n / 2; ++i) {
            addUnique(values, used, g * i);
        }
        fillRandom(values, used, n, 1, 120);
    } else if (mode == 4) {
        n = rnd.next(6, 20);
        k = rnd.next(max(1, n - 4), n);
        fillRandom(values, used, n, 999900, 1000000);
    } else {
        n = rnd.next(15, 45);
        k = rnd.next(1, n);
        int step = rnd.any(vector<int>{6, 12, 30});
        for (int i = 1; (int)values.size() < n / 3; ++i) {
            addUnique(values, used, step * i);
        }
        fillRandom(values, used, n, 1, 300);
    }

    shuffle(values.begin(), values.end());

    println(n, k);
    println(values);

    return 0;
}
