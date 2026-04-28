#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> graph[50001];
int parent[50001];
int level[50001];
bool vis[50001];

void dfs(int node, int lv) {
  vis[node] = true;
  level[node] = lv;

  for (int el : graph[node]) {
    if (!vis[el]) {
      parent[el] = node;
      dfs(el, lv + 1);
    }
  }
}

int main() {
  fast_io();

  int m, x, y;

  for (int i = 2; i < 1024; i++) {
    graph[i / 2].push_back(i);
    graph[i].push_back(i / 2);
  }

  dfs(1, 0);

  cin >> m;
  while (m--) {
    cin >> x >> y;
    while (x != y) {
      if (level[x] < level[y]) y = parent[y];
      else x = parent[x];
    }
    cout << x * 10 << '\n';
  }
}
