#include <bits/stdc++.h>
using namespace std;
#define int long long
char arr[301][301];
int dp[301][301], sub[301][301], subrow[301], subcol[301], gadd;
const int MOD = 1e9 + 7;
int dr[] = {-1,-1,-1,0,0,0,1,1,1}, dc[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int R, C, L;
    cin >> R >> C >> L;
    string tgt;
    cin >> tgt;
    for(int r=0; r<R; r++) {
        cin >> arr[r];
        for(int c=0; c<C; c++) {
            if(arr[r][c] == tgt[0]) 
                dp[r][c] = 1;
        }
    }
    for(int i=1; i<tgt.size(); i++) {
        char ch = tgt[i];
        memset(sub, 0, sizeof sub);
        memset(subrow, 0, sizeof subrow);
        memset(subcol, 0, sizeof subcol);
        gadd = 0;
        for(int r=0; r<R; r++) {
            for(int c=0; c<C; c++) {
                if(!dp[r][c]) {
                    continue;
                }
                gadd += dp[r][c];
                subrow[r] += dp[r][c];
                if(r - 1 >= 0) subrow[r-1] += dp[r][c];
                if(r + 1 < R) subrow[r+1] += dp[r][c];
                
                subcol[c] += dp[r][c];
                if(c - 1 >= 0) subcol[c-1] += dp[r][c];
                if(c + 1 < C) subcol[c+1] += dp[r][c];
                
                for(int tr=r-1; tr<=r+1; tr++) {
                    for(int tc=c-1; tc<=c+1; tc++) {
                        if(tr < 0 || tr >= R || tc < 0 || tc >= C) {
                            continue;
                        }
                        sub[tr][tc] += (MOD - dp[r][c]);
                    }
                }
                for(int tr=r-2; tr<=r+2; tr+=4) {
                    for(int tc=c-2; tc<=c+2; tc+=4) {
                        if(tr < 0 || tr >= R || tc < 0 || tc >= C) {
                            continue;
                        }
                        sub[tr][tc] += dp[r][c];
                    }
                }
            }
        }
        memset(dp, 0, sizeof dp);
        int cur = 0;
        for(int r=0; r<R; r++) {
            subrow[r] %= MOD;
            for(int c=0; c<C; c++) {
                subcol[r] %= MOD;
                sub[r][c] %= MOD;
                if(arr[r][c] != ch) {
                    continue;
                }
                dp[r][c] = (gadd - subrow[r] - subcol[c] - sub[r][c] + MOD * 3) % MOD;
                // printf("(%d %d): dp = %lld - %lld - %lld - %lld = %lld\n", r, c, gadd, subrow[r], subcol[c], sub[r][c], dp[r][c]);
                cur += dp[r][c];
            }
        }
        // printf("at %c, cur = %lld\n", ch, cur);
    }
    int ans = 0;
    for(int r=0; r<R; r++) {
        for(int c=0; c<C; c++) {
            ans += dp[r][c];
        }
    }
    cout << ans % MOD << '\n';
}
