#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

bool inside(int x, int y) {
    return (0 <= x && x < 8 && 0 <= y && y < 8);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // 20% chance: output one of the sample tests exactly
    if (rnd.next(0, 4) == 0) {
        int which = rnd.next(1, 6);
        if (which == 1) {
            println("A1", "A2", 5);
            println("B");
            println("L");
            println("LB");
            println("RB");
            println("LT");
        } else if (which == 2) {
            println("A1", "H8", 1);
            println("T");
        } else if (which == 3) {
            println("A1", "A2", 1);
            println("T");
        } else if (which == 4) {
            println("A1", "A2", 2);
            println("T");
            println("R");
        } else if (which == 5) {
            println("A8", "B7", 18);
            for (int i = 0; i < 18; ++i) println("RB");
        } else { // which == 6
            println("C1", "B1", 3);
            println("L");
            println("T");
            println("LB");
        }
        return 0;
    }

    // Direction mappings
    vector<string> moveNames = {"R", "L", "B", "T", "RT", "LT", "RB", "LB"};
    int dx[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    int dy[8] = {0, 0, -1, 1, 1, 1, -1, -1};

    // Choose N with variety
    int N;
    int nPattern = rnd.next(0, 4);
    if (nPattern == 0) N = 1;
    else if (nPattern == 1) N = rnd.next(2, 5);
    else if (nPattern == 2) N = rnd.next(6, 15);
    else if (nPattern == 3) N = rnd.next(16, 30);
    else N = rnd.next(31, 50);

    // Choose initial positions for king and stone
    int kx0, ky0, sx0, sy0;
    int posPattern = rnd.next(0, 3);
    if (posPattern == 0) {
        // Fully random distinct positions
        kx0 = rnd.next(0, 7);
        ky0 = rnd.next(0, 7);
        do {
            sx0 = rnd.next(0, 7);
            sy0 = rnd.next(0, 7);
        } while (sx0 == kx0 && sy0 == ky0);
    } else if (posPattern == 1) {
        // Stone adjacent to king
        kx0 = rnd.next(0, 7);
        ky0 = rnd.next(0, 7);
        vector<pair<int,int>> neigh;
        for (int dx0 = -1; dx0 <= 1; ++dx0)
            for (int dy0 = -1; dy0 <= 1; ++dy0)
                if (dx0 != 0 || dy0 != 0) {
                    int x = kx0 + dx0;
                    int y = ky0 + dy0;
                    if (inside(x, y)) neigh.push_back({x, y});
                }
        auto p = rnd.any(neigh);
        sx0 = p.first;
        sy0 = p.second;
    } else if (posPattern == 2) {
        // Same row/column/diagonal
        kx0 = rnd.next(0, 7);
        ky0 = rnd.next(0, 7);
        int alignType = rnd.next(0, 2);
        vector<pair<int,int>> cand;
        if (alignType == 0) { // same row
            for (int x = 0; x < 8; ++x)
                if (x != kx0) cand.push_back({x, ky0});
        } else if (alignType == 1) { // same column
            for (int y = 0; y < 8; ++y)
                if (y != ky0) cand.push_back({kx0, y});
        } else { // diagonal
            for (int x = 0; x < 8; ++x)
                for (int y = 0; y < 8; ++y)
                    if (!(x == kx0 && y == ky0) &&
                        (x - y == kx0 - ky0 || x + y == kx0 + ky0))
                        cand.push_back({x, y});
        }
        if (!cand.empty()) {
            auto p = rnd.any(cand);
            sx0 = p.first;
            sy0 = p.second;
        } else {
            // Fallback to random distinct
            do {
                sx0 = rnd.next(0, 7);
                sy0 = rnd.next(0, 7);
            } while (sx0 == kx0 && sy0 == ky0);
        }
    } else { // posPattern == 3
        // King on edge, stone nearby
        int edgeType = rnd.next(0, 3);
        if (edgeType == 0) { // bottom row
            ky0 = 0;
            kx0 = rnd.next(0, 7);
        } else if (edgeType == 1) { // top row
            ky0 = 7;
            kx0 = rnd.next(0, 7);
        } else if (edgeType == 2) { // left column
            kx0 = 0;
            ky0 = rnd.next(0, 7);
        } else { // right column
            kx0 = 7;
            ky0 = rnd.next(0, 7);
        }
        vector<pair<int,int>> neigh;
        for (int dx0 = -2; dx0 <= 2; ++dx0)
            for (int dy0 = -2; dy0 <= 2; ++dy0)
                if (dx0 != 0 || dy0 != 0) {
                    int x = kx0 + dx0;
                    int y = ky0 + dy0;
                    if (inside(x, y)) neigh.push_back({x, y});
                }
        if (!neigh.empty()) {
            auto p = rnd.any(neigh);
            sx0 = p.first;
            sy0 = p.second;
        } else {
            // Fallback to random distinct
            do {
                sx0 = rnd.next(0, 7);
                sy0 = rnd.next(0, 7);
            } while (sx0 == kx0 && sy0 == ky0);
        }
    }

    // Helper to simulate a move with full rules
    auto simulateMove = [&](int dir, int kx, int ky, int sx, int sy,
                            int &nkx, int &nky, int &nsx, int &nsy)->bool {
        int mx = kx + dx[dir];
        int my = ky + dy[dir];
        if (!inside(mx, my)) return false;
        int tx = sx, ty = sy;
        if (mx == sx && my == sy) {
            tx = sx + dx[dir];
            ty = sy + dy[dir];
            if (!inside(tx, ty)) return false;
        }
        nkx = mx; nky = my;
        nsx = tx; nsy = ty;
        return true;
    };

    // Generate moves with some strategy and simulate on a copy
    int kx = kx0, ky = ky0, sx = sx0, sy = sy0;
    vector<string> cmds;
    cmds.reserve(N);

    for (int step = 0; step < N; ++step) {
        double r = rnd.next();
        vector<int> candidates;

        int curDist = max(abs(kx - sx), abs(ky - sy));

        if (r < 0.4) {
            // Prefer moves that approach or push the stone
            for (int i = 0; i < 8; ++i) {
                int nkx, nky, nsx, nsy;
                if (!simulateMove(i, kx, ky, sx, sy, nkx, nky, nsx, nsy))
                    continue;
                int newDist = max(abs(nkx - nsx), abs(nky - nsy));
                bool isPush = (nkx == sx && nky == sy);
                if (isPush || newDist <= curDist)
                    candidates.push_back(i);
            }
        } else if (r < 0.6) {
            // Prefer moves that would be invalid (skipped) -> edge stress
            for (int i = 0; i < 8; ++i) {
                int mx = kx + dx[i];
                int my = ky + dy[i];
                bool bad = false;
                if (!inside(mx, my)) {
                    bad = true;
                } else if (mx == sx && my == sy) {
                    int tx = sx + dx[i];
                    int ty = sy + dy[i];
                    if (!inside(tx, ty)) bad = true;
                }
                if (bad) candidates.push_back(i);
            }
        }

        int dirIndex;
        if (!candidates.empty()) {
            dirIndex = rnd.any(candidates);
        } else {
            dirIndex = rnd.next(0, 7);
        }

        cmds.push_back(moveNames[dirIndex]);

        int nkx, nky, nsx, nsy;
        if (simulateMove(dirIndex, kx, ky, sx, sy, nkx, nky, nsx, nsy)) {
            kx = nkx; ky = nky;
            sx = nsx; sy = nsy;
        } // else move is skipped
    }

    // Output initial positions and commands
    string kingPos, stonePos;
    kingPos += char('A' + kx0);
    kingPos += char('1' + ky0);
    stonePos += char('A' + sx0);
    stonePos += char('1' + sy0);

    println(kingPos, stonePos, N);
    for (const string &cmd : cmds) println(cmd);

    return 0;
}
