#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];
int cnt;

void dfs(int v) {
  vis[v] = 1;
  cnt++;
  for (int d : graph[v]) if (!vis[d]) dfs(d);
}

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int a, b;
    cin >> a >> b;
    graph[b].push_back(a);
  }
  int k;
  cin >> k;
  dfs(k);
  cout << cnt - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
