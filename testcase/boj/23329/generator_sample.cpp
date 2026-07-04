#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Launcher {
    int x;
    int y;
    int c;
    string d;
};

const vector<string> kDirections = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};

int randomCost() {
    int mode = rnd.next(4);
    if (mode == 0) return 0;
    if (mode == 1) return rnd.next(1, 9);
    if (mode == 2) return rnd.next(10, 2000);
    return rnd.next(190000, 200000);
}

string randomDirection() {
    return rnd.any(kDirections);
}

void addPoint(vector<Launcher>& launchers, set<pair<int, int>>& used, int x, int y) {
    if (used.insert({x, y}).second) {
        launchers.push_back({x, y, randomCost(), randomDirection()});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Launcher> launchers;
    set<pair<int, int>> used;

    int baseX = rnd.next(20, 1000);
    int baseY = rnd.next(20, 1000);
    int mode = rnd.next(5);

    if (mode == 0) {
        int n = rnd.next(2, 9);
        for (int i = 0; i < n; ++i) {
            addPoint(launchers, used, baseX + i * rnd.next(1, 4), baseY);
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 9);
        for (int i = 0; i < n; ++i) {
            addPoint(launchers, used, baseX, baseY + i * rnd.next(1, 4));
        }
    } else if (mode == 2) {
        int n = rnd.next(3, 10);
        for (int i = 0; i < n; ++i) {
            int step = i * rnd.next(1, 3);
            addPoint(launchers, used, baseX + step, baseY + step);
        }
    } else if (mode == 3) {
        int n = rnd.next(3, 10);
        for (int i = 0; i < n; ++i) {
            int step = i * rnd.next(1, 3);
            addPoint(launchers, used, baseX + step, baseY + 30 - step);
        }
    } else {
        int arms = rnd.next(1, 3);
        addPoint(launchers, used, baseX, baseY);
        for (int i = 1; i <= arms + 2; ++i) {
            addPoint(launchers, used, baseX + i, baseY);
            addPoint(launchers, used, baseX, baseY + i);
            addPoint(launchers, used, baseX + i, baseY + i);
            addPoint(launchers, used, baseX + i, baseY - i);
        }
    }

    int targetN = rnd.next(max(2, (int)launchers.size()), max(14, (int)launchers.size()));
    while ((int)launchers.size() < targetN) {
        addPoint(launchers, used, rnd.next(1, 60), rnd.next(1, 60));
    }

    shuffle(launchers.begin(), launchers.end());

    int n = launchers.size();
    int s = rnd.next(1, n);
    int e = rnd.next(1, n - 1);
    if (e >= s) ++e;

    println(n, s, e);
    for (const Launcher& launcher : launchers) {
        println(launcher.x, launcher.y, launcher.c, launcher.d);
    }

    return 0;
}
