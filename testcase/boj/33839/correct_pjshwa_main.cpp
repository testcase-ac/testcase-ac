#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
ll P[MAXN + 1];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 1; i <= N; ++i) cin >> P[i], P[i] += P[i - 1];
  if (N == 1) return cout << P[1] << "\n1 1\n", void();

  ll ans = -P[N], l = 2, r = 1;
  priority_queue<pair<ll, int>> pq;
  for (int i = 1; i <= N; ++i) {
    pq.push({-2 * P[i - 1], -i});
    while (-pq.top().second < i - K) pq.pop();
    assert(!pq.empty());

    ll cur = 2 * P[i] - P[N] + pq.top().first, p = -pq.top().second;
    if (ans < cur) ans = cur, l = p, r = i;
    else if (ans == cur && l > p) l = p, r = i;
    else if (ans == cur && l == p && r > i) r = i;
  }
  cout << ans << '\n' << l << ' ' << r << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
