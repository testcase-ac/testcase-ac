#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
vector<pii> adj[MAXN + 1];
ll A[MAXN + 1], S[MAXN + 1], V[MAXN + 1], R[MAXN + 1];
ll f, o, val;
vector<tuple<ll, ll, ll>> C;

void dfs(int v, ll a, ll s) {
  V[v] = 1; A[v] = a; S[v] = s;
  C.emplace_back(s, a, v);

  for (auto& [u, w] : adj[v]) {
    if (V[u]) {
      if (S[u] == S[v]) {
        ll t = w - A[u] - A[v];
        if (t % 2) f = 0;
        else if (o && t / (S[u] + S[v]) != val) f = 0;

        if (f == 0) return;
        o = 1; val = t / (S[u] + S[v]);
      }
      else if (A[u] + A[v] != w) {
        f = 0;
        return;
      }
    }
    else dfs(u, w - a, -s);
  }
}

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  for (int i = 1; i <= N; ++i) {
    if (V[i]) continue;

    f = 1; o = 0; C.clear();
    dfs(i, 0, 1);
    if (f == 0) return cout << "No\n", void();

    if (o) {
      for (auto& [s, a, v] : C) R[v] = s * val + a;
    }
    else {
      vector<ll> candidates;
      for (auto& [s, a, v] : C) candidates.emplace_back(-s * a);
      sort(candidates.begin(), candidates.end());

      ll Z = candidates.size(), c = candidates[0]; ll best = 0;
      for (auto& [s, a, v] : C) best += abs(1LL * s * c + a);

      ll cur = best, val = c, dt = 2 - Z;
      for (int i = 1; i < Z; ++i) {
        ll nc = candidates[i];

        cur += dt * (nc - c);
        if (cur < best) {
          best = cur;
          val = nc;
        }
        dt += 2;
        c = nc;
      }

      for (auto& [s, a, v] : C) R[v] = s * val + a;
    }
  }

  cout << "Yes\n";
  for (int i = 1; i <= N; ++i) cout << R[i] << " ";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
