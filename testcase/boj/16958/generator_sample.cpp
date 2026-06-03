#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct City {
    int special;
    int x;
    int y;
};

pair<int, int> uniquePoint(set<pair<int, int>>& used, int loX, int hiX, int loY, int hiY) {
    while (true) {
        pair<int, int> p = {rnd.next(loX, hiX), rnd.next(loY, hiY)};
        if (used.insert(p).second) return p;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 18);
    int t = rnd.next(1, 25);
    if (mode == 2) t = rnd.next(1, 4);
    if (mode == 3) t = rnd.next(20, 2000);

    vector<City> cities;
    set<pair<int, int>> used;

    for (int i = 0; i < n; ++i) {
        int special = 0;
        if (mode == 1 || mode == 2) {
            special = 1;
        } else if (mode == 3) {
            special = (i == 0 || i == n - 1 || rnd.next(0, 3) == 0);
        } else {
            special = rnd.next(0, 1);
        }

        int xLo = 0, xHi = 1000, yLo = 0, yHi = 1000;
        if (mode == 0) {
            xLo = 0;
            xHi = 20;
            yLo = 0;
            yHi = 20;
        } else if (mode == 2) {
            xLo = rnd.next(0, 5);
            xHi = xLo + 8;
            yLo = rnd.next(0, 5);
            yHi = yLo + 8;
        } else if (mode == 3) {
            if (i < n / 2) {
                xLo = 0;
                xHi = 30;
                yLo = 0;
                yHi = 30;
            } else {
                xLo = 970;
                xHi = 1000;
                yLo = 970;
                yHi = 1000;
            }
        }

        auto [x, y] = uniquePoint(used, xLo, xHi, yLo, yHi);
        cities.push_back({special, x, y});
    }

    if (mode == 0) {
        for (auto& city : cities) city.special = 0;
    } else if (rnd.next(0, 5) == 0) {
        cities[rnd.next(0, n - 1)].special = 1;
    }

    vector<pair<int, int>> queries;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            queries.push_back({i, j});
            queries.push_back({j, i});
        }
    }
    shuffle(queries.begin(), queries.end());

    int m = rnd.next(1, min<int>(30, queries.size()));
    queries.resize(m);

    println(n, t);
    for (const auto& city : cities) {
        println(city.special, city.x, city.y);
    }
    println(m);
    for (auto [a, b] : queries) {
        println(a, b);
    }

    return 0;
}
