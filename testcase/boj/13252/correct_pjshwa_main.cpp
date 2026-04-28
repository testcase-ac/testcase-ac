#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll M;
map<pair<ll, ll>, double> dp;

double rec(ll n, ll k) {
  if (dp.count({n, k})) return dp[{n, k}];

  if (n == 0) return dp[{n, k}] = 0;
  if (k == 1) {
    return dp[{n, k}] = n == 1 ? (double)(M - 1) / M : 1;
  }

  ll q = n / M, r = n % M;
  double ret = (double)r / M * rec(n - q - 1, k - 1) + (double)(M - r) / M * rec(n - q, k - 1);
  return dp[{n, k}] = ret;
}

void solve() {
  ll N, K; cin >> N >> M >> K;
  cout << fixed << setprecision(10) << rec(N, K) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
