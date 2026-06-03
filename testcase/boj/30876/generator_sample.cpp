#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = mode == 0 ? 1 : rnd.next(2, 25);

    vector<pair<int, int>> stations;
    set<pair<int, int>> used;

    auto addStation = [&](int x, int y) {
        if (used.insert({x, y}).second) {
            stations.push_back({x, y});
            return true;
        }
        return false;
    };

    if (n == 1) {
        addStation(rnd.next(-1000, 1000), rnd.next(-1000, 1000));
    } else {
        int minY = rnd.next(-1000, 999);
        if (mode == 2) minY = -1000;
        if (mode == 3) minY = rnd.next(-5, 5);

        int minX = rnd.next(-1000, 1000);
        addStation(minX, minY);

        if (mode == 1) {
            for (int i = 1; i < n; ++i) {
                int x = -1000 + (2000 * i) / max(1, n - 1);
                int y = minY + rnd.next(1, min(2000, 1000 - minY));
                while (!addStation(x, y)) {
                    x = rnd.next(-1000, 1000);
                    y = minY + rnd.next(1, min(2000, 1000 - minY));
                }
            }
        } else if (mode == 2) {
            for (int i = 1; i < n; ++i) {
                int x = rnd.next(-1000, 1000);
                int y = rnd.any(vector<int>{999, 1000, rnd.next(-999, 1000)});
                while (!addStation(x, y)) {
                    x = rnd.next(-1000, 1000);
                    y = rnd.next(-999, 1000);
                }
            }
        } else if (mode == 3) {
            int startX = rnd.next(-20, 20);
            for (int i = 1; i < n; ++i) {
                int x = startX + i * rnd.any(vector<int>{-2, -1, 1, 2});
                x = max(-1000, min(1000, x));
                int y = minY + 1 + (i % 7);
                while (!addStation(x, y)) {
                    x = rnd.next(-30, 30);
                    y = minY + rnd.next(1, min(20, 1000 - minY));
                }
            }
        } else {
            int highY = minY + rnd.next(1, min(50, 1000 - minY));
            for (int i = 1; i < n; ++i) {
                int x = rnd.next(-50, 50);
                int y = rnd.next() < 0.45 ? highY : minY + rnd.next(1, min(80, 1000 - minY));
                while (!addStation(x, y)) {
                    x = rnd.next(-1000, 1000);
                    y = minY + rnd.next(1, min(2000, 1000 - minY));
                }
            }
        }

        shuffle(stations.begin(), stations.end());
    }

    println((int)stations.size());
    for (auto [x, y] : stations) {
        println(x, y);
    }

    return 0;
}
