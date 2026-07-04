#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> monsterNear(int hp, int goldLo, int goldHi) {
    hp = max(1, min(200, hp));
    return {hp, rnd.next(goldLo, goldHi)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(2, 6);
    println(t);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int mode = (caseIndex == 0 ? rnd.next(0, 2) : rnd.next(0, 6));
        int p = rnd.next(20, 200);
        int q = rnd.next(20, 200);
        vector<pair<int, int>> monsters;

        if (mode == 0) {
            p = rnd.next(20, 60);
            q = rnd.next(20, 60);
            int n = rnd.next(1, 5);
            for (int i = 0; i < n; ++i) {
                int hp = rnd.any(vector<int>{1, p, q, min(200, p + q - 1), min(200, p + q)});
                monsters.push_back(monsterNear(hp, 0, 1000));
            }
        } else if (mode == 1) {
            p = rnd.next(120, 200);
            q = rnd.next(20, 80);
            int n = rnd.next(3, 8);
            for (int i = 0; i < n; ++i) {
                int hp = rnd.next(max(1, p - 5), 200);
                int gold = (i % 2 == 0 ? rnd.next(900000, 1000000) : rnd.next(0, 20));
                monsters.push_back({hp, gold});
            }
        } else if (mode == 2) {
            p = rnd.next(20, 80);
            q = rnd.next(120, 200);
            int n = rnd.next(3, 8);
            for (int i = 0; i < n; ++i) {
                int hp = rnd.next(1, 200);
                int gold = (i == 0 ? 0 : rnd.next(1, 1000000));
                monsters.push_back({hp, gold});
            }
        } else if (mode == 3) {
            p = rnd.next(20, 200);
            q = p;
            int n = rnd.next(4, 10);
            for (int i = 0; i < n; ++i) {
                int turns = rnd.next(1, max(1, 200 / p + 1));
                int hp = min(200, turns * p + rnd.next(-1, 1));
                monsters.push_back(monsterNear(hp, 0, 1000000));
            }
        } else if (mode == 4) {
            p = rnd.next(20, 100);
            q = rnd.next(20, 100);
            int n = rnd.next(8, 16);
            for (int i = 0; i < n; ++i) {
                int hp = (i % 3 == 0 ? rnd.next(1, p) : rnd.next(max(1, q), 200));
                int gold = rnd.any(vector<int>{0, 1, rnd.next(2, 1000), 1000000});
                monsters.push_back({hp, gold});
            }
        } else if (mode == 5) {
            p = rnd.next(20, 200);
            q = rnd.next(20, 200);
            int n = rnd.next(12, 24);
            for (int i = 0; i < n; ++i) {
                int base = rnd.next(1, 4) * rnd.any(vector<int>{p, q});
                monsters.push_back(monsterNear(base + rnd.next(-10, 10), 0, 5000));
            }
        } else {
            p = rnd.next(20, 200);
            q = rnd.next(20, 200);
            int n = rnd.next(1, 20);
            for (int i = 0; i < n; ++i) {
                monsters.push_back({rnd.next(1, 200), rnd.next(0, 1000000)});
            }
        }

        println(p, q, (int)monsters.size());
        for (auto [hp, gold] : monsters) {
            println(hp, gold);
        }
    }

    return 0;
}
