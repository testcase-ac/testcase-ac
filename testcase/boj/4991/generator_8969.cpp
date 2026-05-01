#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

bool allDirtyReachable(const vector<string>& g, int w, int h,
                       int rx, int ry,
                       const vector<pair<int,int>>& dirt) {
    vector<vector<bool>> vis(h, vector<bool>(w, false));
    queue<pair<int,int>> q;
    q.push({rx, ry});
    vis[ry][rx] = true;
    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};

    while (!q.empty()) {
        auto [x,y] = q.front(); q.pop();
        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
            if (vis[ny][nx]) continue;
            if (g[ny][nx] == 'x') continue;
            vis[ny][nx] = true;
            q.push({nx, ny});
        }
    }

    for (auto &d : dirt) {
        int x = d.first;
        int y = d.second;
        if (!vis[y][x]) return false;
    }
    return true;
}

vector<string> placeConnectedObstacles(const vector<string>& base, int w, int h,
                                       int rx, int ry,
                                       const vector<pair<int,int>>& dirt) {
    int A = w * h;
    int minObs = A / 10;
    int maxObs = A / 3;
    if (maxObs < 0) maxObs = 0;
    if (minObs > maxObs) minObs = maxObs;

    for (int attempt = 0; attempt < 30; ++attempt) {
        vector<string> g = base;

        vector<pair<int,int>> empties;
        for (int y = 0; y < h; ++y)
            for (int x = 0; x < w; ++x)
                if (g[y][x] == '.')
                    empties.push_back({x, y});

        if (empties.empty() || maxObs == 0) {
            // No place for obstacles or none desired
            if (allDirtyReachable(g, w, h, rx, ry, dirt))
                return g;
            else
                return base;
        }

        shuffle(empties.begin(), empties.end());
        int obsCount = rnd.next(minObs, maxObs);
        if (obsCount > (int)empties.size()) obsCount = (int)empties.size();

        for (int i = 0; i < obsCount; ++i) {
            int x = empties[i].first;
            int y = empties[i].second;
            g[y][x] = 'x';
        }

        if (allDirtyReachable(g, w, h, rx, ry, dirt))
            return g;
    }

    // Fallback: no obstacles
    return base;
}

// Scenario 0: zero dirty cells, small simple room
vector<string> genZeroDirty(int &w, int &h) {
    w = rnd.next(1, 5);
    h = rnd.next(1, 5);
    vector<string> g(h, string(w, '.'));
    int rx = rnd.next(0, w - 1);
    int ry = rnd.next(0, h - 1);
    g[ry][rx] = 'o';
    return g;
}

// Scenario 2: multiple dirty cells, all reachable, with some obstacles
vector<string> genMultiDirtyConnected(int &w, int &h) {
    w = rnd.next(3, 12);
    h = rnd.next(3, 12);
    vector<string> base(h, string(w, '.'));

    int rx = rnd.next(0, w - 1);
    int ry = rnd.next(0, h - 1);
    base[ry][rx] = 'o';

    int area = w * h;
    int freeCells = area - 1; // excluding robot
    int maxDirty = min(10, freeCells);
    int dirtyCnt = rnd.next(2, maxDirty); // ensure at least 2 dirty cells

    vector<pair<int,int>> cells;
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
            if (!(x == rx && y == ry))
                cells.push_back({x, y});
    shuffle(cells.begin(), cells.end());

    vector<pair<int,int>> dirt;
    for (int i = 0; i < dirtyCnt; ++i) {
        int x = cells[i].first;
        int y = cells[i].second;
        base[y][x] = '*';
        dirt.push_back({x, y});
    }

    vector<string> g = placeConnectedObstacles(base, w, h, rx, ry, dirt);
    return g;
}

// Scenario 1: at least one unreachable dirty cell via a partition wall
vector<string> genUnreachablePartition(int &w, int &h) {
    w = rnd.next(4, 12);
    h = rnd.next(3, 12);
    vector<string> g(h, string(w, '.'));

    int cutC = rnd.next(1, w - 2); // wall column
    for (int y = 0; y < h; ++y)
        g[y][cutC] = 'x';

    // Robot on the left side
    int rx = rnd.next(0, cutC - 1);
    int ry = rnd.next(0, h - 1);
    g[ry][rx] = 'o';

    // One mandatory unreachable dirty on the right side
    vector<pair<int,int>> rightCells;
    for (int y = 0; y < h; ++y) {
        for (int x = cutC + 1; x < w; ++x) {
            rightCells.push_back({x, y});
        }
    }
    shuffle(rightCells.begin(), rightCells.end());
    int ux = rightCells[0].first;
    int uy = rightCells[0].second;
    g[uy][ux] = '*';

    // Possibly add more dirty cells (reachable or not)
    vector<pair<int,int>> empties;
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
            if (g[y][x] == '.')
                empties.push_back({x, y});
    shuffle(empties.begin(), empties.end());

    int area = w * h;
    int obstacles = h; // the wall
    int freeCells = area - obstacles - 1 - 1; // minus robot and one dirty
    if (freeCells < 0) freeCells = 0;
    int maxDirtyExtra = min(9, freeCells);
    int extraDirty = (maxDirtyExtra > 0 ? rnd.next(0, maxDirtyExtra) : 0);

    for (int i = 0; i < extraDirty; ++i) {
        int x = empties[i].first;
        int y = empties[i].second;
        g[y][x] = '*';
    }

    return g;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(2, 3);
    // Scenario codes: 0 = zero dirty, 1 = unreachable, 2 = multi-dirty connected
    vector<int> types;
    if (T == 2) {
        types = {1, 2};            // always one unreachable, one multi-dirty connected
    } else {
        types = {0, 1, 2};         // zero-dirty, unreachable, multi-dirty connected
    }
    shuffle(types.begin(), types.end());

    for (int ti = 0; ti < T; ++ti) {
        int w, h;
        vector<string> g;
        if (types[ti] == 0) {
            g = genZeroDirty(w, h);
        } else if (types[ti] == 1) {
            g = genUnreachablePartition(w, h);
        } else {
            g = genMultiDirtyConnected(w, h);
        }

        println(w, h);
        for (int y = 0; y < h; ++y)
            println(g[y]);
    }

    println(0, 0);
    return 0;
}
