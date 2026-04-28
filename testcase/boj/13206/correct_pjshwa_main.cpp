#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, MOD = 1e9 + 7;
int lp[MAX + 1];
vector<int> pr;
int total[MAX + 1];

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void solve() {
  memset(total, 0, sizeof(total));

  int n, x;
  cin >> n;

  unordered_map<int, int> occ;
  for (int i = 0; i < n; i++) {
    cin >> x;
    while (x > 1) {
      occ[lp[x]]++;
      x /= lp[x];
    }
    for (auto [k, v] : occ) total[k] = max(total[k], v);
    occ.clear();
  }
  
  ll ans = 1;
  for (int i = 2; i <= MAX; i++) {
    ans = ans * lpow(i, total[i], MOD) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t;
  cin >> t;
  while (t--) solve();
}
