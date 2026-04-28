#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4, MOD = 1000;
int P[MAX + 1];

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
  int n; cin >> n;
  for (int i = 1; i <= n; ++i) cin >> P[i];

  // count sizes of cycles
  vector<int> cycle_sizes;
  vector<bool> vis(n + 1);
  for (int i = 1; i <= n; ++i) {
    if (vis[i]) continue;
    int cur = i, cnt = 0;
    while (!vis[cur]) {
      vis[cur] = true;
      cur = P[cur];
      ++cnt;
    }
    cycle_sizes.push_back(cnt);
  }

  sort(cycle_sizes.begin(), cycle_sizes.end());
  ll ans = 1, z = cycle_sizes.size();
  for (int i = 0; i < z; ++i) {
    int csz = cycle_sizes[i];

    // this defies tournament definition
    if (csz % 2 == 0) return cout << "0\n", void();

    // let 2 cycles size be a, b
    // then there are 2^(gcd(a, b)) ways to connect them
    ll cur = lpow(2, csz / 2, MOD);
    for (int j = i + 1; j < z; ++j) {
      int g = __gcd(csz, cycle_sizes[j]);
      cur = (cur * lpow(2, g, MOD)) % MOD;
    }
    ans = (ans * cur) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
