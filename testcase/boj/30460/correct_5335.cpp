#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 2e5+5;
int arr[MX], dp[MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i=1; i<=N; i++)
        cin >> arr[i];
    
    for(int i=N; i>=1; i--) {
        dp[i] = dp[i+1] + arr[i];
        dp[i] = max(2*(arr[i] + arr[i+1] +arr[i+2]) + dp[i+3], dp[i]);
    }
    cout << dp[1];
    
}
