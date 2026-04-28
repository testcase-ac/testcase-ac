#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
int a[50], vis[50];
void dfs(int n, int cc) {
  vis[n] = cc;
  if (!vis[a[n]]) dfs(a[n], cc);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  int cc = 0;
  for (int i = 0; i < n; i++) {
    if (!vis[i]) dfs(i, ++cc);
  }

  int ci, mv, mi;
  set<int> chk;
  chk.insert(1);

  mv = 1e9;
  for (int j = 0; j < n; j++) {
    if (vis[j] == 1) continue;
    mv = min(mv, a[j]);
  }

  int p = a[0], lp = 0;
  while (p != 0) {
    if (p > mv) break;
    lp = p;
    p = a[p];
  }

  ci = lp;
  while (chk.size() < cc) {
    mv = 1e9;
    for (int j = 0; j < n; j++) {
      if (chk.count(vis[j])) continue;
      if (mv > a[j]) {
        mv = a[j];
        mi = j;
      }
    }

    swap(a[ci], a[mi]);
    chk.insert(vis[mi]);
    ci = mi;
  }

  for (int i = 0; i < n; i++) cout << a[i] << ' ';
}
