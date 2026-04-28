#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, INF = 0x3f3f3f3f;
vector<pii> adj[MAXN + 1];
int cdist[MAXN + 1];

void solve() {
  int N, P, K; cin >> N >> P >> K;
  while (P--) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  int MAX_R = 1e6 + 1;
  int l = 0, r = MAX_R;
  deque<int> Q;

  while (l < r) {
    int m = (l + r) / 2;

    fill(cdist + 1, cdist + N + 1, INF);
    cdist[1] = 0; Q.push_back(1);
    while (!Q.empty()) {
      int v = Q.front(); Q.pop_front();
      for (auto& [u, w] : adj[v]) {
        if (w <= m) {
          if (cdist[u] > cdist[v]) {
            cdist[u] = cdist[v];
            Q.push_front(u);
          }
        }
        else {
          if (cdist[u] > cdist[v] + 1) {
            cdist[u] = cdist[v] + 1;
            Q.push_back(u);
          }
        }
      }
    }

    if (cdist[N] <= K) r = m;
    else l = m + 1;
  }

  if (l == MAX_R) cout << "-1\n";
  else cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
