#include "testlib.h"

#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

struct Brick {
    int h;
    long long l;
    long long r;
};

static bool overlaps(const Brick& a, const Brick& b) {
    return a.l < b.r && b.l < a.r;
}

static void addBrick(vector<vector<Brick>>& floors, int h, long long l, long long r) {
    assert(l < r);
    floors[h].push_back({h, l, r});
}

static vector<Brick> flattenAndCheck(vector<vector<Brick>> floors) {
    vector<Brick> bricks;
    int h = (int)floors.size() - 1;

    for (int floor = 1; floor <= h; ++floor) {
        assert(!floors[floor].empty());
        sort(floors[floor].begin(), floors[floor].end(), [](const Brick& a, const Brick& b) {
            if (a.l != b.l) {
                return a.l < b.l;
            }
            return a.r < b.r;
        });

        for (int i = 1; i < (int)floors[floor].size(); ++i) {
            assert(floors[floor][i - 1].r <= floors[floor][i].l);
        }
    }

    for (int floor = 2; floor <= h; ++floor) {
        for (const Brick& brick : floors[floor]) {
            bool supported = false;
            for (const Brick& below : floors[floor - 1]) {
                if (overlaps(brick, below)) {
                    supported = true;
                    break;
                }
            }
            assert(supported);
        }
    }

    for (int floor = 1; floor <= h; ++floor) {
        for (const Brick& brick : floors[floor]) {
            bricks.push_back(brick);
        }
    }
    return bricks;
}

static vector<Brick> makeSingleColumn(int h, long long base) {
    vector<vector<Brick>> floors(h + 1);
    long long width = rnd.next(1, 5);
    for (int floor = 1; floor <= h; ++floor) {
        addBrick(floors, floor, base, base + width);
    }
    return flattenAndCheck(floors);
}

static vector<Brick> makeSplittingSupport(int h, long long base) {
    vector<vector<Brick>> floors(h + 1);
    long long a = base;
    long long b = base + rnd.next(2, 5);
    long long c = b;
    long long d = c + rnd.next(2, 5);

    addBrick(floors, 1, a, b);
    addBrick(floors, 1, c, d);

    for (int floor = 2; floor <= h; ++floor) {
        if (floor % 2 == 0) {
            addBrick(floors, floor, a + rnd.next(0, 1), d - rnd.next(0, 1));
        } else {
            long long mid = b;
            addBrick(floors, floor, a, max(a + 1, mid));
            addBrick(floors, floor, min(d - 1, mid), d);
        }
    }
    return flattenAndCheck(floors);
}

static vector<Brick> makeEndpointTouching(int h, long long base) {
    vector<vector<Brick>> floors(h + 1);
    long long x = base;
    long long leftWidth = rnd.next(1, 4);
    long long rightWidth = rnd.next(1, 4);
    for (int floor = 1; floor <= h; ++floor) {
        addBrick(floors, floor, x, x + leftWidth);
        addBrick(floors, floor, x + leftWidth, x + leftWidth + rightWidth);
    }
    return flattenAndCheck(floors);
}

static vector<Brick> makePyramid(int h, long long base) {
    vector<vector<Brick>> floors(h + 1);
    long long left = base;
    long long right = base + 2 * h + rnd.next(2, 8);
    for (int floor = 1; floor <= h; ++floor) {
        addBrick(floors, floor, left, right);
        if (right - left > 2) {
            left += rnd.next(0, 1);
            right -= rnd.next(0, 1);
        }
    }
    return flattenAndCheck(floors);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int h = rnd.next(1, 8);
    long long base = rnd.next(2) == 0 ? 0LL : 1000000000LL - 100LL;

    vector<Brick> bricks;
    int mode = rnd.next(4);
    if (mode == 0) {
        bricks = makeSingleColumn(h, base);
    } else if (mode == 1) {
        bricks = makeSplittingSupport(max(2, h), base);
        h = max(2, h);
    } else if (mode == 2) {
        bricks = makeEndpointTouching(h, base);
    } else {
        bricks = makePyramid(h, base);
    }

    shuffle(bricks.begin(), bricks.end());

    println((int)bricks.size(), h);
    for (const Brick& brick : bricks) {
        println(brick.h, brick.l, brick.r);
    }

    return 0;
}
