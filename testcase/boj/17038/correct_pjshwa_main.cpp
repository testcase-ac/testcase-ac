#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> sg[MAX + 1], dg[MAX + 1];
int vis[MAX + 1];
bool unable = false;

// Check bipartite-ness
void dfs(int v, int c) {
  vis[v] = c;
  for (int d : sg[v]) {
    if (vis[d] && vis[d] != c) {
      unable = true;
      return;
    }
    else if (!vis[d]) dfs(d, c);
  }
  for (int d : dg[v]) {
    if (vis[d] && vis[d] == c) {
      unable = true;
      return;
    }
    else if (!vis[d]) dfs(d, 3 - c);
  }
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  while (m--) {
    string op;
    int a, b;
    cin >> op >> a >> b;
    if (op == "S") {
      sg[a].push_back(b);
      sg[b].push_back(a);
    }
    else {
      dg[a].push_back(b);
      dg[b].push_back(a);
    }
  }

  int cc = 0;
  for (int i = 1; i <= n; i++) if (!vis[i]) {
    cc++;
    dfs(i, 1);
    if (unable) return cout << "0\n", 0;
  }

  cout << 1;
  for (int i = 0; i < cc; i++) cout << 0;
  cout << '\n';
}
