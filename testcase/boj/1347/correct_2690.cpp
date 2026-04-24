#include <bits/stdc++.h>
using namespace std;
// L: +1, R: -1
int dr[] = {1, 0, -1, 0}, dc[] = {0, 1, 0, -1};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    string s;
    cin >> N >> s;
    vector<pair<int,int>> v;
    int r = 0, c = 0, dir = 0, min_r = 0, max_r = 0, min_c = 0, max_c = 0;

    v.push_back({r, c});
    for(char d: s) {
        if(d == 'R') {
            dir = (dir + 3) % 4;
        } else if(d == 'L') {
            dir = (dir + 1) % 4;
        } else {
            r += dr[dir];
            c += dc[dir];
            v.push_back({r, c});
            min_r = min(min_r, r);
            max_r = max(max_r, r);
            min_c = min(min_c, c);
            max_c = max(max_c, c);
        }
    }
    int R = max_r - min_r + 1, C = max_c - min_c + 1;
    vector<vector<char>> ans(R, vector<char>(C, '#'));
    for(auto [r, c]: v) {
        ans[r - min_r][c - min_c] = '.';
    }
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
}
