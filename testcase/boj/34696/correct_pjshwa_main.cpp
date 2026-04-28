#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXM = 50000;
ll vis[MAXM], D[MAXM];

ll sq_d(pii& a, pii& b) {
  return (ll)(a.first - b.first) * (a.first - b.first)
       + (ll)(a.second - b.second) * (a.second - b.second);
}

void solve() {
  int N, M; cin >> N >> M;
  vector<pii> P(M);
  for (auto& [x, y] : P) cin >> x >> y;
  int s1; cin >> s1; --s1;

  vis[s1] = 1; cout << s1 + 1 << '\n';
  for (int i = 0; i < M; ++i) D[i] = sq_d(P[s1], P[i]);

  for (int p = 1; p < N; ++p) {
    ll md = 0, mu;
    for (int i = 0; i < M; ++i) {
      if (vis[i]) continue;
      md = max(md, D[i]);
    }
    for (mu = 0; mu < M; ++mu) {
      if (vis[mu]) continue;
      if (D[mu] == md) break;
    }
    vis[mu] = 1; cout << mu + 1 << '\n';
    for (int i = 0; i < M; ++i) D[i] = min(D[i], sq_d(P[mu], P[i]));
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
