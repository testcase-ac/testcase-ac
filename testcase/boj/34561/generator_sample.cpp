#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    int valueLimit = rnd.next(3, 18);

    vector<int> a(n);
    int pattern = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        if (pattern == 0) {
            a[i] = rnd.next(1, valueLimit);
        } else if (pattern == 1) {
            a[i] = 1 + (i % rnd.next(1, min(valueLimit, 5)));
        } else if (pattern == 2) {
            a[i] = rnd.next(1, min(valueLimit, 4));
        } else {
            a[i] = i == 0 ? rnd.next(1, valueLimit) : a[rnd.next(i)];
        }
    }

    int m = rnd.next(1, 24);
    vector<vector<int>> queries;
    queries.reserve(m);
    bool hasTypeTwo = false;

    int chainStart = rnd.next(1, valueLimit);
    int chainLength = rnd.next(2, min(valueLimit, 7));
    for (int i = 0; i + 1 < chainLength && (int)queries.size() < m; ++i) {
        queries.push_back({1, chainStart + i, chainStart + i + 1});
    }

    while ((int)queries.size() < m) {
        int mode = rnd.next(0, 9);
        if (mode < 6) {
            int x, y;
            if (mode == 0) {
                x = rnd.next(1, valueLimit);
                y = x;
            } else if (mode <= 2) {
                x = rnd.any(a);
                y = rnd.next(1, valueLimit);
            } else {
                x = rnd.next(1, valueLimit);
                y = rnd.next(1, valueLimit);
            }
            queries.push_back({1, x, y});
        } else {
            queries.push_back({2, rnd.next(1, n)});
            hasTypeTwo = true;
        }
    }

    if (!hasTypeTwo) {
        queries[rnd.next((int)queries.size())] = {2, rnd.next(1, n)};
    }

    println(n);
    println(a);
    println((int)queries.size());
    for (const auto& query : queries) {
        println(query);
    }

    return 0;
}
