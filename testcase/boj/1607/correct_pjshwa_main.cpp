#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6, MOD = 9901;
ll d[MAX + 1], T3[MAX + 1];

ll T(ll n) {
  if (d[n] != -1) return d[n];
  if (n == 1) return d[1] = 1;

  ll k = n - round(sqrt(2 * n + 1)) + 1;
  return d[n] = (2 * T(k) + T3[n - k]) % MOD;
}

void solve() {
  int n;
  cin >> n;
  cout << T(n) << '\n';
}

int main() {
  fast_io();

  T3[1] = 1;
  for (int i = 2; i <= MAX; i++) T3[i] = (T3[i - 1] * 2 + 1) % MOD;
  memset(d, -1, sizeof(d));

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
