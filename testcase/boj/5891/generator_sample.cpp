#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    int d = rnd.next(1, 1000000);
    vector<pair<int, int>> drops;

    if (mode == 0) {
        n = rnd.next(1, 8);
        d = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(0, 30);
            int y = rnd.next(0, min(1000000, max(0, d - 1)));
            drops.push_back({x, y});
        }
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        d = rnd.any(vector<int>{1, 2, 999999, 1000000});
        drops.push_back({0, 0});
        drops.push_back({1000000, 1000000});
        for (int i = 2; i < n; ++i) {
            drops.push_back({rnd.any(vector<int>{0, 1, 999999, 1000000}),
                             rnd.next(0, 1000000)});
        }
    } else if (mode == 2) {
        n = rnd.next(3, 15);
        d = rnd.next(1, 200);
        int x = rnd.next(0, 1000000);
        int baseY = rnd.next(0, 1000000 - d);
        drops.push_back({x, baseY});
        drops.push_back({x, baseY + d});
        for (int i = 2; i < n; ++i) {
            drops.push_back({x, rnd.next(max(0, baseY - 50), min(1000000, baseY + d + 50))});
        }
    } else if (mode == 3) {
        n = rnd.next(4, 18);
        d = rnd.next(2, 5000);
        int startX = rnd.next(0, 1000000 - n);
        int width = rnd.next(1, min(20, n - 1));
        int lowY = rnd.next(0, 1000000 - d);
        drops.push_back({startX, lowY});
        drops.push_back({startX + width, lowY + d + rnd.next(0, min(5000, 1000000 - lowY - d))});
        for (int i = 2; i < n; ++i) {
            int x = startX + rnd.next(0, min(40, n + 20));
            int y = rnd.next(max(0, lowY - 200), min(1000000, lowY + d + 200));
            drops.push_back({x, y});
        }
    } else if (mode == 4) {
        n = rnd.next(8, 24);
        d = rnd.next(1, 1000000);
        int centerX = rnd.next(20, 999980);
        int centerY = rnd.next(20, 999980);
        for (int i = 0; i < n; ++i) {
            int x = centerX + rnd.next(-20, 20);
            int y = centerY + rnd.next(-20, 20);
            drops.push_back({x, y});
        }
    } else {
        n = rnd.next(10, 30);
        d = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            int stripe = rnd.next(0, 2);
            int x = stripe == 0 ? rnd.next(0, 10) : rnd.next(999990, 1000000);
            int y = rnd.next(0, 1000000);
            drops.push_back({x, y});
        }
    }

    shuffle(drops.begin(), drops.end());
    println((int)drops.size(), d);
    for (const auto& drop : drops) {
        println(drop.first, drop.second);
    }

    return 0;
}
