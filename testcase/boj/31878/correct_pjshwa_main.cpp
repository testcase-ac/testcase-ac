#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 111'222;
vector<int> adj[MAXN + 1];
int S[MAXN + 1], vis[MAXN + 1];

void solve() {
  int N; cin >> N;
  vector<pii> A;
  for (int i = 1; i <= N; ++i) {
    int x; cin >> x;
    A.emplace_back(x, i);
  }
  sort(A.begin(), A.end());

  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); adj[v].push_back(u);
  }

  queue<int> Q;
  Q.push(1); vis[1] = 1;

  int i = 0;
  while (!Q.empty()) {
    int v = Q.front(); Q.pop();
    S[v] = A[i++].second;

    for (int u : adj[v]) {
      if (vis[u]) continue;
      Q.push(u); vis[u] = 1;
    }
  }

  cout << "YES\n";
  for (int i = 1; i <= N; ++i) cout << S[i] << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
