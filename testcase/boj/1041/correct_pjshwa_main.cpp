#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N, a[6];
  cin >> N;
  for (int i = 0; i < 6; i++) cin >> a[i];

  if (N == 1) {
    ll sum = 0, maxx = 0;
    for (int i = 0; i < 6; i++) sum += a[i], maxx = max(maxx, (ll)a[i]);
    cout << sum - maxx << '\n';
    return;
  }

  int min1 = INF;
  for (int i = 0; i < 6; i++) min1 = min(min1, a[i]);

  int min2 = min({
    a[0] + a[1],
    a[1] + a[5],
    a[5] + a[4],
    a[4] + a[0]
  });
  for (int u : {0, 1, 4, 5}) for (int v : {2, 3}) {
    min2 = min(min2, a[u] + a[v]);
  }

  int min3 = INF;
  vector<pii> vv = {{0, 1}, {1, 5}, {5, 4}, {4, 0}};
  for (auto [u, v] : vv) for (int w : {2, 3}) {
    min3 = min(min3, a[u] + a[v] + a[w]);
  }

  ll cnt3 = 4, cnt2 = 8 * (N - 2) + 4;
  ll cnt1 = 5 * (ll)(N - 2) * (N - 2) + 4 * (N - 2);
  ll ans = cnt1 * min1 + cnt2 * min2 + cnt3 * min3;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
