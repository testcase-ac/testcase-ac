#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin>>n;
    vector<int> c;
    for(int i=1;;i++) {
        int t=i*i*2-i;
        if(t>1000000) break;
        c.push_back(t);
    } vector<int> dp(n+1,10001);
    dp[0]=0;
    for(int i=0;i<c.size();i++) for(int j=c[i];j<=n;j++) dp[j]=min(dp[j],dp[j-c[i]]+1);
    cout<<dp[n];
}
