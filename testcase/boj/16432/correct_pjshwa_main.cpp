#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10000;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];
int a[10][MAX], v[MAX];
vector<int> current;
int n;

void dfs(int v) {
  vis[v] = true;
  int i = v / 10, j = v % 10;
  current.push_back(a[j][i]);

  if (current.size() == n) {
    for (int e : current) cout << e << '\n';
    exit(0);
  }

  for (int e : graph[v]) {
    if (!vis[e]) dfs(e);
  }

  current.pop_back();
}

void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    for (int j = 0; j < v[i]; j++) cin >> a[j][i];
  }
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < v[i]; j++) for (int k = 0; k < v[i + 1]; k++) {
      if (a[j][i] == a[k][i + 1]) continue;
      int u = i * 10 + j, v = (i + 1) * 10 + k;
      graph[u].push_back(v);
    }
  }

  for (int j = 0; j < v[0]; j++) dfs(j);

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
