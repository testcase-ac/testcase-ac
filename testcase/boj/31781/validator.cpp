#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Brick {
    int index;
    int h;
    long long l;
    long long r;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int h = inf.readInt(1, 500000, "H");
    inf.readEoln();

    vector<vector<Brick>> floors(h + 1);
    for (int i = 1; i <= n; ++i) {
        int floor = inf.readInt(1, h, "h_i");
        inf.readSpace();
        long long l = inf.readLong(0LL, 1000000000LL, "l_i");
        inf.readSpace();
        long long r = inf.readLong(0LL, 1000000000LL, "r_i");
        inf.readEoln();

        ensuref(l < r, "brick %d has l_i >= r_i: %lld >= %lld", i, l, r);
        floors[floor].push_back({i, floor, l, r});
    }

    for (int floor = 1; floor <= h; ++floor) {
        ensuref(!floors[floor].empty(), "floor %d has no bricks", floor);

        sort(floors[floor].begin(), floors[floor].end(), [](const Brick& a, const Brick& b) {
            if (a.l != b.l) {
                return a.l < b.l;
            }
            return a.r < b.r;
        });

        for (int i = 1; i < (int)floors[floor].size(); ++i) {
            const Brick& prev = floors[floor][i - 1];
            const Brick& cur = floors[floor][i];
            ensuref(prev.r <= cur.l,
                    "bricks %d and %d overlap on floor %d",
                    prev.index,
                    cur.index,
                    floor);
        }
    }

    for (int floor = 2; floor <= h; ++floor) {
        const vector<Brick>& below = floors[floor - 1];
        int j = 0;
        for (const Brick& brick : floors[floor]) {
            while (j < (int)below.size() && below[j].r <= brick.l) {
                ++j;
            }

            bool supported = j < (int)below.size() && below[j].l < brick.r;
            ensuref(supported,
                    "brick %d on floor %d is floating",
                    brick.index,
                    floor);
        }
    }

    inf.readEof();
    return 0;
}
