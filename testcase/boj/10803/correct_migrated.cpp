#include <bits/stdc++.h>
using namespace std;
int dp[10001][101];
int solve(int n,int m) {
    if(n%m==0) return n/m;
    int& r=dp[n][m];
    if(r!=-1) return r;
    r=n*m;
    if(n>=3*m) r=min(r,solve(n-m,m)+1);
    else {
        for(int i=1;i<=n/2;i++) r=min(r,solve(n-i,m)+solve(i,m));
        for(int j=1;j<=m/2;j++) r=min(r,solve(n,m-j)+solve(n,j));
    } return r;
}
int main() {
    memset(dp,-1,sizeof(dp));
    int n,m;
    cin>>n>>m;
    cout<<solve(n,m);
}
