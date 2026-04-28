#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<tii> dat[MAX + 1];
bool vis[MAX + 1];
pii res[MAX + 1];

void dfs(int v) {
  vis[v] = true;

  for (auto [dst, dx, dy] : dat[v]) {
    if (!vis[dst]) {
      res[dst] = {res[v].first + dx, res[v].second + dy};
      dfs(dst);
    }
  }
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  while (m--) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    dat[a].emplace_back(b, c, d);
    dat[b].emplace_back(a, -c, -d);
  }

  res[1] = {0, 0};
  dfs(1);

  int gap;

  gap = 0;
  for (int i = 1; i <= n; i++) gap = max(gap, res[i].first - (int)1e9);
  for (int i = 1; i <= n; i++) res[i].first -= gap;

  gap = 0;
  for (int i = 1; i <= n; i++) gap = min(gap, res[i].first + (int)1e9);
  for (int i = 1; i <= n; i++) res[i].first -= gap;

  gap = 0;
  for (int i = 1; i <= n; i++) gap = max(gap, res[i].second - (int)1e9);
  for (int i = 1; i <= n; i++) res[i].second -= gap;

  gap = 0;
  for (int i = 1; i <= n; i++) gap = min(gap, res[i].second + (int)1e9);
  for (int i = 1; i <= n; i++) res[i].second -= gap;

  for (int i = 1; i <= n; i++) cout << res[i].first << " " << res[i].second << "\n";
}
