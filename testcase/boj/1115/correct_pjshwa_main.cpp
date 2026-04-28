#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
int a[50];
bool vis[50];

void dfs(int n) {
  vis[n] = true;
  if (!vis[a[n]]) dfs(a[n]);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  int cc = 0;
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      cc++;
      dfs(i);
    }
  }

  cout << (cc >= 2 ? cc : 0);
}
