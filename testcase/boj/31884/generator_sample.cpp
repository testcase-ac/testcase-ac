#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> queries;
    int mode = rnd.next(0, 4);
    int q = rnd.next(1, 80);

    auto add = [&](int type, int x) {
        queries.push_back({type, x});
    };

    if (mode == 0) {
        int base = rnd.next(-20, 20);
        for (int i = 0; i < q; ++i) {
            int type = rnd.next(1, 3);
            int x = base + rnd.next(-5, 8);
            add(type, x);
        }
    } else if (mode == 1) {
        vector<int> anchors = {
            -1000000000, -999999999, -1000000, -7, -1, 0, 1, 7,
            1000000, 999999997, 999999998, 999999999, 1000000000
        };
        for (int i = 0; i < q; ++i) {
            int type = rnd.next(1, 3);
            int x = rnd.any(anchors);
            if (rnd.next(0, 3) == 0) {
                x = max(-1000000000, min(1000000000, x + rnd.next(-3, 3)));
            }
            add(type, x);
        }
    } else if (mode == 2) {
        int x = rnd.next(-100, 100);
        for (int i = 0; i < q; ++i) {
            x = max(-1000000000, min(1000000000, x + rnd.next(-4, 4)));
            int type = rnd.next(0, 99) < 70 ? rnd.next(1, 2) : 3;
            add(type, x);
        }
    } else if (mode == 3) {
        int base = rnd.next(-1000000000, 999999996);
        for (int i = 0; i < q; ++i) {
            int type = rnd.next(1, 3);
            int x = base + rnd.next(0, 4);
            add(type, x);
        }
    } else {
        for (int i = 0; i < q; ++i) {
            int type = rnd.next(0, 99) < 45 ? 3 : rnd.next(1, 2);
            int span = rnd.any(vector<int>{10, 1000, 1000000000});
            int x = rnd.next(-span, span);
            add(type, x);
        }
    }

    bool hasType3 = false;
    for (const auto& query : queries) {
        hasType3 = hasType3 || query.first == 3;
    }
    if (!hasType3) {
        queries[rnd.next(static_cast<int>(queries.size()))].first = 3;
    }

    println(static_cast<int>(queries.size()));
    for (const auto& query : queries) {
        println(query.first, query.second);
    }

    return 0;
}
