#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

using Query = tuple<int, int, int>;

int clampValue(long long value) {
    return int(min(1000000LL, max(1LL, value)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int q = rnd.next(8, 35);
    vector<Query> queries;
    queries.reserve(q);

    auto addQuery = [&](int a, int d, int x) {
        queries.emplace_back(clampValue(a), clampValue(d), clampValue(x));
    };

    addQuery(1, 1, 1);
    addQuery(1, 2, 12);
    addQuery(1, 2, 17);
    addQuery(1000000, 1000000, 1000000);

    while ((int)queries.size() < q) {
        int mode = rnd.next(0, 6);

        if (mode == 0) {
            int a = rnd.next(1, 12);
            int d = rnd.next(1, 12);
            int x = rnd.next(1, 120);
            addQuery(a, d, x);
        } else if (mode == 1) {
            int a = rnd.next(1, 1000000);
            int d = rnd.next(1, 1000000);
            int x = rnd.next(1, min(1000000, a));
            addQuery(a, d, x);
        } else if (mode == 2) {
            int a = rnd.next(1, 2000);
            int d = rnd.next(1, 2000);
            int layer = rnd.next(1, 80);
            long long before = 1LL * (layer - 1) * a + 1LL * (layer - 1) * (layer - 2) * d / 2;
            int offset = rnd.next(1, min(1000000, a + (layer - 1) * d));
            addQuery(a, d, before + offset);
        } else if (mode == 3) {
            int a = rnd.next(1, 1000000);
            int d = rnd.any(vector<int>{1, 2, 999999, 1000000});
            int x = rnd.any(vector<int>{1, 2, 999999, 1000000});
            addQuery(a, d, x);
        } else if (mode == 4) {
            int a = rnd.any(vector<int>{1, 2, 999999, 1000000});
            int d = rnd.next(1, 1000000);
            int x = rnd.next(1, 1000000);
            addQuery(a, d, x);
        } else {
            int a = rnd.next(1, 300);
            int d = rnd.next(1, 300);
            int layer = rnd.next(1, 100);
            long long end = 1LL * layer * a + 1LL * layer * (layer - 1) * d / 2;
            int delta = rnd.next(0, 3);
            addQuery(a, d, end - delta);
        }
    }

    shuffle(queries.begin(), queries.end());

    println((int)queries.size());
    for (auto [a, d, x] : queries) {
        println(a, d, x);
    }

    return 0;
}
