#include "testlib.h"
#include <algorithm>
#include <array>
#include <vector>
using namespace std;

using Enemy = array<int, 3>;

int clampValue(int x) {
    return max(1, min(1000000, x));
}

Enemy makeEnemy(int a, int b, int c) {
    b = clampValue(b);
    c = clampValue(c);
    if (b > c) swap(b, c);
    return {clampValue(a), b, c};
}

void addCluster(vector<Enemy>& enemies, int count, int baseA, int baseB, int width) {
    for (int i = 0; i < count; ++i) {
        int a = clampValue(baseA + rnd.next(-3, 3));
        int b = clampValue(baseB + rnd.next(-4, 4));
        int c = clampValue(b + rnd.next(0, width));
        enemies.push_back(makeEnemy(a, b, c));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<Enemy> enemies;

    if (mode == 0) {
        int n = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            int x = rnd.any(vector<int>{1, 2, 999999, 1000000, rnd.next(1, 1000000)});
            enemies.push_back(makeEnemy(x, x, x));
        }
    } else if (mode == 1) {
        int n = rnd.next(4, 18);
        int sharedA = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            int b = rnd.next(1, 30);
            int c = b + rnd.next(0, 12);
            enemies.push_back(makeEnemy(rnd.next() < 0.7 ? sharedA : rnd.next(1, 30), b, c));
        }
    } else if (mode == 2) {
        int n = rnd.next(5, 20);
        int center = rnd.next(5, 60);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(0, 15);
            int b = center - rnd.next(0, 10);
            int c = center + len;
            enemies.push_back(makeEnemy(rnd.next(1, 70), b, c));
        }
    } else if (mode == 3) {
        int n = rnd.next(5, 18);
        for (int i = 0; i < n; ++i) {
            int block = i / 3;
            int b = 10 + block * 20 + rnd.next(0, 4);
            int c = b + rnd.next(0, 5);
            enemies.push_back(makeEnemy(rnd.next(1, 120), b, c));
        }
    } else if (mode == 4) {
        addCluster(enemies, rnd.next(3, 8), rnd.next(1, 20), rnd.next(1, 20), rnd.next(0, 10));
        addCluster(enemies, rnd.next(3, 8), rnd.next(40, 80), rnd.next(40, 80), rnd.next(0, 20));
        addCluster(enemies, rnd.next(1, 4), 1000000, 1, 999999);
    } else {
        int n = rnd.next(8, 40);
        int valueLimit = rnd.any(vector<int>{10, 30, 100, 1000000});
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(1, valueLimit);
            int b = rnd.next(1, valueLimit);
            int c = rnd.next(b, valueLimit);
            enemies.push_back(makeEnemy(a, b, c));
        }
    }

    shuffle(enemies.begin(), enemies.end());

    println((int)enemies.size());
    for (const auto& enemy : enemies) {
        println(enemy[0], enemy[1], enemy[2]);
    }

    return 0;
}
