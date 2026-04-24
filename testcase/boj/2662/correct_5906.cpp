#include <bits/stdc++.h>
#define sz(x) ((int)((x).size()))
using namespace std;

int dp[20][301], inv[20][301], profit[20][301];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i=1; i<=n; i++) {
        int t;
        cin >> t;
        for(int j=0; j<m; j++)
            cin >> profit[j][i];
    }
    for(int i=0; i<=n; i++) {
        dp[0][i] = profit[0][i];
        inv[0][i] = i;
    }
    for(int i=1; i<m; i++) {
        for(int j=1; j<=n; j++) {
            for(int k=0; k<=j; k++) {
                int p = dp[i-1][j-k] + profit[i][k];
                if(p > dp[i][j]) {
                    dp[i][j] = p;
                    inv[i][j] = k;
                }
            }
        }
    }
    cout << dp[m-1][n] << '\n';
    vector<int> ans;
    int i = m-1, amount = n;
    while(i >= 0) {
        ans.push_back(inv[i][amount]);
        amount -= inv[i][amount];
        i--;
    }
    reverse(ans.begin(), ans.end());
    for(int a: ans) cout << a << ' ';
}
