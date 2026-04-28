#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll dp[21][21];
int main() {
  fast_io();
  int n, m;
  cin >> n >> m;

  dp[1][1] = 1;
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j <= i; j++) dp[i][j] = dp[i - 1][j - 1] + (i - 1) * dp[i - 1][j];
  }

  ll nom = 0, denom = 0;
  for (int i = 1; i <= m; i++) nom += dp[n][i];
  for (int i = 1; i <= n; i++) denom += dp[n][i];

  ll g = __gcd(nom, denom);
  nom /= g;
  denom /= g;
  cout << nom << '/' << denom;
}
