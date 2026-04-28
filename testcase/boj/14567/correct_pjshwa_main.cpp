#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int indegree[1001], ord[1001];
bool adj[1001][1001];
int main() {
  fast_io();

  int n, m, a, b;
  cin >> n >> m;

  while (m--) {
    cin >> a >> b;
    adj[a][b] = true;
    indegree[b]++;
  }

  queue<pair<int, int>> q;
  for (int i = 1; i <= n; i++) {
    if (!indegree[i]) q.push({i, 1});
  }

  for (int i = 1; i <= n; i++) {
    auto [nd, od] = q.front();
    ord[nd] = od;
    q.pop();

    for (int j = 1; j <= n; j++) {
      if (adj[nd][j] && !--indegree[j]) q.push({j, od + 1});
    }
  }

  for (int i = 1; i <= n; i++) cout << ord[i] << ' ';
  cout << '\n';
}
