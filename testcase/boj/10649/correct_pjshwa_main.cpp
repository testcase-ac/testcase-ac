#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 1 << 20, INF = 1e18;
ll d[MAX];
ll hgt[MAX], wgt[MAX], str[MAX];

void solve() {
  int N, H;
  cin >> N >> H;
  for (int i = 0; i < N; i++) cin >> hgt[i] >> wgt[i] >> str[i];

  fill(d, d + (1 << N), -INF);
  d[0] = INF;

  for (int s = 0; s < (1 << N); s++) {
    ll wsum = 0;
    for (int b = 0; b < N; b++) {
      if (!(s & (1 << b))) continue;
      wsum += wgt[b];
    }

    // Put cow b at bottom
    for (int b = 0; b < N; b++) {
      if (!(s & (1 << b))) continue;

      d[s] = max(d[s], min(d[s ^ (1 << b)], str[b] - wsum + wgt[b]));
    }
  }

  ll ans = -1;
  for (int s = 1; s < (1 << N); s++) {
    ll hsum = 0;
    for (int b = 0; b < N; b++) {
      if (!(s & (1 << b))) continue;
      hsum += hgt[b];
    }

    if (hsum >= H) ans = max(ans, d[s]);
  }

  if (ans == -1) cout << "Mark is too tall\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
