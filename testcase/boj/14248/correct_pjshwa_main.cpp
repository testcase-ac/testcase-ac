#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5;
bool vis[MAX];
int a[MAX], n;

void dfs(int v) {
  vis[v] = true;

  if (v - a[v] >= 0 && !vis[v - a[v]]) dfs(v - a[v]);
  if (v + a[v] < n && !vis[v + a[v]]) dfs(v + a[v]);
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  int x;
  cin >> x;
  dfs(x - 1);

  cout << accumulate(vis, vis + n, 0) << '\n';
}
