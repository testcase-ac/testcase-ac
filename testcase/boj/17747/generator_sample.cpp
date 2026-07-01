#include "testlib.h"
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int R, C;
    vector<pair<int, int>> cells;

    auto addCell = [&](int r, int c) {
        cells.push_back({r, c});
    };

    if (mode == 0) {
        R = rnd.next(2, 6);
        C = rnd.next(2, 6);
        addCell(rnd.next(1, R), rnd.next(1, C));
    } else if (mode == 1) {
        R = rnd.next(2, 10);
        C = rnd.next(2, 10);
        vector<pair<int, int>> candidates;
        for (int r = 1; r <= R; ++r) {
            candidates.push_back({r, 1});
            candidates.push_back({r, C});
        }
        for (int c = 2; c < C; ++c) {
            candidates.push_back({1, c});
            candidates.push_back({R, c});
        }
        shuffle(candidates.begin(), candidates.end());
        int n = rnd.next(1, min<int>(candidates.size(), R * C - 1));
        cells.assign(candidates.begin(), candidates.begin() + n);
    } else if (mode == 2) {
        R = rnd.next(3, 14);
        C = rnd.next(3, 14);
        int r1 = rnd.next(1, R - 1);
        int r2 = rnd.next(r1, R);
        int c1 = rnd.next(1, C - 1);
        int c2 = rnd.next(c1, C);
        for (int r = r1; r <= r2; ++r)
            for (int c = c1; c <= c2; ++c)
                addCell(r, c);
        shuffle(cells.begin(), cells.end());
        int keep = rnd.next(1, min<int>(cells.size(), R * C - 1));
        cells.resize(keep);
    } else if (mode == 3) {
        R = rnd.next(2, 7);
        C = rnd.next(2, 7);
        for (int r = 1; r <= R; ++r)
            for (int c = 1; c <= C; ++c)
                addCell(r, c);
        shuffle(cells.begin(), cells.end());
        int empty = rnd.next(1, min(4, R * C - 1));
        cells.resize(R * C - empty);
    } else if (mode == 4) {
        R = rnd.next(2, 3000);
        C = rnd.next(2, 3000);
        int n = rnd.next(1, min(40, R * C - 1));
        set<pair<int, int>> used;
        while (static_cast<int>(cells.size()) < n) {
            int r = rnd.next(1, R);
            int c = rnd.next(1, C);
            if (used.insert({r, c}).second) addCell(r, c);
        }
    } else {
        R = rnd.any(vector<int>{2, 3, 50, 3000});
        C = rnd.any(vector<int>{2, 3, 50, 3000});
        vector<pair<int, int>> anchors = {
            {1, 1},
            {1, C},
            {R, 1},
            {R, C},
            {rnd.next(1, R), rnd.next(1, C)}
        };
        shuffle(anchors.begin(), anchors.end());
        int n = rnd.next(1, min<int>(anchors.size(), R * C - 1));
        set<pair<int, int>> used;
        for (int i = 0; i < static_cast<int>(anchors.size()) && static_cast<int>(cells.size()) < n; ++i) {
            if (used.insert(anchors[i]).second) addCell(anchors[i].first, anchors[i].second);
        }
    }

    set<pair<int, int>> uniqueCells(cells.begin(), cells.end());
    cells.assign(uniqueCells.begin(), uniqueCells.end());
    shuffle(cells.begin(), cells.end());

    println(R, C);
    println(static_cast<int>(cells.size()));
    for (auto cell : cells) println(cell.first, cell.second);

    return 0;
}
