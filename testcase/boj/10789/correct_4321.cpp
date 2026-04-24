#include <bits/stdc++.h>
using namespace std;
bool seen[50][50][10001];
char grid[50][51], text[10001];
int R, C, H, dr[] = {1, 0, -1, 0}, dc[] = {0, 1, 0, -1};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> R >> C;
    for(int i = 0; i < R; i++) {
        cin >> grid[i];
    }
    cin >> text;
    H = strlen(text);
    queue<tuple<int, int, int>> q;
    q.push({0, 0, 0});
    seen[0][0][0] = 1;
    int dist = 0;
    while(q.size()) {
        int sz = q.size();
        while(sz--) {
            auto [r, c, h] = q.front();
            q.pop();
            if(h == H && grid[r][c] == '*') {
                cout << dist + 1;
                return 0;
            }
            for(int i = 0; i < 4; i++) {
                int tr = r + dr[i], tc = c + dc[i];
                while(tr >= 0 && tr < R && tc >= 0 && tc < C && grid[tr][tc] == grid[r][c]) {
                    tr += dr[i];
                    tc += dc[i];
                }
                if(!(tr >= 0 && tr < R && tc >= 0 && tc < C)) {
                    continue;
                }
                if(!seen[tr][tc][h]) {
                    seen[tr][tc][h] = 1;
                    q.push({tr, tc, h});
                }
            }
            if(h < H && grid[r][c] == text[h]) {
                if(!seen[r][c][h + 1]) {
                    seen[r][c][h + 1] = 1;
                    // printf("seen h = %d at dist = %d, r, c = %d, %d\n", h + 1, dist, r, c);
                    q.push({r, c, h + 1});
                }
            }
        }
        dist++;
    }
}
