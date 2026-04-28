#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];
int cnt[2];
int cc = 0;

void dfs(int v) {
  vis[v] = true;
  cnt[cc]++;
  for (int i = 0; i < graph[v].size(); i++) {
    int u = graph[v][i];
    if (!vis[u]) {
      dfs(u);
    }
  }
}

int main() {
  fast_io();

  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    if (i == k) continue;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      dfs(i);
      cc++;
    }
  }

  cout << (ll)cnt[0] * cnt[1] << '\n';
}
