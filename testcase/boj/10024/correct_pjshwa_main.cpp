#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
pii a[MAX + 1];
int x[MAX + 1];
bool vis[MAX + 1];

int dfs(int v) {
  vis[v] = true;
  if (vis[x[v]]) return 1;
  else return 1 + dfs(x[v]);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i].second;
  for (int i = 1; i <= n; i++) cin >> a[i].first;
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) x[i] = a[i].second;

  int cc = 0, lc = -1;
  for (int i = 1; i <= n; i++) {
    if (!vis[i] && i != x[i]) cc++, lc = max(lc, dfs(i));
  }
  cout << cc << ' ' << lc << '\n';
}
