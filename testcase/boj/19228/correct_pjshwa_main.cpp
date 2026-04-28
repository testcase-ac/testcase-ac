#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll C(int n, int k) {
  ll ans = 1;
  for (int i = 1; i <= k; i++) {
    ans *= (n - i + 1);
    ans /= i;
  }
  return ans;
}

int u[30], n;
ll d[30];

ll solve(int s) {
  ll res = 1;
  map<int, int> rems;
  for (int i = s; i < n; i++) rems[u[i]]++;

  int e = n - s, vac = 0;
  for (auto it = rems.rbegin(); it != rems.rend(); it++) {
    auto [k, v] = *it;
    while (e >= 1 && e >= k) e--, vac++;

    res *= C(vac, v);
    vac -= v;
  }
  return res;
}

void solve() {
  ll k;
  cin >> k;

  int it = 2;
  n = 0;
  while (k) {
    u[it - 2] = k % it;
    n++;
    k /= it;
    it++;
  }
  sort(u, u + n);

  int zc = 0;
  while (zc < n && u[zc] == 0) zc++;

  ll ans = solve(0), sub = solve(1);
  if (zc) ans -= sub;
  cout << ans - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
