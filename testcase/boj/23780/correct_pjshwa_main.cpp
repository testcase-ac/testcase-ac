#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXC = 2, MAXN = 1e4, INF = 1e18;
ll A[MAXN], Fv[MAXC][MAXN], Fd[MAXC][MAXN];
vector<pii> adj[MAXN];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int j = 0; j < M; ++j) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  memset(Fv, -1, sizeof(Fv));
  for (int j = 0; j < MAXC; ++j) fill(Fd[j], Fd[j] + N, INF);

  using T = tuple<ll, int, int>;
  priority_queue<T, vector<T>, greater<T>> pq;
  for (int i = 0; i < N; ++i) {
    pq.emplace(A[i], i, i);
  }

  while (!pq.empty()) {
    auto [w, u, s] = pq.top(); pq.pop();

    int j;
    for (j = 0; j < MAXC; ++j) {
      if (Fv[j][u] == -1 || Fv[j][u] == s) break;
    }
    
    // more than 2 vertices have visited u already
    if (j == MAXC) continue;
    if (Fd[j][u] < w) continue;
    Fv[j][u] = s; Fd[j][u] = w;

    for (auto& [v, ew] : adj[u]) {
      ll nw = w + ew, nj;
      for (nj = 0; nj < MAXC; ++nj) {
        if (Fv[nj][v] == -1 || Fv[nj][v] == s) break;
      }
      if (nj != MAXC && nw < Fd[nj][v]) {
        pq.emplace(nw, v, s);
      }
    }
  }

  ll ans = INF;
  for (int v = 0; v < N; ++v) {
    ans = min(ans, Fd[0][v] + Fd[1][v]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
