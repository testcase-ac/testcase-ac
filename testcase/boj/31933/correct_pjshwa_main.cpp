#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000;
vector<tuple<int, int, int>> adj[MAXN];
int vis[MAXN], N;
queue<int> Q;

bool is_possible(int w) {
  fill(vis, vis + N, 0);
  Q.push(0); vis[0] = 1;
  while (!Q.empty()) {
    int v = Q.front(); Q.pop();
    for (auto [u, l, r] : adj[v]) {
      if (vis[u] || l > w || w > r) continue;
      Q.push(u); vis[u] = 1;
    }
  }
  return vis[N - 1];
}

void solve() {
  int M; cin >> N >> M;

  vector<int> S;
  while (M--) {
    int u, v, l, r; cin >> u >> v >> l >> r; --u; --v;
    adj[u].emplace_back(v, l, r);
    adj[v].emplace_back(u, l, r);
    S.push_back(l); S.push_back(r + 1);
  }
  sort(S.begin(), S.end());
  S.erase(unique(S.begin(), S.end()), S.end());
  
  vector<pii> segments; int f = -1;
  for (int e : S) {
    if (f == -1) {
      if (!is_possible(e)) continue;
      f = e;
    } else {
      if (is_possible(e)) continue;
      segments.emplace_back(f, e);
      f = -1;
    }
  }

  vector<int> O;
  int K, x; cin >> K;
  while (K--) cin >> x, O.push_back(x);
  sort(O.begin(), O.end());

  int ans = 0;
  for (auto& [s, e] : segments) {
    ans += lower_bound(O.begin(), O.end(), e) - lower_bound(O.begin(), O.end(), s);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
