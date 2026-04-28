#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

bool visited[(size_t)5e6 + 1];
vector<int> graph[(size_t)5e6 + 1];

int dfs(int node, int depth){
  visited[node] = true;
  int val = 0;
  int cnt = 0;
  for (int dst : graph[node]) {
    if (visited[dst]) continue;

    cnt++;
    val += dfs(dst, depth + 1);
  }

  if (!cnt) return depth;
  else return val;
}

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  FastIO();

  int n, a, b;
  cin >> n;
  memset(visited, false, sizeof(bool) * (n + 1));

  for (int i = 0; i < n - 1; i++) {
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  cout << (dfs(1, 0) % 2 ? "Yes\n" : "No\n");
}
