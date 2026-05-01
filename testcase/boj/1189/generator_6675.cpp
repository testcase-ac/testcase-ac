#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int R, C, L;
vector<pair<int,int>> path;
bool vis[5][5];
int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};

bool dfs(int x, int y, int depth) {
    if (depth == L-1) {
        // reached required length
        return (x == 0 && y == C-1);
    }
    vector<int> dirs = {0,1,2,3};
    shuffle(dirs.begin(), dirs.end());
    for (int d : dirs) {
        int nx = x + dr[d], ny = y + dc[d];
        if (nx>=0 && nx<R && ny>=0 && ny<C && !vis[nx][ny]) {
            vis[nx][ny] = true;
            path.emplace_back(nx, ny);
            if (dfs(nx, ny, depth+1)) return true;
            path.pop_back();
            vis[nx][ny] = false;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // grid size
    R = rnd.next(1, 5);
    C = rnd.next(1, 5);
    int minL = R + C - 1;
    int maxL = R * C;
    // choose length hyperparameter
    int lType = rnd.next(0, 3);
    if (lType == 0) {
        // minimal
        L = minL;
    } else if (lType == 1) {
        // near minimal
        int ext = min(maxL - minL, 2);
        L = minL + rnd.next(0, ext);
    } else if (lType == 2) {
        // near maximal
        int ext = min(maxL - minL, 2);
        L = maxL - rnd.next(0, ext);
    } else {
        // random
        L = rnd.next(minL, maxL);
    }
    // attempt to find a self-avoiding path of length L
    bool found = false;
    path.clear();
    for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) vis[i][j] = false;
    // start at bottom-left
    vis[R-1][0] = true;
    path.emplace_back(R-1, 0);
    found = dfs(R-1, 0, 0);
    // fallback to minimal direct path if dfs failed
    if (!found) {
        L = minL;
        path.clear();
        for (int i = R-1; i >= 0; i--) path.emplace_back(i, 0);
        for (int j = 1; j < C; j++) path.emplace_back(0, j);
    }
    // build grid and place obstacles
    vector<string> grid(R, string(C, '.'));
    int obsType = rnd.next(0, 2);
    if (obsType == 0) {
        // no obstacles
    } else if (obsType == 1) {
        // random density
        double p = rnd.next(0.0, 1.0);
        // mark path cells
        vector<vector<bool>> onPath(R, vector<bool>(C, false));
        for (auto &pr : path) onPath[pr.first][pr.second] = true;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (!onPath[i][j] && rnd.next() < p) {
                    grid[i][j] = 'T';
                }
            }
        }
    } else {
        // block a free row or column
        vector<int> freeRows, freeCols;
        vector<vector<bool>> onPath(R, vector<bool>(C, false));
        for (auto &pr : path) onPath[pr.first][pr.second] = true;
        for (int i = 0; i < R; i++) {
            bool ok = true;
            for (int j = 0; j < C; j++) if (onPath[i][j]) { ok = false; break; }
            if (ok) freeRows.push_back(i);
        }
        for (int j = 0; j < C; j++) {
            bool ok = true;
            for (int i = 0; i < R; i++) if (onPath[i][j]) { ok = false; break; }
            if (ok) freeCols.push_back(j);
        }
        if (!freeRows.empty() && rnd.next(0,1)==0) {
            int br = rnd.any(freeRows);
            for (int j = 0; j < C; j++) grid[br][j] = 'T';
        } else if (!freeCols.empty()) {
            int bc = rnd.any(freeCols);
            for (int i = 0; i < R; i++) grid[i][bc] = 'T';
        } else {
            // fallback to light random
            double p = rnd.next(0.0, 1.0);
            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    if (!onPath[i][j] && rnd.next() < p) grid[i][j] = 'T';
                }
            }
        }
    }
    // ensure start/end are free
    grid[R-1][0] = '.';
    grid[0][C-1] = '.';
    // output
    println(R, C, L);
    for (int i = 0; i < R; i++) {
        printf("%s\n", grid[i].c_str());
    }
    return 0;
}
