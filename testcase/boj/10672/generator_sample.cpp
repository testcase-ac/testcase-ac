#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

struct Cow {
    int x;
    int y;
    int r;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 18);
    vector<int> ys;
    for (int i = 1; i <= 80; ++i) {
        ys.push_back(i);
    }
    shuffle(ys.begin(), ys.end());

    vector<Cow> cows;
    cows.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            cows.push_back({rnd.next(-20, -1), ys[i], rnd.next(1, 30)});
        }
    } else if (mode == 1) {
        int r = rnd.next(1, 40);
        for (int i = 0; i < n; ++i) {
            cows.push_back({rnd.next(-15, -1), ys[i], r});
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int x = -rnd.next(1, 12);
            int r = rnd.next(1, 12);
            if (rnd.next(0, 2) == 0) {
                r = max(1, -x + rnd.next(-2, 2));
            }
            cows.push_back({x, ys[i], r});
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int x = (i % 3 == 0) ? -1000 : rnd.next(-1000, -1);
            int r = (i % 4 == 0) ? 1000000 : rnd.next(1, 1000000);
            int y = 1000000 - i;
            cows.push_back({x, y, r});
        }
    } else {
        n = rnd.next(8, 24);
        cows.clear();
        int baseY = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            int x = -rnd.next(1, 10);
            int r = rnd.next(1, 25);
            cows.push_back({x, baseY + i, r});
        }
        shuffle(cows.begin(), cows.end());
    }

    shuffle(cows.begin(), cows.end());
    println(static_cast<int>(cows.size()));
    for (const Cow& cow : cows) {
        println(cow.x, cow.y, cow.r);
    }

    return 0;
}
