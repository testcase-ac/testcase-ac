#include <bits/stdc++.h>
using namespace std;
int R, C;
int ansbm = 0, anscnt = INT_MAX;
void solve(vector<vector<int>> arr, int bm, bool output = false) {
    vector<vector<int>> ans(R, vector<int>(C, 0));
    auto toggle = [&](int i, int j) {
        ans[i][j] ^= 1;
        arr[i][j] ^= 1;
        if(j) {
            arr[i][j - 1] ^= 1;
        }
        if(i) {
            arr[i - 1][j] ^= 1;
        }
        if(j + 1 < C) {
            arr[i][j + 1] ^= 1;
        }
        if(i + 1 < R) {
            arr[i + 1][j] ^= 1;
        }
    };
    for(int j = 0; j < C; j++) {
        if(bm & (1 << j)) {
            toggle(0, C - 1 - j);
        }
    }
    for(int i = 1; i < R; i++) {
        for(int j = 0; j < C; j++) {
            if(arr[i - 1][j]) {
                toggle(i, j);
            }
        }
    }
    if(output) {
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                cout << ans[i][j] << " ";
            }
            cout << endl;
        }
        return;
    }
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            if(arr[i][j]) {
                assert(i == R - 1);
                return;
            }
        }
    }
    int cnt = 0;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            if(ans[i][j]) {
                cnt++;
            }
        }
    }
    if(cnt < anscnt) {
        anscnt = cnt;
        ansbm = bm;
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> R >> C;
    vector<vector<int>> arr(R, vector<int>(C));
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> arr[i][j];
        }
    }
    for(int bm = 0; bm < (1 << C); bm++) {
        solve(arr, bm);
    }
    if(anscnt != INT_MAX) {
        solve(arr, ansbm, true);
    } else {
        cout << "IMPOSSIBLE";
    }
}
