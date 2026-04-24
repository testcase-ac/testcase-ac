#include <bits/stdc++.h>
using namespace std;

int board[200][200];
bool seen[31][200][200];
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};
int dr_knight[] = {1, 2, 2, 1, -1, -2, -2, -1};
int dc_knight[] = {2, 1, -1, -2, -2, -1, 1, 2};
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int K, C, R;
    cin >> K >> C >> R;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> board[i][j];
        }
    }
    queue<tuple<int, int, int>> que;
    seen[0][0][0] = 1;
    que.push({0, 0, 0});
    int ans = 0;
    while(que.size()) {
        int s = que.size();
        while(s--) {
            auto [k, r, c] = que.front();
            if(r == R - 1 && c == C - 1) {
                return !(cout << ans);
            }
            que.pop();
            if(k < K) {
                for(int i = 0; i < 8; i++) {
                    int nr = r + dr_knight[i];
                    int nc = c + dc_knight[i];
                    if(nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                    if(board[nr][nc] == 0 && !seen[k + 1][nr][nc]) {
                        seen[k + 1][nr][nc] = 1;
                        que.push({k + 1, nr, nc});
                    }
                }
            }
            for(int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if(nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                if(board[nr][nc] == 0 && !seen[k][nr][nc]) {
                    seen[k][nr][nc] = 1;
                    que.push({k, nr, nc});
                }
            }
        }
        ans++;
    }
    cout << -1;
}
