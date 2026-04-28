#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
vector<int> adj[MAXN];
int indegree[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N - 1; ++j) {
    int u = i * N + j, v = i * N + j + 1;
    string W; cin >> W;
    if (W == ">") adj[u].push_back(v), ++indegree[v];
    else adj[v].push_back(u), ++indegree[u];
  }
  for (int i = 0; i < N - 1; ++i) for (int j = 0; j < N; ++j) {
    int u = i * N + j, v = (i + 1) * N + j;
    string W; cin >> W;
    if (W == ">") adj[u].push_back(v), ++indegree[v];
    else adj[v].push_back(u), ++indegree[u];
  }

  queue<int> Q;
  for (int i = 0; i < N * N; ++i) {
    if (indegree[i] == 0) Q.push(i);
  }

  vector<vector<int>> ans(N, vector<int>(N));
  for (int l = N * N; l >= 1; --l) {
    int x = Q.front(); Q.pop();
    for (int y : adj[x]) {
      if (--indegree[y] == 0) Q.push(y);
    }
    int i = x / N, j = x % N;
    ans[i][j] = l;
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) cout << ans[i][j] << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
