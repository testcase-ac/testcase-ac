#include <bits/stdc++.h>
// 제 코드가 아니며, 저가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
using namespace std;
using ll = long long;
#define mp make_pair
#define all(x) x.begin(), x.end()
#define x first
#define y second

int dp[11][1001010];

void solve() {

    int t, n, d, k;
    cin >> t >> n >> d >> k;

    vector<int> A(n);
    for (auto& i : A) cin >> i;
    sort(all(A));


    int pv = 0;
    for (int i = 1; i <= n; i++) {
        int v = A[i - 1];
        
        while (pv < i && A[pv] + d <= v) pv++;
        for (int j = 0; j < k; j++) {
            dp[j + 1][i] = max(dp[j + 1][i - 1], dp[j][pv] + i - pv);
        }
    }
    cout << dp[k][n];    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
