#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
ll P[MAXN + 5], W[MAXN + 5];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i < N; ++i) cin >> W[i];
  while (M--) {
    int s, e, w; cin >> s >> e >> w;
    P[s] += w; P[e] -= w;
  }

  for (int i = 1; i < N; ++i) {
    P[i] += P[i - 1];
    ll m = P[i] / W[i], r = P[i] % W[i];

    ll cur = m * m * W[i];
    cur += (2 * m + 1) * r;
    cout << cur << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
