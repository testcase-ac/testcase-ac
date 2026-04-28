#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll a[100'000];
ll dp[100'001][4];
ll n, s;

ll r(int pos, int d) {
  if (pos == n) return d == 4;
  if (d >= 4) return 0;

  if (dp[pos][d] == -1) {
    ll ans = r(pos + 1, d);
    if (a[pos] == s * (d + 1)) ans += r(pos + 1, d + 1);
    dp[pos][d] = ans;
  }
  return dp[pos][d];
}

int main() {
  fast_io();

  cin >> n;
  cin >> a[0];
  for (int i = 1; i < n; i++) {
    cin >> a[i];
    a[i] += a[i - 1];
  }
  s = a[n - 1] / 4;
  memset(dp, -1, sizeof(dp));

  cout << r(0, 0);
}
