#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
string S[MAXN];
int C[26][26], indegree[26], score[26];
vector<int> adj[26];

void solve() {
  int n, k; cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    cin >> S[i];
    for (int j1 = 0; j1 < k; ++j1) for (int j2 = j1 + 1; j2 < k; ++j2) {
      int c1 = S[i][j1] - 'A', c2 = S[i][j2] - 'A';
      C[c1][c2] = 1;
    }
  }

  for (int j1 = 0; j1 < k; ++j1) for (int j2 = j1 + 1; j2 < k; ++j2) {
    int c1 = j1, c2 = j2;
    if ((C[c1][c2] ^ C[c2][c1]) == 0) continue;
    if (C[c1][c2]) {
      adj[c1].push_back(c2);
      ++indegree[c2];
    }
    else {
      adj[c2].push_back(c1);
      ++indegree[c1];
    }
  }

  queue<int> q; int ans = 1;
  for (int i = 0; i < k; ++i) {
    if (indegree[i] == 0) q.push(i), score[i] = 1;
  }

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      score[v] = max(score[v], score[u] + 1);
      ans = max(ans, score[v]);
      if (--indegree[v] == 0) q.push(v);
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
