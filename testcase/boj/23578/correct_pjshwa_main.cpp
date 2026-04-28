#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
ll a[MAX], e[MAX];

void solve() {
  int n;
  cin >> n;
  if (n == 1) return cout << "0\n", void();

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    cin >> a[i], e[i] = 1, ans += a[i];
    pq.push({a[i] * (2 * e[i] + 1), i});
  }

  for (int i = 0; i < n - 2; ++i) {
    auto [x, idx] = pq.top();
    pq.pop();

    ans += x;
    e[idx]++;
    pq.push({a[idx] * (2 * e[idx] + 1), idx});
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
