#include <bits/stdc++.h>
using namespace std;
const int MXP = 1132502, MX = 152;
bitset<MXP> dp[MX];
int arr[MX], N, K;
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    cin >> K;
    dp[0][0] = 1;
    for(int i = 1; i <= N + 1; i++) {
        dp[i] = dp[i - 1];
        int sum = 0;
        for(int j = i - 1; j >= 1; j--) {
            sum += arr[j] * (i - j);
            dp[i] |= (dp[j - 1] << sum);
        }
    }
    for(int p = K; p < MXP; p++) {
        if(!dp[N + 1][p]) {
            return !(cout << p);
        }
    }
    cout << K;
}
