#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid dimensions (avoid too small to place towers away from borders)
    int R = rnd.next(3, 10);
    int S = rnd.next(3, 10);

    // Maximum towers so that each can be placed at least one cell away from borders
    int maxT = min(R - 2, S - 2);
    int Tcount = rnd.next(1, maxT);

    // Choose distinct rows and columns for towers (ensures no two in same row/col)
    vector<int> rows(R - 2), cols(S - 2);
    iota(rows.begin(), rows.end(), 1);
    iota(cols.begin(), cols.end(), 1);
    shuffle(rows.begin(), rows.end());
    shuffle(cols.begin(), cols.end());
    rows.resize(Tcount);
    cols.resize(Tcount);

    // Place towers with a valid hidden orientation (0=left/down,1=down/right,2=right/up,3=up/left)
    vector<tuple<int,int,int>> towers;
    for (int i = 0; i < Tcount; i++) {
        int r = rows[i], c = cols[i];
        int d = rnd.next(0, 3);
        towers.emplace_back(r, c, d);
    }

    // Initialize empty grid
    vector<string> grid(R, string(S, '.'));

    // Mark towers
    for (auto &t : towers) {
        int r, c, d;
        tie(r, c, d) = t;
        grid[r][c] = 'T';
    }

    // Direction deltas: 0=left,1=down,2=right,3=up
    vector<pair<int,int>> delta = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

    // For each tower, place one clone in each of its two firing directions (adjacent cell)
    for (auto &t : towers) {
        int r, c, d;
        tie(r, c, d) = t;
        int d1 = d, d2 = (d + 1) % 4;
        auto [dr1, dc1] = delta[d1];
        auto [dr2, dc2] = delta[d2];
        grid[r + dr1][c + dc1] = 'n';
        grid[r + dr2][c + dc2] = 'n';
    }

    // Output
    println(R, S);
    for (int i = 0; i < R; i++) {
        println(grid[i]);
    }

    return 0;
}
