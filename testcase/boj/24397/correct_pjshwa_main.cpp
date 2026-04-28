#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3.3e6;
pii graph[MAX + 1];
int ssize[MAX + 1], osize[MAX + 1];

void dfs(int v) {
  auto [u1, u2] = graph[v];

  if (u1 == -1 && u2 == -1) return ssize[v] = osize[v], void();
  if (u1 != -1) dfs(u1), ssize[v] += ssize[u1];
  if (u2 != -1) dfs(u2), ssize[v] += ssize[u2];
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  for (int i = 0; i <= MAX; i++) graph[i] = {-1, -1};

  int s, x, it = 0;
  for (int i = 0; i < n; i++) {
    cin >> x;

    s = 0;
    for (int b = 30; b >= 0; b--) {
      if (x & (1 << b)) {
        if (graph[s].second == -1) graph[s].second = ++it;
        s = graph[s].second;
      }
      else {
        if (graph[s].first == -1) graph[s].first = ++it;
        s = graph[s].first;
      }
    }
    osize[s]++;
  }

  dfs(0);

  ll ans = 0;
  while (m--) {
    cin >> x;

    s = 0;
    for (int b = 30; b >= 0; b--) {
      if (s == -1) break;

      if (x & (1 << b)) {
        if (k & (1 << b)) {
          if (graph[s].second != -1) ans += ssize[graph[s].second];
          s = graph[s].first;
        }
        else s = graph[s].second;
      }
      else {
        if (k & (1 << b)) {
          if (graph[s].first != -1) ans += ssize[graph[s].first];
          s = graph[s].second;
        }
        else s = graph[s].first;
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
