#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct CaseData {
    int h;
    int w;
    vector<pair<int, int>> rocks;
};

static vector<pair<int, int>> chooseRocks(int h, int w, int r) {
    vector<pair<int, int>> cells;
    for (int row = 1; row <= h; ++row) {
        for (int col = 1; col <= w; ++col) {
            if ((row == 1 && col == 1) || (row == h && col == w)) {
                continue;
            }
            cells.push_back({row, col});
        }
    }

    shuffle(cells.begin(), cells.end());
    cells.resize(r);
    sort(cells.begin(), cells.end());
    return cells;
}

static CaseData makeCase(int mode) {
    int h = 1;
    int w = 1;

    if (mode == 0) {
        h = rnd.next(1, 4);
        w = rnd.next(1, 4);
    } else if (mode == 1) {
        h = rnd.next(1, 3);
        w = rnd.next(5, 20);
        if (rnd.next(2)) {
            swap(h, w);
        }
    } else if (mode == 2) {
        int stepsA = rnd.next(1, 8);
        int stepsB = rnd.next(1, 8);
        h = 1 + stepsA * 1 + stepsB * 2 + rnd.next(0, 2);
        w = 1 + stepsA * 2 + stepsB * 1 + rnd.next(0, 2);
    } else if (mode == 3) {
        h = rnd.next(40, 100);
        w = rnd.next(40, 100);
    } else {
        h = rnd.next(1, 100);
        w = rnd.next(1, 100);
    }

    int available = h * w - (h == 1 && w == 1 ? 1 : 2);
    int maxRocks = min(10, max(0, available));
    int r = 0;
    if (maxRocks > 0) {
        if (mode == 0) {
            r = rnd.next(0, min(maxRocks, 3));
        } else if (mode == 3) {
            r = rnd.next(7, maxRocks);
        } else {
            r = rnd.next(0, maxRocks);
        }
    }

    return {h, w, chooseRocks(h, w, r)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 14);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        CaseData data = makeCase(tc < 5 ? tc : rnd.next(0, 4));
        println(data.h, data.w, static_cast<int>(data.rocks.size()));
        for (const auto& rock : data.rocks) {
            println(rock.first, rock.second);
        }
    }

    return 0;
}
