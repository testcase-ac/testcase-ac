#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main() {
    cin.tie(0);
    int n;
    vector<int> dp(1<<24,0);
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++) {
        cin>>a[i];
        dp[a[i]]++;
    } for(int j=0;j<24;j++) for(int i=0;i<(1<<24);i++) if(!(i&(1<<j))) dp[i]+=dp[i|(1<<j)];
    for(int i=0;i<(1<<24);i++) {if(dp[i]>1) dp[i]=__builtin_popcount(i);}
    for(int j=0;j<24;j++) for(int i=0;i<(1<<24);i++) if(i&(1<<j)) dp[i]=max(dp[i],dp[i^(1<<j)]);
    int r=0;
    for(int i:a) r+=dp[i];
    cout<<r;
}
