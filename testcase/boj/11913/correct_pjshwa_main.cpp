#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

map<pll, ll> d;
ll a, b, p, q;
ll dfs(pll v) {
  if (d.count(v)) return d[v];

  auto [a, b] = v;
  if (a == 0 || b == 0) return d[v] = 0;

  ll ret = dfs({b, a % b}) + p;

  ll na = a, nb = b;
  if (na >= nb) na -= nb;
  else nb -= na;
  ret = min(ret, dfs({na, nb}) + q);

  return d[v] = ret;
}

void solve() {
  cin >> a >> b >> p >> q;

  d.clear();
  cout << dfs({a, b}) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
