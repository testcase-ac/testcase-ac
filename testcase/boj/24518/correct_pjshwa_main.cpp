#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;
ll n, m;

ll msum(ll s, ll e) {
  ll em = e % m, sm = s % m;
  ll es = em * (em + 1) / 2, ss = m * (m - 1) / 2 - sm * (sm - 1) / 2;
  e -= em, s -= sm;
  s += m;

  ll res = (es + ss) % MOD;
  ll addend = (MOD + ((e - s) / m)) % MOD;
  addend = (addend * ((m * (m - 1) / 2) % MOD)) % MOD;
  res = (res + addend) % MOD;
  return res;
}

void solve() {
  cin >> n >> m;

  int sq = sqrt(n);
  ll ans = 0;
  for (int i = 1; i <= sq; i++) {
    ans = (ans + (ll)(n / i) * (i % m)) % MOD;
  }

  int last = n;
  for (int i = 1; i < n / sq; i++) {
    int s = n / (i + 1) + 1;
    ans = (ans + (ll)msum(s, last) * i) % MOD;
    last = s - 1;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
