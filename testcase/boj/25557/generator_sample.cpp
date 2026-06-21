#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(8, 24);
    vector<tuple<int, int, int>> games;
    games.reserve(n);

    auto addGame = [&](int x, int y, int k) {
        games.emplace_back(x, y, k);
    };

    addGame(-1200, -1200, -1200);
    addGame(1200, 1200, 1200);
    addGame(-1200, 1200, rnd.any(vector<int>{-1200, -1, 0, 1, 1200}));

    while ((int)games.size() < n) {
        int mode = rnd.next(0, 5);
        int x, y, k;

        if (mode == 0) {
            x = rnd.next(-1200, 1200);
            y = x;
            k = x;
        } else if (mode == 1) {
            int len = rnd.next(1, 6);
            x = rnd.next(-1200, 1200 - len);
            y = x + len;
            k = rnd.next(x, y);
        } else if (mode == 2) {
            x = rnd.next(-10, 0);
            y = rnd.next(0, 10);
            k = rnd.next(x, y);
        } else if (mode == 3) {
            x = rnd.next(-1200, -1000);
            y = rnd.next(1000, 1200);
            k = rnd.any(vector<int>{x, y, (x + y) / 2, rnd.next(x, y)});
        } else if (mode == 4) {
            int len = rnd.next(20, 200);
            x = rnd.next(-1200, 1200 - len);
            y = x + len;
            int bias = rnd.next(0, 2);
            if (bias == 0) {
                k = rnd.next(x, min(y, x + 3));
            } else if (bias == 1) {
                k = rnd.next(max(x, y - 3), y);
            } else {
                k = rnd.next(x, y);
            }
        } else {
            x = rnd.next(-1200, 1199);
            y = rnd.next(x + 1, 1200);
            k = rnd.next(x, y);
        }

        addGame(x, y, k);
    }

    shuffle(games.begin(), games.end());

    println((int)games.size());
    for (auto [x, y, k] : games) {
        println(x, y, k);
    }

    return 0;
}
