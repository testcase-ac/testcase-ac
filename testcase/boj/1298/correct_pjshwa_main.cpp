#include <bits/stdc++.h>
using namespace std;

vector<int> graph[200];
int ma[200], mb[200];
bool vis[200];

bool dfs(int a) {
  vis[a] = true;
  for (int b : graph[a]) {
    if (mb[b] == -1 || !vis[mb[b]] && dfs(mb[b])) {
      ma[a] = b;
      mb[b] = a;
      return true;
    }
  }
  return false;
}

int main() {
  int n, m, si, ti;
  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    cin >> si >> ti;
    graph[si - 1].push_back(ti - 1);
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < n; i++) {
    if (ma[i] != -1) continue;
    memset(vis, false, sizeof vis);
    if (dfs(i)) match++;
  }

  cout << match << '\n';
}
