#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

pair<int, int> foldPoint(long long unfoldedX, int y, int m) {
    long long period = 2LL * m;
    int r = int(unfoldedX % period);
    if (r < 0) r += period;
    if (r > m) r = 2 * m - r;
    return {r, y};
}

bool addSensor(set<pair<int, int>>& used, vector<pair<int, int>>& sensors,
               int x, int y, int m, int maxN) {
    if ((int)sensors.size() >= maxN) return false;
    if (x <= 0 || x >= m || y <= 0 || y > 9999999) return false;
    if (!used.insert({x, y}).second) return false;
    sensors.push_back({x, y});
    return true;
}

void addRandomSensor(set<pair<int, int>>& used, vector<pair<int, int>>& sensors,
                     int m, int maxN, int yLimit) {
    for (int attempt = 0; attempt < 200 && (int)sensors.size() < maxN; ++attempt) {
        int x = rnd.next(1, m - 1);
        int y = rnd.next(1, yLimit);
        if (addSensor(used, sensors, x, y, m, maxN)) return;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = rnd.next(2, 30);
    int k = rnd.next(1, 12);
    int maxN = rnd.next(1, 24);
    int yLimit = rnd.next(10, 300);

    if (mode == 1) {
        m = rnd.next(2, 8);
        k = rnd.next(1, 20);
        maxN = rnd.next(8, 30);
    } else if (mode == 2) {
        m = rnd.any(vector<int>{2, 3, 4, 5, 10000});
        k = rnd.any(vector<int>{1, 2, 3, 1000});
        maxN = rnd.next(1, 12);
        yLimit = rnd.next(20, 500);
    } else if (mode == 3) {
        m = rnd.next(20, 80);
        k = rnd.next(5, 40);
        maxN = rnd.next(12, 40);
        yLimit = rnd.next(50, 1000);
    } else if (mode == 4) {
        m = rnd.next(2, 100);
        k = rnd.next(1, 1000);
        maxN = rnd.next(1, 35);
        yLimit = 9999999;
    }

    set<pair<int, int>> used;
    vector<pair<int, int>> sensors;

    if (rnd.next(0, 99) < 75) {
        int dx = rnd.next(1, max(2, 2 * m * min(k, 8)));
        int dy = rnd.next(1, max(2, yLimit / maxN));
        int count = rnd.next(1, min(maxN, max(1, min(k, 18))));
        for (int step = 1; step <= count; ++step) {
            long long ux = 1LL * dx * step;
            int y = dy * step;
            auto p = foldPoint(ux, y, m);
            addSensor(used, sensors, p.first, p.second, m, maxN);
        }
    }

    if (rnd.next(0, 99) < 60) {
        int sameX = rnd.next(1, m - 1);
        int count = rnd.next(1, min(maxN, 8));
        for (int i = 0; i < count; ++i) {
            int y = rnd.next(1, yLimit);
            addSensor(used, sensors, sameX, y, m, maxN);
        }
    }

    if (rnd.next(0, 99) < 50) {
        int count = rnd.next(1, min(maxN, 8));
        for (int i = 0; i < count; ++i) {
            int x = rnd.any(vector<int>{1, m - 1});
            int y = rnd.next(1, yLimit);
            addSensor(used, sensors, x, y, m, maxN);
        }
    }

    while ((int)sensors.size() < maxN) {
        int before = sensors.size();
        addRandomSensor(used, sensors, m, maxN, yLimit);
        if ((int)sensors.size() == before) break;
    }

    shuffle(sensors.begin(), sensors.end());
    println((int)sensors.size(), m, k);
    for (auto [x, y] : sensors) println(x, y);

    return 0;
}
