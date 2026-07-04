#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int p_lr = rnd.next(1, 30);
    int p_j = rnd.next(1, 30);
    vector<pair<int, int>> money;
    set<pair<int, int>> used;

    auto addMoney = [&](int x, int y) {
        if (x < -1000000000 || x > 1000000000 || y < 1 || y > 1000000000) {
            return false;
        }
        if (!used.insert({x, y}).second) {
            return false;
        }
        money.push_back({x, y});
        return true;
    };

    if (mode == 0) {
        n = 1;
        p_lr = rnd.any(vector<int>{1, 2, 100000});
        p_j = rnd.any(vector<int>{1, 3, 100000});
        int x = rnd.any(vector<int>{-1000000000, -20, -1, 0, 1, 20, 1000000000});
        int y = rnd.any(vector<int>{1, 2, 30, 1000000000});
        addMoney(x, y);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        int y = rnd.next(1, 12);
        int center = rnd.next(-5, 5);
        for (int i = 0; (int)money.size() < n && i < 100; ++i) {
            addMoney(center + rnd.next(-8, 8), y);
        }
    } else if (mode == 2) {
        n = rnd.next(3, 16);
        int y = rnd.next(1, 4);
        int x = rnd.next(-3, 3);
        for (int i = 0; i < n; ++i) {
            x += rnd.next(-1, 1);
            y += rnd.next(0, 2);
            if (!addMoney(x + rnd.next(-1, 1), y)) {
                addMoney(x + i + 2, y);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(4, 18);
        int base_y = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int y = base_y + rnd.next(0, 5);
            int x = rnd.next(-12, 12);
            if (!addMoney(x, y)) {
                addMoney(x + 30 + i, y);
            }
        }
    } else if (mode == 4) {
        n = rnd.next(3, 12);
        p_lr = rnd.next(99980, 100000);
        p_j = rnd.next(1, 5);
        int base_x = rnd.any(vector<int>{-1000000000 + 30, 999999950, rnd.next(-20, 20)});
        int base_y = rnd.any(vector<int>{1, 1000000000 - 30, rnd.next(10, 40)});
        for (int i = 0; i < n; ++i) {
            addMoney(base_x + rnd.next(-20, 20), base_y + rnd.next(0, 20));
        }
    } else {
        n = rnd.next(5, 20);
        p_lr = rnd.next(1, 100000);
        p_j = rnd.next(1, 100000);
        for (int i = 0; (int)money.size() < n && i < 200; ++i) {
            int y = rnd.next(1, 25);
            int spread = rnd.next(0, 20);
            int x = rnd.next(-spread, spread);
            addMoney(x, y);
        }
    }

    while ((int)money.size() < n) {
        addMoney((int)money.size() + 100, rnd.next(1, 100));
    }

    shuffle(money.begin(), money.end());

    println((int)money.size(), p_lr, p_j);
    for (auto [x, y] : money) {
        println(x, y);
    }

    return 0;
}
