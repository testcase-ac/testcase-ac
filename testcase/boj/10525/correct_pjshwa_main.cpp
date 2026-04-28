#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAX = 10000;
pii c[MAX + 1];
bool vis[MAX + 1];
vector<int> graph[MAX + 1];
int nxt = 3;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void dfs(int v, int par) {
  vis[v] = true;

  if (par == -1) c[v] = {1, 2};

  bool first = true;
  for (int d : graph[v]) {
    if (vis[d]) continue;
    if (first) {
      c[d].first = c[v].second;
      first = false;
    }
    else c[d].first = c[v].first;
    c[d].second = nxt++;
    dfs(d, v);
  }

  // me me leaf node
  if (first) c[v].second = c[v].first == c[par].first ? c[par].second : c[par].first;
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  dfs(1, -1);

  for (int i = 1; i <= n; i++) {
    cout << c[i].first << ' ' << c[i].second << '\n';
  }

}
