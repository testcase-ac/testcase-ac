#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

static vector<int> randomGraphDegrees(int n) {
    vector<int> d(n, 0);
    int style = rnd.next(0, 3);

    if (style == 0) {
        double p = rnd.next(0.05, 0.85);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < p) {
                    ++d[i];
                    ++d[j];
                }
            }
        }
    } else if (style == 1) {
        int center = rnd.next(n);
        int leaves = rnd.next(0, n - 1);
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end());
        for (int v : order) {
            if (v == center) continue;
            if (leaves-- <= 0) break;
            ++d[center];
            ++d[v];
        }
    } else if (style == 2) {
        int k = rnd.next(1, n);
        vector<int> chosen(n);
        iota(chosen.begin(), chosen.end(), 0);
        shuffle(chosen.begin(), chosen.end());
        chosen.resize(k);
        for (int i = 0; i < k; ++i) {
            for (int j = i + 1; j < k; ++j) {
                ++d[chosen[i]];
                ++d[chosen[j]];
            }
        }
    } else {
        int edges = rnd.next(0, n * (n - 1) / 2);
        vector<pair<int, int>> all;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                all.push_back({i, j});
            }
        }
        shuffle(all.begin(), all.end());
        for (int i = 0; i < edges; ++i) {
            ++d[all[i].first];
            ++d[all[i].second];
        }
    }

    return d;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> values;

    if (mode == 0) {
        n = rnd.next(2, 12);
        values = randomGraphDegrees(n);
        values.push_back(rnd.next(0, n - 1));
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        values = randomGraphDegrees(n);
        int copyFrom = rnd.next(n);
        values.push_back(values[copyFrom]);
    } else if (mode == 2) {
        n = rnd.next(2, 16);
        int lo = rnd.next(0, n - 1);
        int hi = rnd.next(lo, n - 1);
        for (int i = 0; i <= n; ++i) {
            values.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 3) {
        n = rnd.next(2, 18);
        int fill = rnd.next(0, 1) ? 0 : n - 1;
        values.assign(n + 1, fill);
        int changes = rnd.next(0, min(n + 1, 4));
        for (int i = 0; i < changes; ++i) {
            values[rnd.next(n + 1)] = rnd.next(0, n - 1);
        }
    } else if (mode == 4) {
        n = rnd.next(2, 20);
        values = randomGraphDegrees(n);
        int idx = rnd.next(n);
        values[idx] = rnd.next(0, n - 1);
        values.push_back(rnd.next(0, n - 1));
    } else {
        n = rnd.next(450, 500);
        values = randomGraphDegrees(n);
        values.push_back(rnd.next(0, n - 1));
    }

    shuffle(values.begin(), values.end());

    println(n);
    for (int x : values) {
        println(x);
    }

    return 0;
}
