#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> reachablePoint(int rCount, int uCount, int xCount) {
    int diag = rnd.next(0, xCount);
    int right = rnd.next(0, rCount);
    int up = rnd.next(0, uCount);
    return {1 + diag + right, 1 + diag + up};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 35);
    int k = rnd.next(1, 45);

    if (mode == 1) {
        n = rnd.next(1, 8);
        k = rnd.next(1, 12);
    } else if (mode == 2) {
        n = rnd.next(20, 80);
        k = rnd.next(25, 80);
    } else if (mode == 3) {
        n = rnd.next(1, 50);
        k = rnd.next(20, 70);
    } else if (mode == 4) {
        n = rnd.next(1, 25);
        k = rnd.next(10, 55);
    } else if (mode == 5) {
        n = rnd.next(70, 140);
        k = rnd.next(60, 120);
    }

    string alphabet = "RUX";
    if (mode == 1) alphabet = string(1, rnd.any(alphabet));
    if (mode == 3) alphabet = "RX";
    if (mode == 4) alphabet = "UX";

    string commands;
    commands.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 5) {
            int pick = rnd.next(0, 9);
            commands.push_back(pick < 5 ? 'X' : (pick < 7 ? 'R' : 'U'));
        } else {
            commands.push_back(rnd.any(alphabet));
        }
    }
    shuffle(commands.begin(), commands.end());

    int rCount = count(commands.begin(), commands.end(), 'R');
    int uCount = count(commands.begin(), commands.end(), 'U');
    int xCount = count(commands.begin(), commands.end(), 'X');

    set<pair<int, int>> used;
    vector<pair<int, int>> points;
    auto addPoint = [&](int x, int y) {
        if ((int)points.size() == k) return;
        x = max(1, min(500000, x));
        y = max(1, min(500000, y));
        if (used.emplace(x, y).second) points.push_back({x, y});
    };

    addPoint(1, 1);
    addPoint(1 + rCount + xCount, 1 + uCount + xCount);
    addPoint(500000, 500000);
    addPoint(1, 500000);
    addPoint(500000, 1);

    while ((int)points.size() < k) {
        int kind = rnd.next(0, 6);
        if (kind <= 2) {
            auto p = reachablePoint(rCount, uCount, xCount);
            addPoint(p.first, p.second);
        } else if (kind == 3) {
            auto p = reachablePoint(rCount, uCount, xCount);
            addPoint(p.first + rnd.next(-2, 4), p.second + rnd.next(-2, 4));
        } else if (kind == 4) {
            int base = rnd.next(1, n + 3);
            addPoint(base, rnd.next(1, n + 3));
        } else if (kind == 5) {
            addPoint(rnd.next(1, 500000), rnd.next(1, 500000));
        } else {
            int offset = rnd.next(0, 10);
            if (rnd.next(0, 1) == 0) {
                addPoint(500000 - offset, rnd.next(1, n + 10));
            } else {
                addPoint(rnd.next(1, n + 10), 500000 - offset);
            }
        }
    }

    shuffle(points.begin(), points.end());

    println(n);
    println(commands);
    println(k);
    for (auto [x, y] : points) {
        println(x, y);
    }

    return 0;
}
