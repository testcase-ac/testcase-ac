#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> graph[100001];
int parent[100001];

void dfs(int node, int p) {
  parent[node] = p;

  for (auto &dst : graph[node]) {
    if (parent[dst] == -1) dfs(dst, node);
  }
}

int main() {
  fast_io();

  int n, a, b;
  cin >> n;

  memset(parent, -1, sizeof(parent));

  for (int i = 0; i < n - 1; i++) {
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  dfs(1, 0);

  for (int i = 2; i <= n; i++) cout << parent[i] << '\n';
}
