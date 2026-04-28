#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int dp[200001];

int g(int n) {
  if (n == 1) return 1;

  if (dp[n] == -1) dp[n] = 1 + g(n - g(g(n - 1)));
  return dp[n];
}

int main() {
  memset(dp, -1, sizeof(dp));
  dp[1] = 1;
  
  int n;
  cin >> n;
  if (n <= 200) cout << g(n);
  else {
    g(200000);

    ll s = 0;
    int p = 0;
    for (int i = 1; i <= 200000; i++) {
      s += (i * dp[i]);

      if (s >= n) {
        s -= (i * dp[i]);
        cout << p + 1 + (n - s) / i;
        return 0;
      }

      p += dp[i];
    }
  }

}
