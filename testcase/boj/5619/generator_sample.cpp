#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

void addValue(vector<int>& values, set<int>& used, int value) {
    if (1 <= value && value <= 10000 && used.insert(value).second) {
        values.push_back(value);
    }
}

void fillRandom(vector<int>& values, set<int>& used, int targetN, int lo, int hi) {
    while ((int)values.size() < targetN) {
        addValue(values, used, rnd.next(lo, hi));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(3, 18);

    vector<int> values;
    set<int> used;

    if (mode == 0) {
        fillRandom(values, used, n, 1, 200);
    } else if (mode == 1) {
        vector<int> bases = {1, 10, 11, 100, 101, 110, 111, 1000, 1001, 10000};
        shuffle(bases.begin(), bases.end());
        for (int value : bases) {
            if ((int)values.size() == n) break;
            addValue(values, used, value);
        }
        fillRandom(values, used, n, 1, 1200);
    } else if (mode == 2) {
        int firstDigit = rnd.next(1, 9);
        vector<int> candidates;
        for (int value = 1; value <= 10000; ++value) {
            int x = value;
            while (x >= 10) x /= 10;
            if (x == firstDigit) candidates.push_back(value);
        }
        shuffle(candidates.begin(), candidates.end());
        for (int value : candidates) {
            if ((int)values.size() == n) break;
            addValue(values, used, value);
        }
    } else if (mode == 3) {
        vector<int> edges = {1, 2, 3, 9, 10, 99, 100, 999, 1000, 9998, 9999, 10000};
        shuffle(edges.begin(), edges.end());
        for (int value : edges) {
            if ((int)values.size() == n) break;
            addValue(values, used, value);
        }
        fillRandom(values, used, n, 9500, 10000);
    } else {
        int start = rnd.next(1, 30);
        int step = rnd.next(1, 17);
        for (int i = 0; (int)values.size() < n && i < 60; ++i) {
            addValue(values, used, start + i * step);
        }
        fillRandom(values, used, n, 1, 500);
    }

    shuffle(values.begin(), values.end());

    println((int)values.size());
    for (int value : values) {
        println(value);
    }

    return 0;
}
