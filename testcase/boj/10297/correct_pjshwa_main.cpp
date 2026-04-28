#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1e5, INF = 1e18;
ll X[MAXN + 1], S[MAXN + 1], L[MAXN + 1], ans;
vector<int> adj[MAXN + 1];

ll rec1(int u, int p) {
  if (L[u] != -1) return L[u];

  ll res = S[u] ? X[u] : -INF;
  for (int v : adj[u]) {
    if (v == p) continue;
    ll val = rec1(v, u);
    if (val != -INF) res = max(res, val + X[u]);
  }
  return L[u] = res;
}

void rec2(int u, int p) {

  vector<ll> child_vals;
  for (int v : adj[u]) {
    if (v == p) continue;
    if (L[v] != -INF) child_vals.push_back(L[v]);
  }
  sort(child_vals.rbegin(), child_vals.rend());

  if (child_vals.size() >= 2) {
    ans = max(ans, child_vals[0] + child_vals[1] + X[u]);
  }
  if (child_vals.size() >= 1 && S[u]) {
    ans = max(ans, child_vals[0] + X[u]);
  }
  child_vals.clear();

  for (int v : adj[u]) {
    if (v == p) continue;
    rec2(v, u);
  }
}

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) adj[i].clear();
  ans = -INF;

  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); adj[v].push_back(u);
  }
  for (int i = 1; i <= N; ++i) cin >> X[i];
  for (int i = 1; i <= N; ++i) cin >> S[i];

  memset(L, -1, sizeof L);
  rec1(1, -1);
  rec2(1, -1);

  if (ans > 0) cout << ans << '\n';
  else cout << "Stay Home\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
