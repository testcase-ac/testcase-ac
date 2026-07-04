#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

struct Shark {
    int r, c, s, d, z;
};

static bool addShark(vector<Shark>& sharks, set<pair<int, int>>& usedPos,
                     int r, int c, int s, int d, int z) {
    if (usedPos.count({r, c})) return false;
    usedPos.insert({r, c});
    sharks.push_back({r, c, s, d, z});
    return true;
}

static int periodForDirection(int R, int C, int d) {
    if (d <= 2) return 2 * R - 2;
    return 2 * C - 2;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int R = rnd.next(2, 12);
    int C = rnd.next(2, 12);
    vector<Shark> sharks;
    set<pair<int, int>> usedPos;

    if (mode == 0) {
        R = rnd.next(2, 100);
        C = rnd.next(2, 100);
    } else if (mode == 1) {
        R = rnd.next(2, 4);
        C = rnd.next(2, 5);
        int z = 1;
        for (int r = 1; r <= R; ++r) {
            for (int c = 1; c <= C; ++c) {
                int d = rnd.next(1, 4);
                int s = rnd.next(0, 3 * periodForDirection(R, C, d));
                addShark(sharks, usedPos, r, c, s, d, z++);
            }
        }
    } else if (mode == 2) {
        R = rnd.next(3, 8);
        C = rnd.next(3, 8);
        int row = rnd.next(1, R);
        int baseZ = rnd.next(1, 9000);
        addShark(sharks, usedPos, row, 1, 1, 3, baseZ);
        addShark(sharks, usedPos, row, 3, 1, 4, baseZ + 1);
        addShark(sharks, usedPos, 1, C, 0, rnd.next(1, 4), baseZ + 2);
        if (R >= 5) {
            addShark(sharks, usedPos, R, rnd.next(1, C), rnd.next(2, 12), 1, baseZ + 3);
        }
    } else if (mode == 3) {
        R = rnd.next(2, 10);
        C = rnd.next(2, 10);
        int z = 1;
        vector<pair<int, int>> cells;
        for (int r = 1; r <= R; ++r) {
            cells.push_back({r, 1});
            cells.push_back({r, C});
        }
        for (int c = 2; c < C; ++c) {
            cells.push_back({1, c});
            cells.push_back({R, c});
        }
        shuffle(cells.begin(), cells.end());
        int take = rnd.next(1, min<int>(cells.size(), 18));
        for (int i = 0; i < take; ++i) {
            int d = rnd.next(1, 4);
            int period = periodForDirection(R, C, d);
            int s = rnd.next(0, 5) == 0 ? 1000 : rnd.next(0, 2 * period + 7);
            addShark(sharks, usedPos, cells[i].first, cells[i].second, s, d, z++);
        }
    } else if (mode == 4) {
        R = rnd.next(6, 18);
        C = rnd.next(6, 18);
        int limit = min(R * C, rnd.next(15, 45));
        vector<pair<int, int>> cells;
        for (int r = 1; r <= R; ++r)
            for (int c = 1; c <= C; ++c)
                cells.push_back({r, c});
        shuffle(cells.begin(), cells.end());
        vector<int> sizes;
        for (int z = 1; z <= 10000; ++z) sizes.push_back(z);
        shuffle(sizes.begin(), sizes.end());
        for (int i = 0; i < limit; ++i) {
            int d = rnd.next(1, 4);
            int speedBias = rnd.next(0, 3);
            int s = speedBias == 0 ? 0 : (speedBias == 1 ? rnd.next(1, 20) : rnd.next(900, 1000));
            addShark(sharks, usedPos, cells[i].first, cells[i].second, s, d, sizes[i]);
        }
    } else {
        R = rnd.next(2, 100);
        C = rnd.next(2, 100);
        int limit = rnd.next(1, min(R * C, 120));
        vector<pair<int, int>> cells;
        for (int r = 1; r <= R; ++r)
            for (int c = 1; c <= C; ++c)
                cells.push_back({r, c});
        shuffle(cells.begin(), cells.end());
        int z = rnd.next(1, 10000 - limit + 1);
        for (int i = 0; i < limit; ++i) {
            int d = rnd.next(1, 4);
            int period = periodForDirection(R, C, d);
            int s = rnd.next(0, 4) == 0 ? 1000 : rnd.next(0, min(1000, 4 * period));
            addShark(sharks, usedPos, cells[i].first, cells[i].second, s, d, z + i);
        }
    }

    shuffle(sharks.begin(), sharks.end());
    println(R, C, int(sharks.size()));
    for (const Shark& shark : sharks) {
        println(shark.r, shark.c, shark.s, shark.d, shark.z);
    }

    return 0;
}
