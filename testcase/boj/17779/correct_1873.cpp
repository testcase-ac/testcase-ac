#include <bits/stdc++.h>
using namespace std;

int arr[21][21], bound[21][21];
int N;
int solve(int r, int c, int d1, int d2) {
    memset(bound, 0, sizeof bound);
    bound[r][c] = 5;
    if(r-d1 <= 0 || c + d1 + d2 > N || r+d2 > N)
        return INT_MAX;
    for(int t=1; t<=d1; t++) {
        bound[r-t][c+t] = 5;
    }
    int sr = r-d1, sc = c+d1;
    for(int t=1; t<=d2; t++) {
        bound[sr+t][sc+t] = 5;
    }
    for(int t=1; t<=d2; t++) {
        bound[r+t][c+t] = 5;
    }
    sr = r+d2, sc = c+d2;
    for(int t=1; t<=d1; t++) {
        bound[sr-t][sc+t] = 5;
    }

    for(int tr=r-d1+1; tr<r+d2; tr++) {
        int tc = 1;
        while(bound[tr][tc] != 5) {
            tc++;
        }
        tc++;
        while(bound[tr][tc] != 5) {
            bound[tr][tc] = 5;
            tc++;
        }
    }

    for(int tr=1; tr<=N; tr++) {
        for(int tc=1; tc<=N; tc++) {
            if(bound[tr][tc] == 5) continue;
            if(tr < r && tc <= c + d1 && tr + tc < r + c) bound[tr][tc] = 1;
            else if(tr <= r - d1 + d2 && tc > c + d1 && tc - tr >= c-r+d1*2 ) bound[tr][tc] = 2;
            else if(tr >= r && tc < c + d2 && tc - tr <= c-r) bound[tr][tc] = 3;
            else bound[tr][tc] = 4;
        }
    }

    // for(int i=1; i<=N; i++) {
    //     for(int j=1; j<=N; j++) {
    //         cout << bound[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }
    vector<int> buk(5);
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            buk[bound[i][j]-1] += arr[i][j];
        }
    }
    int mx = 0, mn = INT_MAX;
    for(int i=0; i<5; i++) {
        mx = max(mx, buk[i]);
        mn = min(mn, buk[i]);
    }
    return mx - mn;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for(int r=1; r<=N; r++) {
        for(int c=1; c<=N; c++) {
            cin >> arr[r][c];
        }
    }
    int ans = INT_MAX;
    for(int r=1; r<=N; r++) {
        for(int c=1; c<=N; c++) {
            for(int d1=1; d1<=N; d1++) {
                for(int d2=1; d2<=N; d2++) {
                    int s = solve(r, c, d1, d2);
                    ans = min(s, ans);
                }
            }
        }
    }
    cout << ans;
}
