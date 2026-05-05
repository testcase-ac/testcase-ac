#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M;

bool is_cliff(int v) {
    return v != 1;
}

bool is_intersection(const vector<vector<int>>& g, int r, int c) {
    bool hor = false, ver = false;
    if (c > 0 && is_cliff(g[r][c - 1])) hor = true;
    if (c < N - 1 && is_cliff(g[r][c + 1])) hor = true;
    if (r > 0 && is_cliff(g[r - 1][c])) ver = true;
    if (r < N - 1 && is_cliff(g[r + 1][c])) ver = true;
    return hor && ver;
}

bool check_solvable(const vector<vector<int>>& g, bool allow_new_bridge) {
    vector<vector<vector<bool>>> vis(N, vector<vector<bool>>(N, vector<bool>(2, false)));
    queue<pair<pair<int, int>, int>> q;

    q.push({{0, 0}, 0});
    vis[0][0][0] = true;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        int r = curr.first.first;
        int c = curr.first.second;
        int used = curr.second;

        if (r == N - 1 && c == N - 1) return true;

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;

            if (is_cliff(g[r][c]) && is_cliff(g[nr][nc])) continue;

            if (g[nr][nc] == 1) { // 일반 땅
                if (!vis[nr][nc][used]) {
                    vis[nr][nc][used] = true;
                    q.push({{nr, nc}, used});
                }
            } else if (g[nr][nc] >= 2) { // 기존 오작교
                if (!is_intersection(g, nr, nc)) {
                    if (!vis[nr][nc][used]) {
                        vis[nr][nc][used] = true;
                        q.push({{nr, nc}, used});
                    }
                }
            } else if (g[nr][nc] == 0) { // 새 오작교를 지을 수 있는 절벽
                if (allow_new_bridge && used == 0 && !is_intersection(g, nr, nc)) {
                    if (!vis[nr][nc][1]) {
                        vis[nr][nc][1] = true;
                        q.push({{nr, nc}, 1});
                    }
                }
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) 
{
    registerGen(argc, argv, 1);

    N = rnd.next(2, 10);
    M = rnd.next(2, 20);

    vector<vector<int>> best_g(N, vector<int>(N, 1));
    int best_score = -1;

    for (int attempt = 0; attempt < 5000; attempt++) {
        vector<vector<int>> g(N, vector<int>(N, 1));

        int num_cliffs = rnd.next(1, N * N / 2);
        for (int i = 0; i < num_cliffs; i++) {
            int r = rnd.next(0, N - 1);
            int c = rnd.next(0, N - 1);
            if ((r == 0 && c == 0) || (r == N - 1 && c == N - 1)) continue;
            g[r][c] = 0;
        }

        int num_bridges = rnd.next(0, N * N / 4);
        for (int i = 0; i < num_bridges; i++) {
            int r = rnd.next(0, N - 1);
            int c = rnd.next(0, N - 1);
            if ((r == 0 && c == 0) || (r == N - 1 && c == N - 1)) continue;
            g[r][c] = rnd.next(2, 20);
        }

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (g[r][c] >= 2 && is_intersection(g, r, c)) {
                    g[r][c] = 1; 
                }
            }
        }

        bool has_buildable_zero = false;
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (g[r][c] == 0 && !is_intersection(g, r, c)) {
                    has_buildable_zero = true;
                    break;
                }
            }
            if (has_buildable_zero) break;
        }
        if (!has_buildable_zero) continue;

        bool solvable_with_new = check_solvable(g, true);
        if (!solvable_with_new) continue;

        bool solvable_without_new = check_solvable(g, false);

        int score = 1;
        if (!solvable_without_new) {
            score += 10;
        }

        if (score > best_score) {
            best_score = score;
            best_g = g;
            
            if (score > 10) break;
        }
    }

    println(N, M);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << best_g[i][j] << (j == N - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
