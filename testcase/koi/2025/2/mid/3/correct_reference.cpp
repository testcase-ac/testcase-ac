#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const ll INF = 2e17;
 
int n, m, nxt[300300][20];
ll dp[300300][20], x[300300], p[300300];
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> x[i] >> p[i];
    cin >> m;
    
    for(int i=1;i<n;i++) {
        ll pcur = p[i];
        while(x[i] + pcur < x[i+1]) {
            dp[i][0] += pcur+1;
            pcur <<= 1;
        }
        nxt[i][0] = upper_bound(x+i+1, x+1+n, x[i]+pcur)-x-1;
        dp[i][0] += 1 + x[i]+pcur - x[nxt[i][0]];
    }
    dp[n][0] = INF, nxt[n][0] = n;

    for(int j=1;j<20;j++) for(int i=1;i<=n;i++) {
        dp[i][j] = min(dp[i][j-1] + dp[nxt[i][j-1]][j-1], INF);
        nxt[i][j] = nxt[nxt[i][j-1]][j-1];
    }
 
 
    while(m--) {
        ll s, t; cin >> s >> t;
 
        int k = upper_bound(x+1, x+1+n, s)-x-1;
        if(k == 0 || s-x[k] >= t) {
            cout << s-t << "\n";
            continue;
        }

        t -= s-x[k];
        for(int i=19;i>=0;i--) if(dp[k][i] <= t) t -= dp[k][i], k = nxt[k][i];

        if(t == 0) {
            cout << x[k] << "\n";
            continue;
        }

        ll pcur = p[k];
        while(pcur+1 < t) {
            t -= pcur+1;
            pcur <<= 1;
        }
        cout << x[k]+pcur-t+1 << "\n";
    }
}
