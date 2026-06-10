#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 25);
    vector<pair<int, int>> items;
    items.reserve(n);

    if (mode == 0) {
        int value = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            items.emplace_back(value, value);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) {
                items.emplace_back(rnd.next(0, 1000), 0);
            } else {
                items.emplace_back(0, rnd.next(0, 1000));
            }
        }
    } else if (mode == 2) {
        vector<pair<int, int>> pool = {
            {0, 0}, {0, 1000}, {1000, 0}, {1000, 1000},
            {1, 999}, {999, 1}, {1, 1}
        };
        for (int i = 0; i < n; ++i) {
            items.push_back(rnd.any(pool));
        }
    } else if (mode == 3) {
        int hi = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            items.emplace_back(rnd.next(0, hi), rnd.next(0, hi));
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int a = n == 1 ? rnd.next(0, 1000) : i * 1000 / (n - 1);
            int b = 1000 - a;
            if (rnd.next(0, 4) == 0) {
                a = rnd.next(0, 1000);
            }
            if (rnd.next(0, 4) == 0) {
                b = rnd.next(0, 1000);
            }
            items.emplace_back(a, b);
        }
    } else if (mode == 5) {
        int baseA = rnd.next(0, 1000);
        int baseB = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            int da = rnd.next(0, min(20, 1000 - baseA));
            int db = rnd.next(0, min(20, 1000 - baseB));
            items.emplace_back(baseA + da, baseB + db);
        }
    } else {
        n = rnd.next(20, 60);
        for (int i = 0; i < n; ++i) {
            items.emplace_back(rnd.next(0, 1000), rnd.next(0, 1000));
        }
    }

    shuffle(items.begin(), items.end());

    println(static_cast<int>(items.size()));
    for (const auto& item : items) {
        println(item.first, item.second);
    }

    return 0;
}
