#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

struct Op { int t, x, y; };

int pickX(int t) {
    if (t == 3) return rnd.next(0, 2);
    return rnd.next(0, 3);
}
int pickY(int t) {
    if (t == 2) return rnd.next(0, 2);
    return rnd.next(0, 3);
}

int pickXBiased(int t) {
    int hi = (t == 3) ? 2 : 3;
    // 50% uniform, 50% biased toward edges (either low or high)
    if (rnd.next(0, 1) == 0) return rnd.next(0, hi);
    int bias = rnd.any(vector<int>{-2, -1, 1, 2});
    return rnd.wnext(hi + 1, bias);
}
int pickYBiased(int t) {
    int hi = (t == 2) ? 2 : 3;
    if (rnd.next(0, 1) == 0) return rnd.next(0, hi);
    int bias = rnd.any(vector<int>{-2, -1, 1, 2});
    return rnd.wnext(hi + 1, bias);
}

void addExample(vector<Op>& ops, int id) {
    // Examples from the statement
    if (id == 1) {
        ops.push_back({1,1,1});
    } else if (id == 2) {
        ops.push_back({1,1,1});
        ops.push_back({2,3,0});
    } else if (id == 3) {
        ops.push_back({1,1,1});
        ops.push_back({2,3,0});
        ops.push_back({3,2,2});
        ops.push_back({3,2,3});
    } else if (id == 4) {
        ops.push_back({1,1,1});
        ops.push_back({2,3,0});
        ops.push_back({3,2,2});
        ops.push_back({3,2,3});
        ops.push_back({3,1,3});
    } else if (id == 5) {
        ops.push_back({1,1,1});
        ops.push_back({2,3,0});
        ops.push_back({3,2,2});
        ops.push_back({3,2,3});
        ops.push_back({3,1,3});
        ops.push_back({2,0,0});
    } else if (id == 6) {
        ops.push_back({1,1,1});
        ops.push_back({2,3,0});
        ops.push_back({3,2,2});
        ops.push_back({3,2,3});
        ops.push_back({3,1,3});
        ops.push_back({2,0,0});
        ops.push_back({3,2,0});
    } else if (id == 7) {
        ops.push_back({1,1,1});
        ops.push_back({2,3,0});
        ops.push_back({3,2,2});
        ops.push_back({3,2,3});
        ops.push_back({3,1,3});
        ops.push_back({2,0,0});
        ops.push_back({3,2,0});
        ops.push_back({3,1,2});
    }
}

void addRandomOps(vector<Op>& ops, int cnt) {
    vector<int> pool = {1,1,1,2,2,3,3};
    for (int i = 0; i < cnt; ++i) {
        int t = rnd.any(pool);
        int x = pickXBiased(t);
        int y = pickYBiased(t);
        // Ensure boundaries for t=2 and t=3
        if (t == 2) y = min(y, 2);
        if (t == 3) x = min(x, 2);
        ops.push_back({t, x, y});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Op> ops;
    int mode = rnd.next(0, 99);

    if (mode < 50) {
        // Heavy interaction example from the statement (Example 7), plus some random noise
        addExample(ops, 7);
        int extra = rnd.next(0, 5);
        addRandomOps(ops, extra);
    } else if (mode < 70) {
        // One of Examples 1..6 plus some randoms
        int id = rnd.next(1, 6);
        addExample(ops, id);
        int extra = rnd.next(0, 5);
        addRandomOps(ops, extra);
    } else if (mode < 85) {
        // Structured small patterns
        int pattern = rnd.next(0, 2);
        if (pattern == 0) {
            // Horizontal dominos across selected rows
            vector<int> rows = {0,1,2,3};
            shuffle(rows.begin(), rows.end());
            int take = rnd.next(2, 4);
            rows.resize(take);
            for (int r : rows) {
                int segments = rnd.next(1, 3);
                for (int s = 0; s < segments; ++s) {
                    int y = rnd.next(0, 2);
                    ops.push_back({2, r, y});
                }
                if (rnd.next(0,1)) ops.push_back({1, r, rnd.next(0,3)});
            }
        } else if (pattern == 1) {
            // Vertical dominos across selected columns
            vector<int> cols = {0,1,2,3};
            shuffle(cols.begin(), cols.end());
            int take = rnd.next(2, 4);
            cols.resize(take);
            for (int c : cols) {
                int segments = rnd.next(1, 3);
                for (int s = 0; s < segments; ++s) {
                    int x = rnd.next(0, 2);
                    ops.push_back({3, x, c});
                }
                if (rnd.next(0,1)) ops.push_back({1, rnd.next(0,3), c});
            }
        } else {
            // Corner and single fills
            vector<pair<int,int>> cells;
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    cells.push_back({i,j});
            shuffle(cells.begin(), cells.end());
            int take = rnd.next(4, 12);
            for (int i = 0; i < take; ++i) {
                auto [x,y] = cells[i];
                ops.push_back({1, x, y});
            }
            // Add a couple of edge dominos
            if (rnd.next(0,1)) ops.push_back({2, rnd.next(0,3), rnd.next(0,2)});
            if (rnd.next(0,1)) ops.push_back({3, rnd.next(0,2), rnd.next(0,3)});
        }
    } else {
        // Pure random, but biased toward edges and with varied N
        int N = rnd.wnext(20, rnd.next(0, 3)) + 1; // 1..20
        addRandomOps(ops, N);
    }

    println((int)ops.size());
    for (auto &op : ops) {
        println(op.t, op.x, op.y);
    }
    return 0;
}
