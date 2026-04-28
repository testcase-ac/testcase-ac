#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6, INF = 1e9 + 7;
int minh[MAX + 1], maxh[MAX + 1];
int mint[MAX + 1], maxt[MAX + 1];
int h[MAX + 1], t[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> h[i] >> t[i];

  minh[1] = h[1] ? h[1] : INF;
  maxt[1] = t[1] ? t[1] : -INF;
  for (int i = 2; i <= n; i++) {
    minh[i] = minh[i - 1];
    maxt[i] = maxt[i - 1];
    if (h[i]) minh[i] = min(minh[i], h[i]);
    if (t[i]) maxt[i] = max(maxt[i], t[i]);
  }
  maxh[n] = h[n] ? h[n] : -INF;
  mint[n] = t[n] ? t[n] : INF;
  for (int i = n - 1; i >= 1; i--) {
    maxh[i] = maxh[i + 1];
    mint[i] = mint[i + 1];
    if (h[i]) maxh[i] = max(maxh[i], h[i]);
    if (t[i]) mint[i] = min(mint[i], t[i]);
  }

  int ans = -1;
  for (int i = 1; i < n; i++) {
    if (minh[i] > maxh[i + 1] && maxt[i] < mint[i + 1]) ans = max(ans, i);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
