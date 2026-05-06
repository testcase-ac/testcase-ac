#include <bits/stdc++.h>
using namespace std;
int main() {
    int n,c;
    cin>>n>>c;
    long long t[n+1];
    t[0]=0;
    for(int i=1;i<=n;i++) cin>>t[i];
    sort(t,t+n+1);
    if(n<=c) {cout<<t[n];return 0;}
    long long dp[n+1][(n-2)/c+1];
    for(int i=2;i<=c;i++) dp[i][0]=t[i];
    for(int i=2;i<=n;i++) t[i]+=t[i-1];
    for(int i=2;i<=c;i++) {
        for(int j=1;j<=(n-2)/c;j++) {
            int k=min(i,j+1);
            dp[i][j]=dp[k][j-k+1]+t[k]+t[i]-t[i-1];k--;
            for(;k>1;k--) dp[i][j]=min(dp[i][j],dp[k][j-k+1]+t[k]+t[i]-t[i-1]);
        }
    } for(int i=c+1;i<=n;i++) {
        for(int j=0;j<=(n-i)/c;j++) {
            if(i==c+1) {
                dp[i][j]=dp[2][j]+t[i]-t[c]+t[1];
                for(int k=2;k<=min(j+1,c-1);k++) dp[i][j]=min(dp[i][j],dp[k+1][j-k+1]+t[k]+t[i]-t[i-1]);
            } else {
                dp[i][j]=dp[i-c][j+1]+t[i]-t[i-1];
                for(int k=1;k<=min(j+1,c-1);k++) dp[i][j]=min(dp[i][j],dp[i-c+k][j-k+1]+t[k]+t[i]-t[i-1]);
            }
        }
    } cout<<dp[n][0];
}
