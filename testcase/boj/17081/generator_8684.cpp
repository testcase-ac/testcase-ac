#include "testlib.h"
using namespace std;

struct MonCell {
    int r, c;
    bool isBoss;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Mode controls overall style / density
    int mode = rnd.next(0, 2); // 0: small/sparse, 1: larger/monster-heavy, 2: loot-heavy

    int N, M;
    if (mode == 0) {
        N = rnd.next(3, 5);
        M = rnd.next(3, 5);
    } else if (mode == 1) {
        N = rnd.next(5, 8);
        M = rnd.next(5, 8);
    } else {
        N = rnd.next(4, 7);
        M = rnd.next(4, 7);
    }

    int A = N * M;

    // Collect all cell positions
    vector<pair<int,int>> cells;
    cells.reserve(A);
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < M; ++c)
            cells.push_back({r, c});

    shuffle(cells.begin(), cells.end());

    // Place hero and boss first
    pair<int,int> heroPos = cells.back(); cells.pop_back();
    pair<int,int> bossPos = cells.back(); cells.pop_back();

    int rem = (int)cells.size();

    // Caps per mode for number of objects (to keep test small & readable)
    int monCapArr[3]  = {3, 7, 5}; // normal monsters (&), boss is separate
    int boxCapArr[3]  = {3, 4, 7};
    int trapCapArr[3] = {2, 5, 4};
    int wallCapArr[3] = {2, 5, 3};

    int monCap  = monCapArr[mode];
    int boxCap  = boxCapArr[mode];
    int trapCap = trapCapArr[mode];
    int wallCap = wallCapArr[mode];

    // Decide counts; ensure they fit remaining cells
    int monMax = min(rem, monCap);
    int monMin = (mode == 1 ? 1 : 0); // in monster-heavy mode, likely at least 1 normal monster
    if (monMin > monMax) monMin = 0;
    int monNor = (monMax > 0 ? rnd.next(monMin, monMax) : 0);
    rem -= monNor;

    int boxMax = min(rem, boxCap);
    int boxes = (boxMax > 0 ? rnd.next(0, boxMax) : 0);
    rem -= boxes;

    int trapMax = min(rem, trapCap);
    int traps = (trapMax > 0 ? rnd.next(0, trapMax) : 0);
    rem -= traps;

    int wallMax = min(rem, wallCap);
    int walls = (wallMax > 0 ? rnd.next(0, wallMax) : 0);
    rem -= walls;
    // remaining cells stay empty '.'

    // Build grid
    vector<string> g(N, string(M, '.'));
    g[heroPos.first][heroPos.second] = '@';
    g[bossPos.first][bossPos.second] = 'M';

    // Assign other objects to remaining cells
    // cells currently has all except hero & boss
    // First walls, then traps, then boxes, then monsters
    int idx = 0;

    for (int i = 0; i < walls && idx < (int)cells.size(); ++i, ++idx) {
        int r = cells[idx].first;
        int c = cells[idx].second;
        g[r][c] = '#';
    }
    for (int i = 0; i < traps && idx < (int)cells.size(); ++i, ++idx) {
        int r = cells[idx].first;
        int c = cells[idx].second;
        g[r][c] = '^';
    }
    for (int i = 0; i < boxes && idx < (int)cells.size(); ++i, ++idx) {
        int r = cells[idx].first;
        int c = cells[idx].second;
        g[r][c] = 'B';
    }
    for (int i = 0; i < monNor && idx < (int)cells.size(); ++i, ++idx) {
        int r = cells[idx].first;
        int c = cells[idx].second;
        // Avoid overwriting hero or boss (should not happen as they were removed)
        if (g[r][c] == '.' )
            g[r][c] = '&';
        else
            ; // safety; in practice shouldn't occur
    }

    // Generate command string S using a random walk biased to stay in-bounds
    int minLen[3] = {1, 10, 5};
    int maxLen[3] = {30, 80, 60};
    int len = rnd.next(minLen[mode], maxLen[mode]);

    string cmds;
    cmds.reserve(len);
    int cr = heroPos.first;
    int cc = heroPos.second;
    vector<char> allDirs = {'L','R','U','D'};

    for (int i = 0; i < len; ++i) {
        vector<char> inBounds;
        // Check each direction for staying inside grid
        // Left
        if (cc - 1 >= 0) inBounds.push_back('L');
        // Right
        if (cc + 1 < M) inBounds.push_back('R');
        // Up
        if (cr - 1 >= 0) inBounds.push_back('U');
        // Down
        if (cr + 1 < N) inBounds.push_back('D');

        char d;
        if (!inBounds.empty() && rnd.next(0, 4) != 0) { // 75% prefer in-bounds
            d = rnd.any(inBounds);
        } else {
            d = rnd.any(allDirs);
        }
        cmds.push_back(d);

        // Simulate position for future steps (respect walls and bounds)
        int nr = cr, nc = cc;
        if (d == 'L') nc--;
        else if (d == 'R') nc++;
        else if (d == 'U') nr--;
        else if (d == 'D') nr++;

        if (nr >= 0 && nr < N && nc >= 0 && nc < M && g[nr][nc] != '#') {
            cr = nr;
            cc = nc;
        }
    }

    // Collect monster cells (including boss)
    vector<MonCell> monsters;
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            if (g[r][c] == '&' || g[r][c] == 'M') {
                MonCell mc;
                mc.r = r;
                mc.c = c;
                mc.isBoss = (g[r][c] == 'M');
                monsters.push_back(mc);
            }
        }
    }

    // Collect item box cells
    vector<pair<int,int>> boxCells;
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < M; ++c)
            if (g[r][c] == 'B')
                boxCells.push_back({r, c});

    // Helper for random stats within [1,20]
    auto randStat = [&](int low, int high) {
        if (low > high) swap(low, high);
        low = max(low, 1);
        high = min(high, 20);
        if (low > high) low = high = max(1, min(20, low));
        return rnd.next(low, high);
    };

    // Print output
    println(N, M);
    for (int r = 0; r < N; ++r)
        println(g[r]);

    println(cmds);

    // Monster info lines
    int K = (int)monsters.size();
    int baseLow = 1 + 3 * mode;
    int baseHigh = 8 + 4 * mode;
    baseLow = max(baseLow, 1);
    baseHigh = min(baseHigh, 20);
    if (baseLow > baseHigh) baseLow = baseHigh;

    for (int i = 0; i < K; ++i) {
        MonCell mc = monsters[i];
        int R = mc.r + 1;
        int C = mc.c + 1;

        // Simple unique names: "A", "B", "C", ...
        string name(1, char('A' + i));

        int W, Adef, H, E;
        if (mc.isBoss) {
            W    = randStat(baseLow + 2, baseHigh + 8);
            Adef = randStat(baseLow + 2, baseHigh + 8);
            H    = randStat(baseLow + 8, baseHigh + 12);
            E    = randStat(baseLow + 3, baseHigh + 10);
        } else {
            W    = randStat(baseLow, baseHigh);
            Adef = randStat(baseLow, baseHigh);
            H    = randStat(baseLow + 3, baseHigh + 7);
            E    = randStat(baseLow, baseHigh);
        }

        println(R, C, name, W, Adef, H, E);
    }

    // Item box info lines
    vector<string> accTypes = {"HR", "RE", "CO", "EX", "DX", "HU", "CU"};
    for (auto &bc : boxCells) {
        int R = bc.first + 1;
        int C = bc.second + 1;

        char T;
        int pick = rnd.next(0, 9);
        if (mode == 2) {
            // loot-heavy: more accessories
            if (pick < 2) T = 'W';
            else if (pick < 4) T = 'A';
            else T = 'O';
        } else {
            if (pick < 3) T = 'W';
            else if (pick < 6) T = 'A';
            else T = 'O';
        }

        if (T == 'W' || T == 'A') {
            int val = rnd.next(1, 10);
            println(R, C, T, val);
        } else {
            string eff = rnd.any(accTypes);
            println(R, C, T, eff);
        }
    }

    return 0;
}
