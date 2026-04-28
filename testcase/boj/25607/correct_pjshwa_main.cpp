#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXK = 15, INF = 0x3f3f3f3f;
int cdist[MAXN + 1][1 << MAXK];
int P[MAXN + 1], W[MAXN + 1];

void solve() {
  int N, K; cin >> N >> K;

  memset(P, -1, sizeof(P));
  for (int i = 0; i < K; ++i) {
    int r, c; cin >> r >> c;
    P[c] = N - r;
    W[c] = i;
  }

  memset(cdist, 0x3f, sizeof(cdist));
  int C; cin >> C;

  queue<pii> q; int mask = (1 << K) - 1;
  q.emplace(C, mask); cdist[C][mask] = 0;

  while (!q.empty()) {
    auto [p, s] = q.front(); q.pop();
    // cout << "p: " << p << ", s: " << s << ", cdist[p][s]: " << cdist[p][s] << ", P[p]: " << P[p] << endl;

    int d = cdist[p][s];
    for (int np : {p - 1, p + 1}) {
      if (np < 1 || np > N) continue;
      if (cdist[np][s] > d + 1) {
        cdist[np][s] = d + 1;
        q.emplace(np, s);
      }
    }

    if (P[p] == -1 || P[p] <= d) continue;

    int i = W[p];
    if (!(s >> i & 1)) continue;

    // remove asteroid i
    int ns = s ^ (1 << i);
    if (cdist[p][ns] > d + 1) {
      cdist[p][ns] = d + 1;
      q.emplace(p, ns);
    }
  }

  int ans = INF;
  for (int p = 1; p <= N; ++p) ans = min(ans, cdist[p][0]);
  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
