#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int a[MAX + 1];
vector<int> g[MAX + 1];

void solve() {
  int n, c;
  cin >> n >> c;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    g[a[i]].push_back(i);
  }

  ll cur = 0, dt = 0;
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 1; i <= c; i++) {
    cur += (g[i][0] - 1);
    if (g[i][0] == 1) dt++;
    else dt--;

    for (int j = 0; j < g[i].size(); j++) pq.push({2 * g[i][j], 2});
    for (int j = 0; j < g[i].size() - 1; j++) {
      pq.push({g[i][j] + g[i][j + 1], -2});
    }
  }

  while (!pq.empty() && pq.top().first <= 2) pq.pop();
  cur *= 2;

  ll ans = cur;
  for (int i = 3; i <= 2 * n; i++) {
    cur += dt;

    while (!pq.empty() && pq.top().first == i) {
      auto [v, d] = pq.top();
      pq.pop();
      dt += d;
    }

    ans = min(ans, cur);
  }

  ll g = __gcd(ans, 2LL * c);
  cout << ans / g << '/' << 2 * c / g << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
