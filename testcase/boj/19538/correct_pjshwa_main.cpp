#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
vector<int> graph[MAX + 1];
int threshold[MAX + 1], ans[MAX + 1];
bool vis[MAX + 1];

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    int x;
    while (cin >> x) {
      if (x == 0) break;
      graph[i].push_back(x);
    }
    threshold[i] = (graph[i].size() + 1) / 2;
  }

  memset(ans, -1, sizeof(ans));

  queue<int> q;
  int M;
  cin >> M;
  while (M--) {
    int x;
    cin >> x;
    q.push(x);
    vis[x] = 1;
  }

  for (int t = 0;; t++) {
    queue<int> nq;

    while (!q.empty()) {
      int v = q.front(); q.pop();
      ans[v] = t;

      for (int u : graph[v]) {
        if (vis[u]) continue;

        threshold[u]--;
        if (threshold[u] == 0) {
          nq.push(u);
          vis[u] = 1;
        }
      }
    }

    if (nq.empty()) break;
    swap(q, nq);
  }

  for (int i = 1; i <= N; i++) cout << ans[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
