#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 52, INF = 1e9 + 7;
int c[MAX][MAX], f[MAX][MAX];
int from[MAX];
vector<int> graph[MAX];

void solve() {
  int m;
  cin >> m;
  while (m--) {
    string us, vs; int u, v, w;
    cin >> us >> vs >> w;

    if (us[0] >= 'a') u = us[0] - 'a' + 26;
    else u = us[0] - 'A';
    if (vs[0] >= 'a') v = vs[0] - 'a' + 26;
    else v = vs[0] - 'A';

    c[u][v] = c[v][u] += w;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  int ans = 0, S = 0, T = 25;
  while (1) {
    memset(from, -1, sizeof(from));
    queue<int> q;
    q.push(S);

    // Find augmenting path
    while (!q.empty() && from[T] == -1) {
      int u = q.front(); q.pop();

      for (int v : graph[u]) {
        if (c[u][v] - f[u][v] > 0 && from[v] == -1) {
          from[v] = u;
          q.push(v);
        }
      }
    }

    if (from[T] == -1) break;

    int mflo = INF;
    for (int u = T; u != S; u = from[u]) mflo = min(mflo, c[from[u]][u] - f[from[u]][u]);
    for (int u = T; u != S; u = from[u]) {
      f[from[u]][u] += mflo;
      f[u][from[u]] -= mflo;
    }

    ans += mflo;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
