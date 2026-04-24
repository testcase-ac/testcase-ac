#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 2005;
int arr[MX][MX], acc[MX][MX], ans[MX*2][MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int R, C, Q;
    cin >> R >> C >> Q;
    for(int r=1; r<=R; r++) {
        for(int c=1; c<=C; c++) {
            cin >> arr[r][c];
            acc[r][c] = acc[r-1][c] + arr[r][c];
        }
    }
    for(int diff=1; diff<R+C; diff++) {
        for(int c=1; c<=C; c++) {
            int r = min(R, diff + c - C);
            if(r >= 1) {
                ans[diff][c] = ans[diff][c-1] + acc[r][c];
            }
        }
    }
    while(Q--) {
        int r, c;
        cin >> r >> c;
        cout << ans[r + C - c][c] << '\n';
    }
}
