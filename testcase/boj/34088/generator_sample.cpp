#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    vector<int> values;
    set<int> used;

    auto addValue = [&](int x) {
        if (1 <= x && x <= 1000000000 && used.insert(x).second) {
            values.push_back(x);
        }
    };

    if (mode == 0) {
        n = rnd.next(1, 4);
        while ((int)values.size() < n) {
            addValue(rnd.next(1, 30));
        }
    } else if (mode == 1) {
        n = rnd.next(5, 14);
        int k = rnd.next(2, 12);
        int r = rnd.next(1, k);
        for (int i = 0; i < n; ++i) {
            addValue(r + k * i);
        }
    } else if (mode == 2) {
        n = rnd.next(6, 16);
        int k = rnd.next(2, 20);
        int strongResidue = rnd.next(0, k - 1);
        int strongCount = rnd.next(3, n);
        for (int i = 0; i < strongCount; ++i) {
            addValue(strongResidue + 1 + k * rnd.next(0, 40));
        }
        while ((int)values.size() < n) {
            addValue(rnd.next(1, 300));
        }
    } else if (mode == 3) {
        n = rnd.next(8, 18);
        int base = rnd.next(1, 40);
        int step = rnd.next(2, 50);
        for (int i = 0; i < n; ++i) {
            addValue(base + step * i);
        }
    } else if (mode == 4) {
        n = rnd.next(5, 15);
        while ((int)values.size() < n) {
            int x = rnd.next(999999850, 1000000000);
            addValue(x);
        }
    } else {
        n = rnd.next(7, 18);
        int cluster = rnd.next(1, 100);
        for (int i = 0; i < n / 2; ++i) {
            addValue(cluster + i);
        }
        while ((int)values.size() < n) {
            addValue(rnd.next(1, 500));
        }
    }

    while ((int)values.size() < n) {
        addValue(rnd.next(1, 1000));
    }

    shuffle(values.begin(), values.end());
    println((int)values.size());
    println(values);
    return 0;
}
