#include <bits/stdc++.h>
using namespace std;
int dp[101][101][2];

int main() {
	//ios::sync_with_stdio(0);cin.tie(0);
    int T;
    cin >> T;
    dp[1][0][0] = dp[1][0][1] = 1;
    for(int i=2; i<=100; i++) {
        dp[i][0][0] = dp[i-1][0][1] + dp[i-1][0][0];
        dp[i][0][1] = dp[i-1][0][0];
        for(int j=0; j<i; j++) {
            dp[i][j][0] = dp[i-1][j][1] + dp[i-1][j][0];
            dp[i][j][1] = dp[i-1][j][0] + dp[i-1][j-1][1];
        }
    }
    while(T--) {
        int n,k;
        cin >> n >> k;
        if(k >= n) {
            cout << "0\n";
            continue;
        }
        cout << dp[n][k][0] + dp[n][k][1] << '\n';
    }
}
