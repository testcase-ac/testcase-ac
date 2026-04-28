#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
vector<int> adj[MAXN];
int X[MAXN], Y[MAXN], R[MAXN];
int P[MAXN], Q[MAXN], O[MAXN];
bool vis[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    adj[i].clear();
    cin >> X[i] >> Y[i] >> R[i];
  }

  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
    int rsum = R[i] + R[j], dx = X[i] - X[j], dy = Y[i] - Y[j];
    if (dx * dx + dy * dy == rsum * rsum) { 
      adj[i].push_back(j);
      adj[j].push_back(i);
    }
  }

  memset(vis, 0, sizeof(vis));
  memset(P, -1, sizeof(P));
  memset(Q, -1, sizeof(Q));

  queue<tuple<int, int, int, int>> W;
  W.emplace(0, 1, 1, 0); vis[0] = true;

  while (!W.empty()) {
    auto [v, p, q, o] = W.front(); W.pop();
    P[v] = p; Q[v] = q; O[v] = o;

    for (int u : adj[v]) {
      if (vis[u]) continue;
      vis[u] = true;

      int np = p * R[v], nq = q * R[u];
      int g = gcd(np, nq);
      W.emplace(u, np / g, nq / g, o ^ 1);
    }
  }

  for (int i = 0; i < N; ++i) {
    if (P[i] == -1) cout << "not moving\n";
    else {
      if (Q[i] == 1) cout << P[i] << " ";
      else cout << P[i] << "/" << Q[i] << " ";

      if (O[i]) cout << "counterclockwise\n";
      else cout << "clockwise\n";
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
