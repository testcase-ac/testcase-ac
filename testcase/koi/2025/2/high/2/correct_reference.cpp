#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int MOD = 1e9 + 7;

int a[6060];
ll dp[6060][3030], dp2[6060][3030];

void dfs(int s, int e, int lim){
    fill(dp[s]+1, dp[s]+lim+1, 1);
    fill(dp2[s]+1, dp2[s]+lim+2, 1);

    for (int i=s+1;i<e;i=a[i]+1){
        dfs(i, a[i], lim+1);
        for (int j=1;j<=lim+1;j++){
            dp2[s][j] = dp2[s][j] * dp[i][j] % MOD;
        }
    }
    
    for (int j=1;j<=lim;j++){
        dp[s][j] = dp2[s][j+1] * j % MOD;
        dp[s][j] -= dp2[s][j];
        if (dp[s][j] < 0) dp[s][j] += MOD;
    }
}

void solve(){
    int n;
    scanf("%d", &n);

    for (int i=1;i<=n;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        a[x] = y;
    }

    ll ans = 1;
    for (int i=1;i<=n*2;i=a[i]+1){
        dfs(i, a[i], 1);
        ans = ans * dp[i][1] % MOD;
    }

    printf("%lld\n", ans);
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--) solve();
}