#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> intervalContaining(int i, int n, int maxExtra) {
    int leftExtra = rnd.next(0, min(maxExtra, i - 1));
    int rightExtra = rnd.next(0, min(maxExtra, n - i));
    return {i - leftExtra, i + rightExtra};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, 14);
    int q = rnd.next(1, 18);

    vector<pair<int, int>> intervals(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (mode == 0) {
            intervals[i] = {i, i};
        } else if (mode == 1) {
            intervals[i] = {1, n};
        } else if (mode == 2) {
            int reach = rnd.next(1, min(3, max(n - 1, 1)));
            intervals[i] = {max(1, i - reach), min(n, i + reach)};
        } else if (mode == 3) {
            int left = rnd.next(1, i);
            int right = rnd.next(i, n);
            intervals[i] = {left, right};
        } else {
            int maxExtra = rnd.next(0, min(5, n - 1));
            intervals[i] = intervalContaining(i, n, maxExtra);
        }
    }

    vector<pair<int, int>> queries;
    for (int i = 1; i <= n && (int)queries.size() < q; ++i) {
        if (rnd.next(3) == 0) queries.push_back({i, i});
        if (rnd.next(2) == 0) queries.push_back({i, intervals[i].first});
        if (rnd.next(2) == 0) queries.push_back({i, intervals[i].second});
    }

    while ((int)queries.size() < q) {
        int u = rnd.next(1, n);
        int choice = rnd.next(4);
        int v;
        if (choice == 0) {
            v = u;
        } else if (choice == 1) {
            v = intervals[u].first;
        } else if (choice == 2) {
            v = intervals[u].second;
        } else {
            v = rnd.next(1, n);
        }
        queries.push_back({u, v});
    }
    shuffle(queries.begin(), queries.end());

    println(n, q);
    for (int i = 1; i <= n; ++i) {
        println(intervals[i].first, intervals[i].second);
    }
    for (int i = 0; i < q; ++i) {
        println(queries[i].first, queries[i].second);
    }

    return 0;
}
