#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 4001;
double dp[31][MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int B, N;
    cin >> B >> N;
    vector<int> arr(N+1);
    for(int i=1; i<=N; i++) {
        cin >> arr[i];
    }
    fill(dp[0] + 1, dp[0] + MX, LLONG_MAX / 2);
    for(int b=1; b<=B; b++) {
        for(int i=1; i<=N; i++) {
            dp[b][i] = INT_MAX;
            double sm = 0, smsq = 0;
            for(int j=i; j>=1; j--) {
                sm += arr[j];
                smsq += arr[j] * arr[j];
                double cost = smsq - (sm * sm / (i-j+1));
                dp[b][i] = min(dp[b][i], dp[b-1][j-1] + cost);
            }
        }
    }
    cout << fixed << setprecision(6) << (dp[B][N]);
}
