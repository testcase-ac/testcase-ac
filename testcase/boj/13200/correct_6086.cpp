#include <bits/stdc++.h>
using namespace std;
int arr[7][7], seen[7][7], lcnt[7][7], ans[7][7];
int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};
struct seg {
    int r, c1, c2;
};
struct req {
    int r, c, cnt;
};
struct pos {
    int r, c;
};
void solve() {
    memset(arr, 0, sizeof(arr));
    memset(seen, 0, sizeof(seen));
    memset(lcnt, 0, sizeof(lcnt));
    int N;
    cin >> N;
    vector<req> reqs;
    vector<seg> segs;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> arr[i][j];
            if(arr[i][j] >= 0) {
                reqs.push_back({i, j, arr[i][j]});
            }
        }
    }
    for(int r=0; r<N; r++) {
        for(int i=0, j=0; i<N; i=j) {
            if(arr[r][j] != -2) {
                j++;
                continue;
            }
            while(j<N && arr[r][j] == -2) {
                j++;
            }
            segs.push_back({r, i, j-1});
        }
    }
    vector<pos> lights;
    function<bool(int)> dfs = [&](int p) {
        // printf("enter p = %d\n", p);
        if(p == segs.size()) {
            for(auto [r, c, cnt]: reqs) {
                if(lcnt[r][c] != cnt) {
                    return false;
                }
            }
            for(int r=0; r<N; r++) {
                for(int c=0; c<N; c++) {
                    if(arr[r][c] == -2 && !seen[r][c]) {
                        return false;
                    }
                }
            }
            return true;
        }
        auto [r, c1, c2] = segs[p];
        for(int c=c1; c<=c2; c++) {
            seen[r][c]++;
        }
        for(int c=c1; c<=c2; c++) {
            if(seen[r][c] > 1) {
                continue;
            }
            for(int t=r+1; t<N; t++) {
                if(arr[t][c] >= -1) // black
                    break;
                seen[t][c]++;
            }
            for(int t=r-1; t>=0; t--) {
                if(arr[t][c] >= -1)
                    break;
                seen[t][c]++;
            }
            for(int t=0; t<4; t++) {
                int tr = r + dr[t], tc = c + dc[t];
                if(0 <= tr && tr < N && 0 <= tc && tc < N && arr[tr][tc] >= 0) {
                    lcnt[tr][tc]++;
                }
            }
            lights.push_back({r, c});
            // printf("p = %d: enter with marking %d, %d\n", p, r, c);
            if(dfs(p+1)) {
                return true;
            }
            lights.pop_back();
            for(int t=0; t<4; t++) {
                int tr = r + dr[t], tc = c + dc[t];
                if(0 <= tr && tr < N && 0 <= tc && tc < N) {
                    lcnt[tr][tc]--;
                }
            }
            for(int t=r+1; t<N; t++) {
                if(arr[t][c] >= -1) // black
                    break;
                seen[t][c]--;
            }
            for(int t=r-1; t>=0; t--) {
                if(arr[t][c] >= -1)
                    break;
                seen[t][c]--;
            }
        }
        for(int c=c1; c<=c2; c++) {
            seen[r][c]--;
        }
        // printf("p = %d: enter no check\n", p);
        return dfs(p+1);
    };
    bool res = dfs(0);
    memset(ans, 0, sizeof(ans));
    for(auto [r, c]: lights) {
        ans[r][c] = 1;
    }
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }

}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        solve();
    }
}
