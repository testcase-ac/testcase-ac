#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> sizes = {2, 4, 6, 8, 10, 12, 16, 20};
    int n = sizes[rnd.next((int)sizes.size())];
    int mode = rnd.next(5);
    int limit = rnd.next(0, 3) == 0 ? 1000000 : rnd.next(5, 100);

    vector<vector<int>> c(n, vector<int>(n, 0));

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                c[i][j] = c[j][i] = rnd.next(-limit, limit);
            }
        }
    } else if (mode == 1) {
        int split = n / 2;
        int same = rnd.next(-limit, limit);
        int cross = rnd.next(-limit, limit);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                bool sameGroup = (i < split) == (j < split);
                int noise = rnd.next(-3, 3);
                long long value = (sameGroup ? same : cross) + noise;
                value = max(-1000000LL, min(1000000LL, value));
                c[i][j] = c[j][i] = (int)value;
            }
        }
    } else if (mode == 2) {
        vector<int> weight(n);
        for (int i = 0; i < n; ++i) {
            weight[i] = rnd.next(-limit / 2, limit / 2);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int noise = rnd.next(-5, 5);
                long long value = (long long)weight[i] + weight[j] + noise;
                value = max(-1000000LL, min(1000000LL, value));
                c[i][j] = c[j][i] = (int)value;
            }
        }
    } else if (mode == 3) {
        int edges = rnd.next(n - 1, n * (n - 1) / 2);
        vector<pair<int, int>> pairs;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                pairs.push_back({i, j});
            }
        }
        shuffle(pairs.begin(), pairs.end());
        for (int k = 0; k < edges; ++k) {
            int value = rnd.next(0, 1) == 0 ? -limit : limit;
            int i = pairs[k].first;
            int j = pairs[k].second;
            c[i][j] = c[j][i] = value;
        }
    } else {
        int base = rnd.next(-limit, limit);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int value = base + ((i + j) % 3) - 1;
                value = max(-1000000, min(1000000, value));
                c[i][j] = c[j][i] = value;
            }
        }
        int tweaks = rnd.next(1, n);
        for (int k = 0; k < tweaks; ++k) {
            int i = rnd.next(n);
            int j = rnd.next(n);
            if (i == j) {
                continue;
            }
            if (i > j) {
                swap(i, j);
            }
            c[i][j] = c[j][i] = rnd.next(-limit, limit);
        }
    }

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());

    println(n);
    for (int i = 0; i < n; ++i) {
        vector<int> row;
        for (int j = 0; j < n; ++j) {
            row.push_back(c[order[i]][order[j]]);
        }
        println(row);
    }

    return 0;
}
