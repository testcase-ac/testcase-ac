#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXSN = 2000, MAXSN_B = 1000, INF = 0x3f3f3f3f;
int SN[MAXN], W[MAXN];
int cdist[MAXN * MAXSN], N;
vector<pii> adj[MAXN * MAXSN];

void dijk(int s) {
  for (int i = 0; i < N; ++i) for (int j = 0; j < SN[i]; ++j) {
    int soff = i * MAXSN + j, son = soff + MAXSN_B;
    cdist[soff] = cdist[son] = INF;
  }

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.emplace(0, s); cdist[s] = 0;

  while (!pq.empty()) {
    auto [cd, cn] = pq.top(); pq.pop();
    if (cd > cdist[cn]) continue;

    for (auto [nn, nd] : adj[cn]) {
      int ndist = cd + nd;
      if (ndist < cdist[nn]) {
        cdist[nn] = ndist;
        pq.emplace(ndist, nn);
      }
    }
  }
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ":\n";

  cin >> N;
  for (int i = 0; i < N; ++i) {
    int W; cin >> SN[i] >> W;
    for (int j = 0; j < SN[i]; ++j) {
      int soff = i * MAXSN + j, son = soff + MAXSN_B;
      adj[soff].emplace_back(son, W);
      adj[son].emplace_back(soff, 0);
    }

    for (int j = 0; j < SN[i] - 1; ++j) {
      int T; cin >> T;
      int son = i * MAXSN + j + MAXSN_B, eon = son + 1;
      adj[son].emplace_back(eon, T);
      adj[eon].emplace_back(son, T);
    }
  }

  int M; cin >> M;
  while (M--) {
    int m1i, s1i, m2i, s2i, ti; cin >> m1i >> s1i >> m2i >> s2i >> ti;
    --m1i; --s1i; --m2i; --s2i;

    int soff = m1i * MAXSN + s1i, eoff = m2i * MAXSN + s2i;
    adj[soff].emplace_back(eoff, ti);
    adj[eoff].emplace_back(soff, ti);
  }

  int Q; cin >> Q;
  while (Q--) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    --x1; --y1; --x2; --y2;

    int s = x1 * MAXSN + y1, e = x2 * MAXSN + y2;
    dijk(s);

    int ans = cdist[e];
    if (ans == INF) cout << "-1\n";
    else cout << ans << '\n';
  }

  // Clean up
  for (int i = 0; i < N; ++i) for (int j = 0; j < SN[i]; ++j) {
    int soff = i * MAXSN + j, son = soff + MAXSN_B;
    adj[soff].clear(); adj[son].clear();
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
