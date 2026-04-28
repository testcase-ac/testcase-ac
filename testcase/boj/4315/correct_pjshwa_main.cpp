#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e4;
vector<int> graph[MAX + 1];
int indegree[MAX + 1], b[MAX + 1], need[MAX + 1];
bool vis[MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int dfs(int v) {
  vis[v] = true;
  int ans = b[v] - 1;
  for (int d : graph[v]) {
    if (!vis[d]) ans += dfs(d);
  }
  need[v] = abs(ans);
  return ans;
}

int main() {
  fast_io();

  while (1) {
    int n;
    cin >> n;
    if (n == 0) break;

    for (int i = 1; i <= n; i++) graph[i].clear(), indegree[i] = 0, vis[i] = false;

    for (int i = 0; i < n; i++) {
      int v, s, d, di;
      cin >> v >> s >> d;
      b[v] = s;

      for (int j = 0; j < d; j++) {
        cin >> di;
        graph[v].push_back(di);
        indegree[di]++;
      }
    }

    for (int i = 1; i <= n; i++) if (indegree[i] == 0) dfs(i);
    cout << accumulate(need + 1, need + n + 1, 0LL) << '\n';
  }

}
