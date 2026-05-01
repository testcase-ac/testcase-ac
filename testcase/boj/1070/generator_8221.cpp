#include "testlib.h"
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Dimensions
    int N = rnd.next(3, 12);
    int M = rnd.next(3, 12);
    // Choose number of terrain types
    int K = rnd.next(3, 6);
    vector<char> letters;
    for (int i = 0; i < K; i++) letters.push_back(char('A' + i));
    // Block density up to 30%
    int blockThreshold = rnd.next(0, 300); // per mille
    vector<string> grid(N, string(M, ' '));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (rnd.next(0, 999) < blockThreshold) grid[i][j] = '-';
            else grid[i][j] = rnd.any(letters);
        }
    }
    // Place the capital '*' at a random interior cell
    int si = rnd.next(1, N-2), sj = rnd.next(1, M-2);
    grid[si][sj] = '*';
    // Collect boundary cells
    vector<pair<int,int>> border;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i==0 || i==N-1 || j==0 || j==M-1)
                border.emplace_back(i, j);
        }
    }
    // Optionally ensure at least one path (80% of cases), otherwise leave for zero-cost scenario
    if (rnd.next() < 0.8) {
        // Find a boundary letter cell
        vector<pair<int,int>> cand;
        for (auto &p : border) {
            int i = p.first, j = p.second;
            if (grid[i][j] != '-') cand.push_back(p);
        }
        if (cand.empty()) {
            // open one boundary cell
            auto p = rnd.any(border);
            grid[p.first][p.second] = rnd.any(letters);
            cand.push_back(p);
        }
        auto b = rnd.any(cand);
        // BFS to see if reachable
        vector<vector<bool>> vis(N, vector<bool>(M, false));
        queue<pair<int,int>> q;
        vis[b.first][b.second] = true;
        q.push(b);
        int di[4] = {1,-1,0,0}, dj[4] = {0,0,1,-1};
        bool reach = false;
        while (!q.empty()) {
            auto u = q.front(); q.pop();
            if (u.first==si && u.second==sj) { reach = true; break; }
            for (int d = 0; d < 4; d++) {
                int ni = u.first + di[d], nj = u.second + dj[d];
                if (ni<0||ni>=N||nj<0||nj>=M) continue;
                if (vis[ni][nj] || grid[ni][nj]=='-') continue;
                vis[ni][nj] = true;
                q.emplace(ni,nj);
            }
        }
        // If not reachable, carve a simple Manhattan path
        if (!reach) {
            int ci = b.first, cj = b.second;
            while (ci != si) {
                if (ci < si) ci++; else ci--;
                if (grid[ci][cj]=='-') grid[ci][cj] = rnd.any(letters);
            }
            while (cj != sj) {
                if (cj < sj) cj++; else cj--;
                if (grid[ci][cj]=='-') grid[ci][cj] = rnd.any(letters);
            }
            // ensure the capital stays '*'
            grid[si][sj] = '*';
        }
    }
    // Generate weights for A-Z
    vector<int> w(26);
    for (int i = 0; i < 26; i++) {
        w[i] = rnd.next(1, 100);
    }
    // Output
    println(N, M);
    for (int i = 0; i < N; i++) println(grid[i]);
    println(w);
    return 0;
}
