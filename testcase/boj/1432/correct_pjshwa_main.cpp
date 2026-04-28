#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
char board[MAX + 1][MAX + 1];
vector<int> graph[MAX + 1];
int indegree[MAX + 1];
int res[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> board[i];
    for (int j = 0; j < n; j++) {
      if (board[i][j] == '1') {
        graph[j + 1].push_back(i + 1);
        indegree[i + 1]++;
      }
    }
  }

  set<int> q;
  for (int i = 1; i <= n; i++) {
    if (indegree[i] == 0) q.insert(i);
  }

  int t = n;
  while (!q.empty()) {
    auto it = q.end();
    it--;
    int u = *it;
    q.erase(it);
    res[u] = t--;
    for (int v : graph[u]) {
      indegree[v]--;
      if (indegree[v] == 0) q.insert(v);
    }
  }

  if (t == 0) for (int i = 1; i <= n; i++) cout << res[i] << ' ';
  else cout << -1;
  cout << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
