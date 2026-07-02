#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int coordInBand(int band) {
    if (band == 0) return rnd.next(-20, 20);
    if (band == 1) return rnd.next(-1000, 1000);
    return rnd.any(vector<int>{-1000000000, -999999999, -500000000, -1, 0, 1, 500000000, 999999999, 1000000000});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<pair<int, int>> points;

    if (mode == 0) {
        n = rnd.next(1, 3);
        int x = coordInBand(rnd.next(0, 2));
        int y = coordInBand(rnd.next(0, 2));
        for (int i = 0; i < n; ++i) points.push_back({x, y});
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int y = coordInBand(rnd.next(0, 1));
        int start = rnd.next(-30, 10);
        int step = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) points.push_back({start + i * step, y});
        if (rnd.next(2)) reverse(points.begin(), points.end());
    } else if (mode == 2) {
        n = rnd.next(3, 15);
        int x = coordInBand(rnd.next(0, 1));
        int start = rnd.next(-30, 10);
        int step = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) points.push_back({x, start + i * step});
        shuffle(points.begin(), points.end());
    } else if (mode == 3) {
        n = rnd.next(4, 18);
        int clusters = rnd.next(2, 4);
        vector<pair<int, int>> centers;
        for (int i = 0; i < clusters; ++i) {
            centers.push_back({rnd.next(-25, 25), rnd.next(-25, 25)});
        }
        for (int i = 0; i < n; ++i) {
            auto center = rnd.any(centers);
            if (rnd.next(100) < 65) {
                points.push_back(center);
            } else {
                points.push_back({center.first + rnd.next(-2, 2), center.second + rnd.next(-2, 2)});
            }
        }
    } else if (mode == 4) {
        n = rnd.next(2, 14);
        for (int i = 0; i < n; ++i) {
            int band = rnd.next(0, 2);
            points.push_back({coordInBand(band), coordInBand(band)});
        }
    } else {
        n = rnd.next(5, 21);
        int baseX = rnd.next(-50, 50);
        int baseY = rnd.next(-50, 50);
        for (int i = 0; i < n; ++i) {
            int dx = rnd.next(-10, 10);
            int dy = rnd.next(-10, 10);
            if (rnd.next(100) < 25) dx = 0;
            if (rnd.next(100) < 25) dy = 0;
            points.push_back({baseX + dx, baseY + dy});
        }
    }

    println(n);
    for (auto point : points) {
        println(point.first, point.second);
    }

    return 0;
}
