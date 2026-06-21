#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int targetPrice;
    vector<pair<int, int>> items;

    if (mode == 0) {
        n = rnd.next(1, 4);
        targetPrice = rnd.next(1, 200);
        for (int i = 0; i < n; ++i) {
            items.push_back({rnd.next(1, 20), rnd.next(1, 3)});
        }
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        targetPrice = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            items.push_back({rnd.next(500, 10000), rnd.next(1, 3)});
        }
    } else if (mode == 2) {
        n = rnd.next(8, 25);
        targetPrice = rnd.next(100000, 1000000000);
        for (int i = 0; i < n; ++i) {
            int discount = rnd.wnext(3, 2) + 1;
            items.push_back({rnd.next(1, 30), discount});
        }
    } else if (mode == 3) {
        n = rnd.next(10, 50);
        targetPrice = rnd.next(1000, 1000000000);
        for (int i = 0; i < n; ++i) {
            int discount = (i % 3) + 1;
            int cost = (rnd.next(0, 3) == 0) ? rnd.next(1, 50) : rnd.next(1000, 10000000);
            items.push_back({cost, discount});
        }
    } else if (mode == 4) {
        n = rnd.next(2, 20);
        targetPrice = rnd.next(1, 1000000000);
        int discount = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            items.push_back({rnd.next(1, 100000), discount});
        }
    } else {
        n = 50;
        targetPrice = rnd.next(900000000, 1000000000);
        for (int i = 0; i < n; ++i) {
            int discount = rnd.next(1, 3);
            int cost = (i < 15) ? rnd.next(1, 100) : rnd.next(1000000, 10000000);
            items.push_back({cost, discount});
        }
    }

    shuffle(items.begin(), items.end());

    println(n, targetPrice);
    for (auto item : items) {
        println(item.first, item.second);
    }

    return 0;
}
