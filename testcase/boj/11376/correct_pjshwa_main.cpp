#include <bits/stdc++.h>
using namespace std;

vector<int> graph[2000];
int ma[2000], mb[2000];
bool vis[2000];

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
  int n, m, s, si;
  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    cin >> s;
    for (int j = 0; j < s; j++) {
      cin >> si;
      graph[i].push_back(si - 1);
      graph[i + n].push_back(si - 1);
    }
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < 2 * n; i++) {
    if (ma[i] != -1) continue;
    memset(vis, false, sizeof vis);
    if (dfs(i)) match++;
  }

  cout << match << '\n';
}
