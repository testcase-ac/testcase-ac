#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
vector<int> graph[MAX];
bool vis[MAX];

void solve() {
  int N; string S;
  cin >> N >> S;
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  queue<int> q;
  q.push(0);
  vis[0] = 1;

  cout << S[0];
  while (1) {
    queue<int> nq;

    char x = 0;
    vector<int> t;
    for (int i = 0; i < q.size(); i++) {
      int v = q.front(); q.pop();

      for (int u : graph[v]) {
        if (vis[u]) continue;
        x = max(x, S[u]);
      }
      q.push(v);
    }

    while (!q.empty()) {
      int v = q.front(); q.pop();

      for (int u : graph[v]) {
        if (vis[u]) continue;
        if (S[u] == x) {
          nq.push(u);
          vis[u] = 1;
        }
      }
    }

    if (nq.empty()) break;
    cout << x;
    swap(q, nq);
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
