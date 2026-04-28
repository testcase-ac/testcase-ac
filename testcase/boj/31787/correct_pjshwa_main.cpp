#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 2e18;

map<ll, ll> dp;
ll f(ll n) {
  if (dp.count(n)) return dp[n];
  if (n % 16 == 0) return dp[n] = f(n / 4) + 1;
  if (n % 4 == 0) {
    int r = n % 16;
    return dp[n] = min(f(n - r) + r / 4, f(n + 16 - r) + (16 - r) / 4);
  }
  int r = n % 4;
  return dp[n] = min(f(r) + (ll)n / 4, f(4 * n) + 1);
}

void solve() {
  ll N; cin >> N;
  cout << f(N) << '\n';
}

int main() {
  fast_io();

  dp[0] = 0;
  dp[1] = 2;
  dp[2] = dp[3] = 3;
  dp[4] = 1;

  int t = 1;
  cin >> t;
  while (t--) solve();
}
