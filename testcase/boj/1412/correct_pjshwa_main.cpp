#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50;
char adj_c[MAXN + 1][MAXN + 1];
vector<int> adj_p[MAXN];
int indegree[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> adj_c[i];
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    if (adj_c[i][j] == 'Y' && adj_c[j][i] == 'N') {
      adj_p[i].push_back(j);
      ++indegree[j];
    }
  }

  queue<int> Q;
  for (int i = 0; i < N; ++i) if (indegree[i] == 0) Q.push(i);
  for (int t = 0; t < N; ++t) {
    if (Q.empty()) return cout << "NO\n", void();
    int u = Q.front(); Q.pop();
    for (int v : adj_p[u]) {
      if (--indegree[v] == 0) Q.push(v);
    }
  }
  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
