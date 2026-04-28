#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> graph[50];
bool vis[50];
int leaves = 0;
int erased;

void dfs(int node) {
  vis[node] = true;

  if (graph[node].empty() || (graph[node].size() == 1 && graph[node][0] == erased)) {
    leaves++;
    return;
  }

  for (auto dst : graph[node]) {
    if (!vis[dst] && dst != erased) dfs(dst);
  }
}

int main() {
  fast_io();

  int n, k;
  cin >> n;

  int root;
  for (int i = 0; i < n; i++) {
    cin >> k;
    if (k == -1) root = i;
    else graph[k].push_back(i);
  }

  cin >> erased;

  if (root != erased) dfs(root);
  cout << leaves << '\n';
}
