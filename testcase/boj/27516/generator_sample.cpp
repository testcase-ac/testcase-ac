#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

const long long MIN_COORD = -100000000LL;
const long long MAX_COORD = 100000000LL;

long long clampCoord(long long v) {
    return max(MIN_COORD, min(MAX_COORD, v));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long x = rnd.next(-1000, 1000);
    long long y = rnd.next(-1000, 1000);
    int mode = rnd.next(0, 5);
    vector<pair<long long, long long>> points;

    auto addPoint = [&](long long px, long long py) {
        px = clampCoord(px);
        py = clampCoord(py);
        if (px == x && py == y) {
            py = (py == MIN_COORD ? py + 1 : py - 1);
        }
        points.emplace_back(px, py);
    };

    if (mode == 0) {
        int groups = rnd.next(2, 5);
        for (int g = 0; g < groups; ++g) {
            int dir = rnd.any(vector<int>{-1, 1});
            int baseDx = rnd.next(1, 8);
            int drop = rnd.next(1, 20);
            int copies = rnd.next(1, 5);
            for (int i = 1; i <= copies; ++i) {
                long long dx = 1LL * baseDx * i;
                long long dy = -1LL * drop * i * i;
                addPoint(x + dir * dx, y + dy);
            }
        }
    } else if (mode == 1) {
        int n = rnd.next(6, 30);
        for (int i = 0; i < n; ++i) {
            long long px = x + rnd.next(-20, 20);
            long long py = y + rnd.next(-20, 20);
            addPoint(px, py);
            if (rnd.next(0, 3) == 0) addPoint(px, py);
        }
    } else if (mode == 2) {
        int n = rnd.next(8, 40);
        for (int i = 0; i < n; ++i) {
            long long px = (rnd.next(0, 2) == 0 ? x : x + rnd.next(-30, 30));
            long long py = y + rnd.next(-10, 30);
            addPoint(px, py);
        }
    } else if (mode == 3) {
        x = rnd.any(vector<long long>{MIN_COORD, MAX_COORD, -99999999LL, 99999999LL});
        y = rnd.any(vector<long long>{MIN_COORD, MAX_COORD, -99999999LL, 99999999LL});
        int n = rnd.next(5, 20);
        for (int i = 0; i < n; ++i) {
            long long px = rnd.any(vector<long long>{MIN_COORD, MAX_COORD, x, x + (x == MAX_COORD ? -1 : 1)});
            long long py = rnd.any(vector<long long>{MIN_COORD, MAX_COORD, y, y + (y == MAX_COORD ? -1 : 1)});
            addPoint(px, py);
        }
    } else if (mode == 4) {
        int n = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            int dir = (i % 2 == 0 ? -1 : 1);
            long long dx = rnd.next(1, 200);
            long long drop = rnd.next(1, 5000);
            addPoint(x + dir * dx, y - drop);
        }
    } else {
        int n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            addPoint(x + rnd.next(-3, 3), y + rnd.next(-3, 3));
        }
    }

    shuffle(points.begin(), points.end());
    if (points.size() > 100000) points.resize(100000);

    println(x, y);
    println((int)points.size());
    for (auto [px, py] : points) {
        println(px, py);
    }

    return 0;
}
