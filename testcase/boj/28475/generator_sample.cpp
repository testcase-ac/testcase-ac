#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int shifted(int x, int delta) {
    return (x + delta + 8) % 8;
}

int anyOf(const vector<int>& values) {
    return values[rnd.next(0, static_cast<int>(values.size()) - 1)];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 30);
    int m = rnd.next(1, 60);
    vector<int> a(n + 1);

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        int cur = rnd.next(0, 7);
        for (int i = 1; i <= n; ++i) {
            a[i] = cur;
            if (i < n) cur = shifted(cur, anyOf({2, 6}));
        }
    } else if (mode == 1) {
        int cur = rnd.next(0, 7);
        for (int i = 1; i <= n; ++i) {
            a[i] = cur;
            if (i < n) cur = shifted(cur, anyOf({0, 1, 3, 4, 5, 7}));
        }
    } else if (mode == 2) {
        int value = rnd.next(0, 7);
        for (int i = 1; i <= n; ++i) a[i] = value;
    } else {
        int maxValue = rnd.next(0, 7);
        for (int i = 1; i <= n; ++i) a[i] = rnd.next(0, maxValue);
    }

    vector<int> initial(a.begin() + 1, a.end());
    vector<vector<int>> queries;
    bool hasTypeTwo = false;
    int queryBias = rnd.next(0, 3);
    for (int i = 0; i < m; ++i) {
        bool makeAsk = !hasTypeTwo && i == m - 1;
        if (!makeAsk) makeAsk = rnd.next(0, 99) < (queryBias == 0 ? 70 : 45);

        if (makeAsk) {
            hasTypeTwo = true;
            int l, r;
            int rangeMode = rnd.next(0, 3);
            if (rangeMode == 0) {
                l = rnd.next(1, n - 1);
                r = l + 1;
            } else if (rangeMode == 1) {
                l = 1;
                r = n;
            } else {
                l = rnd.next(1, n - 1);
                r = rnd.next(l + 1, min(n, l + rnd.next(1, 8)));
            }
            queries.push_back({2, l, r});
        } else {
            int posMode = rnd.next(0, 3);
            int pos;
            if (posMode == 0) {
                pos = anyOf({1, n});
            } else if (posMode == 1) {
                pos = rnd.next(1, min(n, 4));
            } else {
                pos = rnd.next(1, n);
            }

            int valueMode = rnd.next(0, 3);
            int value;
            if (valueMode == 0) {
                value = shifted(a[pos], anyOf({2, 6}));
            } else if (valueMode == 1) {
                value = shifted(a[pos], anyOf({1, 3, 5, 7}));
            } else {
                value = rnd.next(0, 7);
            }
            a[pos] = value;
            queries.push_back({1, pos, value});
        }
    }

    println(n, m);
    println(initial);
    for (const auto& query : queries) println(query);

    return 0;
}
