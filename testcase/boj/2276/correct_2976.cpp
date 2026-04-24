#include <bits/stdc++.h>
using namespace std;
int height[300][300], water[300][300], C, R;
int dr[] = {1, 0, -1, 0}, dc[] = {0, 1, 0, -1};
struct elem {
    int r, c, w;
    bool operator<(const elem &e) const {
        return w > e.w;
    }
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> C >> R;
    memset(water, 0x3f, sizeof(water));
    priority_queue<elem> pq;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> height[i][j];
            if(!i || i == R - 1 || !j || j == C - 1) {
                water[i][j] = height[i][j];
                pq.push({i, j, height[i][j]});
            }
        }
    }
    while(pq.size()) {
        auto [r, c, w] = pq.top();
        pq.pop();
        if(water[r][c] < w) {
            continue;
        }
        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if(nr < 0 || nr >= R || nc < 0 || nc >= C) {
                continue;
            }
            int nw = max(min(w, water[nr][nc]), height[nr][nc]);
            if(nw < water[nr][nc]) {
                water[nr][nc] = nw;
                pq.push({nr, nc, nw});
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            ans += water[i][j] - height[i][j];
        }
    }
    cout << ans;
}
