#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 1e5;
int graph[MAX + 1];
int indegree[MAX + 1];
bool vis[MAX + 1];
vector<int> ans;

int lstart;

void dfs(int v) {
  vis[v] = true;
  ans.push_back(v);
  lstart = v;

  int d = graph[v];
  if (vis[d]) return;

  indegree[d]--;
  dfs(d);
}

int main() {
  fast_io();

  int n;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
    graph[i] = a;
    indegree[a]++;
  }

  dfs(1);
  ans.push_back(graph[lstart]);

  for (int i = 2; i <= n; i++) {
    if (!indegree[i] && !vis[i]) {
      dfs(i);
      ans.push_back(graph[lstart]);
    }
  }

  // Get rid of cycles
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) {
      dfs(i);
      ans.push_back(graph[lstart]);
    }
  }

  cout << ans.size() - 1 << '\n';
  for (int i = 1; i < ans.size(); i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}
