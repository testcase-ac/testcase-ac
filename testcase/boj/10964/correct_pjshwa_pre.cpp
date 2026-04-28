#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
set<int> adj[MAX];
int vis[MAX];
int n;
int mt = 1e9;

void collect() {
  set<int> var;
  for (int i = 0; i < n; i++) var.insert(vis[i]);

  if (var.size() < mt) {
    mt = var.size();
    cout << mt << '\n';
    for (int team : var) {
      for (int i = 0; i < n; i++) {
        if (vis[i] == team) cout << i + 1 << ' ';
      }
      cout << endl;
    }
  }

}

void dfs(int c) {
  for (int i = 0; i < c; i++) for (int j = i + 1; j < c; j++) {
    if (vis[i] == vis[j] && adj[i].count(j)) return;
  }

  if (c == n) {
    collect();
    return;
  }

  for (int t = 1; t <= 7; t++) {
    vis[c] = t;
    dfs(c + 1);
    vis[c] = 0;
  }
}

int main() {
  fast_io();

  int m;
  cin >> n >> m;
  while (m--) {
    int a, b;
    cin >> a >> b;
    adj[a - 1].insert(b - 1);
  }

  dfs(0);
}
