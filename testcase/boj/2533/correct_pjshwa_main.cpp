#include <bits/stdc++.h>
using namespace std;

vector<int> graph[(int)1e6 + 1];
vector<int> tree[(int)1e6 + 1];

void construct_tree(int node, int parent) {
  tree[parent].push_back(node);
  for (int& dst : graph[node]) {
    if (dst != parent) construct_tree(dst, node);
  }
}

int dp[(int)1e6 + 1][2];
int min_adapters(int node, int select) {
  if (dp[node][select] == -1) {
    int ans;
    if (tree[node].empty()) ans = select;
    else {
      ans = 0;
      if (select) {
        ans++;
        for (int& dst : tree[node]) ans += min(min_adapters(dst, 1), min_adapters(dst, 0));
      }
      else {
        for (int& dst : tree[node]) ans += min_adapters(dst, 1);
      }
    }

    dp[node][select] = ans;
  }
  return dp[node][select];
}

int main() {
  int n, u, v;
  cin >> n;

  for (int i = 0; i < n - 1; i++) {
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  construct_tree(1, 0);
  memset(dp, -1, sizeof(dp));
  cout << min(min_adapters(1, 1), min_adapters(1, 0)) << '\n';
}
