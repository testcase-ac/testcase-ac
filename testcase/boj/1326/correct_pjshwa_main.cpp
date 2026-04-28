#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int a[MAX + 1];
bool vis[MAX + 1];

void solve() {
  int N, S, E;
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> a[i];
  cin >> S >> E;

  queue<pii> q;
  q.push({S, 0});
  vis[S] = 1;

  while (!q.empty()) {
    auto [v, c] = q.front();
    q.pop();

    if (v == E) {
      cout << c << '\n';
      return;
    }

    for (int m = 1;; m++) {
      int t = v + m * a[v];
      if (t > N) break;
      if (vis[t]) continue;

      vis[t] = true;
      q.push({t, c + 1});
    }
    for (int m = 1;; m++) {
      int t = v - m * a[v];
      if (t < 1) break;
      if (vis[t]) continue;

      vis[t] = true;
      q.push({t, c + 1});
    }
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
