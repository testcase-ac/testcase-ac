#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<pii> graph[101];
int indegree[101];
int parts[101][101];
int main() {
  fast_io();

  int n, m, x, y, k;
  cin >> n >> m;

  for (int i = 1; i <= m; i++) {
    cin >> x >> y >> k;
    graph[y].push_back({x, k});
    indegree[x]++;
  }

  int g;
  for (int i = 1; i <= n; i++) {
    if (!indegree[i]) {
      parts[i][i] = 1;
      g = i;
    }
  }

  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!indegree[i]) q.push(i);
  }

  int a;
  for (int i = 1; i <= n; i++) {
    a = q.front();
    q.pop();

    for (pii p : graph[a]) {
      tie(y, k) = p;
      for (int i = 1; i <= g; i++) parts[y][i] += k * parts[a][i];
      if (!--indegree[y]) q.push(y);
    }
  }

  for (int i = 1; i <= g; i++) {
    if (parts[n][i]) cout << i << ' ' << parts[n][i] << '\n';
  }
}
