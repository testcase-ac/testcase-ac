#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
ll par[MAXN + 1], S[MAXN + 1];
vector<pair<int, ll>> U;
vector<int> adj[MAXN + 1];

void dfs1(int v) {
  S[v] = 1;
  for (int u : adj[v]) {
    dfs1(u);
    S[v] += S[u];
  }
}

void dfs2(int v) {
  ll cnt = S[v];
  for (int u : adj[v]) {
    cnt += S[u] * (S[v] - S[u]);
    dfs2(u);
  }
  U.emplace_back(v, cnt);
}

void solve() {
  int N, root; cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> par[i];
    if (par[i]) adj[par[i]].push_back(i);
    else root = i;
  }
  dfs1(root); dfs2(root);

  sort(U.begin(), U.end()); ll f = 0, O = 0, E = 0;
  for (auto& [v, cnt] : U) {
    ll lh = cnt / 2, rh = cnt - lh;
    lh *= v, rh *= v;

    if (f) E += rh, O += lh;
    else E += lh, O += rh;
    if (cnt % 2) f ^= 1;
  }
  cout << E << ' ' << O << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
