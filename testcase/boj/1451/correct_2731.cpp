#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, N) for(int i=0; i<N; i++)
#define all(x) x.begin(), x.end()

int R, C, arr[51][51], acc[51][51];

int f(int r1, int r2, int c1, int c2) {
    return acc[r2][c2] - acc[r1-1][c2] - acc[r2][c1-1] + acc[r1-1][c1-1];
}
int subp(int r1, int r2, int c1, int c2) {
    int res = 0;
    for(int r=r1; r<r2; r++) {
        res = max(res, f(r1, r, c1, c2) * f(r+1, r2, c1, c2));
    }
    for(int c=c1; c<c2; c++) {
        res = max(res, f(r1, r2, c1, c) * f(r1, r2, c+1, c2));
    }
    return res;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> R >> C;
    for(int i=1; i<=R; i++) {
        string s;
        cin >> s;
        for(int j=1; j<=C; j++) {
            arr[i][j] = s[j-1] - '0';
        }
    }
    for(int i=1; i<=R; i++) {
        for(int j=1; j<=C; j++) {
            acc[i][j] = acc[i-1][j] + acc[i][j-1] - acc[i-1][j-1] + arr[i][j];
        }
    }
    int res = 0;
    for(int r=1; r<R; r++) {
        res = max({
            res, 
            subp(1, r, 1, C) * f(r+1, R, 1, C), 
            f(1, r, 1, C) * subp(r+1, R, 1, C)});
    }
    for(int c=1; c<C; c++) {
        res = max({
            res, 
            subp(1, R, 1, c) * f(1, R, c+1, C), 
            f(1, R, 1, c) * subp(1, R, c+1, C)
        });
    }
    cout << res;
}
