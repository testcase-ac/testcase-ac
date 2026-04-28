#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 1e9 + 7;
int A[MAX][MAX];
vector<int> graph[MAX];
int cdist[MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    cin >> A[i][j];
    if (A[i][j]) graph[i].push_back(j);
  }

  int ans = 0;
  for (int i = 0; i < N; i++) {
    fill(cdist, cdist + N, INF);
    queue<pii> q;
    for (int v : graph[i]) {
      if (v == i) {
        q.push({v, 0});
        cdist[v] = 0;
      }
      else {
        q.push({v, 1});
        cdist[v] = 1;
      }
    }

    while (!q.empty()) {
      auto [v, c] = q.front(); q.pop();
      for (int u : graph[v]) {
        if (cdist[u] > c + 1) {
          q.push({u, c + 1});
          cdist[u] = c + 1;
        }
      }
    }

    ans = max(ans, *max_element(cdist, cdist + N));
  }

  if (ans == INF) cout << "0\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
