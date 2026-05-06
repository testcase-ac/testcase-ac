#include <bits/stdc++.h>
using namespace std;
bool x[1000];
int main() {
    int n,t,k,m=1e9;
    cin>>n>>k;
    for(int i=0;i<n;i++) {
        cin>>t;
        x[t-1]=1;
        m=min(m,t-1);
    } vector<int> a;
    for(int i=m+1;i<1000;i++) if(x[i]) a.push_back(i-m);
    if(a.empty()) {cout<<(m+1)*k;return 0;}
    vector<int> dp(a.back()*k+1,1000000000);
    dp[0]=0;
    for(int i:a) {
        for(int j=i;j<dp.size();j++) dp[j]=min(dp[j],dp[j-i]+1);
    } for(int i=0;i<dp.size();i++) if(dp[i]<=k) cout<<i+k*(m+1)<<' ';
}
