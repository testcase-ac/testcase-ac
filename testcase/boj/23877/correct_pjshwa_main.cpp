#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
int ta[MAX + 1], tb[MAX + 1];
ll dt[2 * MAX + 10];

void solve() {
  int n, m;
  cin >> n >> m;
  vector<pii> q(n);
  for (int i = 0; i < n; i++) cin >> q[i].first >> q[i].second;
  for (auto [a, b] : q) ta[a]++, tb[b]++;
  for (auto [a, b] : q) for (int j = 0; j <= m; j++) dt[j + a] += ta[j], dt[j + b + 1] -= tb[j];

  ll s = 0;
  for (int j = 0; j <= 2 * m; j++) s += dt[j], cout << s << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
