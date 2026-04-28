#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, MOD = 1e9 + 7;
bool vis[MAX];
vector<int> graph[MAX];
int a[MAX], d[MAX][10];

void dfs(int v) {
  vis[v] = true;

  d[v][a[v]] = 1;
  for (int o : graph[v]) if (!vis[o]) {
    dfs(o);
    for (int i = 0; i < 10; i++) d[v][i] = (d[v][i] + d[o][i]) % MOD;
    for (int i = a[v]; i < 10; i++) d[v][a[v]] = (d[v][a[v]] + d[o][i]) % MOD;
  }
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    graph[a - 1].push_back(b - 1);
    graph[b - 1].push_back(a - 1);
  }
  dfs(0);

  int ans = 0;
  for (int i = 0; i < 10; i++) ans = (ans + d[0][i]) % MOD;
  cout << ans;
}
