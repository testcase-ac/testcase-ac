#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int sd[MAX + 1], td[MAX + 1];
vector<int> graph[MAX + 1];

void bfs(int s, int* dist) {
  memset(dist, -1, sizeof(int) * (MAX + 1));

  queue<int> q;
  q.push(s);
  dist[s] = 0;

  while (!q.empty()) {
    int u = q.front(); q.pop();

    for (int v : graph[u]) {
      if (dist[v] != -1) continue;
      dist[v] = dist[u] + 1;
      q.push(v);
    }
  }
}

void solve() {
  int N, M, s, t;
  cin >> N >> M >> s >> t;
  while (M--) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  map<int, int> sc, tc;

  bfs(s, sd);
  for (int i = 1; i <= N; i++) sc[sd[i]]++;

  bfs(t, td);
  for (int i = 1; i <= N; i++) tc[td[i]]++;

  ll r = td[s], ans = 0;
  for (int i = 0; i <= r - 2; i++) {
    ans += (ll)sc[i] * tc[r - 2 - i];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
