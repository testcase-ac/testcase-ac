#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1e9+7;
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
int main() {
    int n,r,g,b;
    cin>>n>>r>>g>>b;
    ll f[101],invf[101];
    f[0]=1;
    for(int i=1;i<=100;i++) f[i]=f[i-1]*i%M;
    invf[100]=pw(f[100],M-2);
    for(int i=99;i>=0;i--) invf[i]=invf[i+1]*(i+1)%M;
    ll dp[n+1][r+1][g+1][b+1];
    memset(dp,0,sizeof(dp));
    dp[0][r][g][b]=1;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<8;j++) {
            int t=__builtin_popcount(j);
            if(i%t) continue;
            int k=i/t;
            int R=j%2*k,G=(j/2)%2*k,B=(j/4)*k;
            ll w=f[R+G+B]*invf[R]%M*invf[G]%M*invf[B]%M;
            for(int x=R;x<=r;x++) for(int y=G;y<=g;y++) for(int z=B;z<=b;z++) dp[i][x-R][y-G][z-B]+=dp[i-1][x][y][z]*w;
        }
    } ll ans=0;
    for(int i=0;i<=r;i++) for(int j=0;j<=g;j++) for(int k=0;k<=b;k++) ans+=dp[n][i][j][k];
    cout<<ans;
}
