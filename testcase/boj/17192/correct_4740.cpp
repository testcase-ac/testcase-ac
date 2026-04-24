#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[401][401], a[401], n;
int f(int t, int k) {
    if(dp[t][k] != -1)
        return dp[t][k];
    if(t == n)
        return 0;
    if(!k)
        return 0x3f3f3f3f;
    int &ret = dp[t][k];
    ret = INT_MAX;
    int cur = 0, h = 0;
    for(int i=t; i<n; i++) {
        if(a[i] > h) {
            cur += (a[i]-h)*(i-t);
            h = a[i];
        } else {
            cur += h - a[i];
        }
        ret = min(ret, cur + f(i+1, k-1));
    }
    return ret;
}
int32_t main() {
    ios::sync_with_stdio(0);cin.tie(0);
    memset(dp, -1, sizeof dp);
    int k;
    cin >> n >> k;
    for(int i=0; i<n; i++) {
        cin >> a[i];
    }
    cout << f(0, k+1);
}
