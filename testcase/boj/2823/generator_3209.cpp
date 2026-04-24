#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int dr[4] = {-1,1,0,0}, dc[4] = {0,0,-1,1};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid size
    int R = rnd.next(3, 10);
    int C = rnd.next(3, 10);
    // Decide type: with dead-end (tree-like) or without dead-end
    bool has_dead_end = rnd.next(0,1) == 1;
    vector<vector<bool>> road(R, vector<bool>(C, false));
    int total = R * C;
    if (has_dead_end) {
        // Grow a random tree of roads
        int target = rnd.next(2, max(2, total/2));
        // start point
        int sr = rnd.next(0, R-1), sc = rnd.next(0, C-1);
        road[sr][sc] = true;
        int roadCount = 1;
        vector<pair<int,int>> frontier;
        // add initial neighbors
        for (int d = 0; d < 4; d++) {
            int nr = sr + dr[d], nc = sc + dc[d];
            if (nr>=0 && nr<R && nc>=0 && nc<C)
                frontier.emplace_back(nr,nc);
        }
        // unique frontier
        sort(frontier.begin(), frontier.end());
        frontier.erase(unique(frontier.begin(), frontier.end()), frontier.end());
        while (roadCount < target && !frontier.empty()) {
            int idx = rnd.next(0, (int)frontier.size()-1);
            auto [r, c] = frontier[idx];
            // if already road, skip
            if (road[r][c]) {
                frontier.erase(frontier.begin()+idx);
                continue;
            }
            // add road
            road[r][c] = true;
            roadCount++;
            frontier.erase(frontier.begin()+idx);
            // add its neighbors
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr>=0 && nr<R && nc>=0 && nc<C && !road[nr][nc]) {
                    frontier.emplace_back(nr,nc);
                }
            }
            // dedupe frontier
            sort(frontier.begin(), frontier.end());
            frontier.erase(unique(frontier.begin(), frontier.end()), frontier.end());
        }
    } else {
        // Start full of roads
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                road[i][j] = true;
        int roadCount = total;
        // attempt to remove up to some cells
        int attempts = rnd.next(0, total/3);
        while (attempts-- > 0 && roadCount > 2) {
            // gather candidates
            vector<pair<int,int>> cand;
            for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
                if (!road[i][j]) continue;
                // don't remove if it'd leave <2 roads
                if (roadCount <= 2) continue;
                // check neighbor degrees after removal
                bool ok = true;
                for (int d = 0; d < 4; d++) {
                    int ni = i + dr[d], nj = j + dc[d];
                    if (ni>=0 && ni<R && nj>=0 && nj<C && road[ni][nj]) {
                        int deg = 0;
                        for (int e = 0; e < 4; e++) {
                            int mi = ni + dr[e], mj = nj + dc[e];
                            if (mi>=0 && mi<R && mj>=0 && mj<C) {
                                if (mi==i && mj==j) continue;
                                if (road[mi][mj]) deg++;
                            }
                        }
                        if (deg < 2) { ok = false; break; }
                    }
                }
                if (!ok) continue;
                // simulate removal and check connectivity
                road[i][j] = false;
                // find a start
                queue<pair<int,int>> q;
                vector<vector<bool>> vis(R, vector<bool>(C,false));
                bool found = false;
                for (int x = 0; x < R && !found; x++)
                    for (int y = 0; y < C; y++) if (road[x][y]) {
                        q.emplace(x,y);
                        vis[x][y] = true;
                        found = true;
                        break;
                    }
                int cc = 0;
                if (found) {
                    while (!q.empty()) {
                        auto [x,y] = q.front(); q.pop();
                        cc++;
                        for (int d = 0; d < 4; d++) {
                            int ni = x + dr[d], nj = y + dc[d];
                            if (ni>=0 && ni<R && nj>=0 && nj<C && road[ni][nj] && !vis[ni][nj]) {
                                vis[ni][nj] = true;
                                q.emplace(ni,nj);
                            }
                        }
                    }
                }
                if (!found || cc != roadCount-1) ok = false;
                // restore
                road[i][j] = true;
                if (ok) cand.emplace_back(i,j);
            }
            if (cand.empty()) break;
            // remove one random
            auto [ri, rj] = rnd.any(cand);
            road[ri][rj] = false;
            roadCount--;
        }
    }
    // Ensure at least 2 roads
    vector<pair<int,int>> cells;
    for (int i = 0; i < R; i++) for (int j = 0; j < C; j++)
        if (road[i][j]) cells.emplace_back(i,j);
    if ((int)cells.size() < 2) {
        // force-add roads until 2
        for (int i = 0; i < R && (int)cells.size() < 2; i++) {
            for (int j = 0; j < C && (int)cells.size() < 2; j++) {
                if (!road[i][j]) {
                    road[i][j] = true;
                    cells.emplace_back(i,j);
                }
            }
        }
    }
    // Output
    println(R, C);
    for (int i = 0; i < R; i++) {
        string s;
        for (int j = 0; j < C; j++)
            s += (road[i][j] ? '.' : 'X');
        printf("%s\n", s.c_str());
    }
    return 0;
}
