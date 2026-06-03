#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

vector<int> makePattern(int n, int groups) {
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    vector<int> pattern(n);
    for (int rank = 0; rank < n; ++rank) {
        int bucket = rank * groups / n;
        pattern[order[rank]] = bucket;
    }
    return pattern;
}

vector<int> valuesFromPattern(const vector<int>& pattern) {
    int maxGroup = *max_element(pattern.begin(), pattern.end());
    int base = rnd.next(1, 10000 - maxGroup);
    int step = rnd.next(1, max(1, (10000 - base) / max(1, maxGroup)));

    vector<int> values(pattern.size());
    for (int i = 0; i < int(pattern.size()); ++i) {
        values[i] = base + pattern[i] * step;
    }
    return values;
}

vector<int> perturbPattern(vector<int> pattern) {
    int n = int(pattern.size());
    int changes = rnd.next(1, max(1, n / 4));
    for (int it = 0; it < changes; ++it) {
        int a = rnd.next(n);
        int b = rnd.next(n);
        swap(pattern[a], pattern[b]);
    }
    return pattern;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int m = rnd.next(2, 10);
    int n = (mode == 4 ? rnd.next(30, 100) : rnd.next(3, 25));

    vector<vector<int>> universes;

    if (mode == 0) {
        int groups = rnd.next(1, n);
        vector<int> pattern = makePattern(n, groups);
        for (int i = 0; i < m; ++i) {
            universes.push_back(valuesFromPattern(pattern));
        }
    } else if (mode == 1) {
        int groups = rnd.next(1, min(n, 5));
        vector<int> pattern = makePattern(n, groups);
        for (int i = 0; i < m; ++i) {
            universes.push_back(valuesFromPattern(i % 3 == 0 ? perturbPattern(pattern) : pattern));
        }
    } else if (mode == 2) {
        for (int i = 0; i < m; ++i) {
            vector<int> row(n);
            int start = rnd.next(1, 10000 - n + 1);
            for (int j = 0; j < n; ++j) row[j] = start + j;
            if (i % 2 == 1) reverse(row.begin(), row.end());
            if (rnd.next(2)) shuffle(row.begin(), row.end());
            universes.push_back(row);
        }
    } else if (mode == 3) {
        for (int i = 0; i < m; ++i) {
            vector<int> row(n);
            int lo = rnd.next(1, 9950);
            int hi = rnd.next(lo, min(10000, lo + rnd.next(0, 50)));
            for (int j = 0; j < n; ++j) row[j] = rnd.next(lo, hi);
            universes.push_back(row);
        }
    } else {
        int groups = rnd.next(2, min(n, 12));
        vector<int> pattern = makePattern(n, groups);
        for (int i = 0; i < m; ++i) {
            universes.push_back(valuesFromPattern(i < m / 2 ? pattern : perturbPattern(pattern)));
        }
    }

    println(m, n);
    for (const auto& row : universes) {
        println(row);
    }

    return 0;
}
