#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
bool vis[MAX];

void solve() {
  int N, T, G;
  cin >> N >> T >> G;

  queue<pii> q;
  q.push({N, 0});
  vis[N] = true;

  while (!q.empty()) {
    auto [v, c] = q.front();
    q.pop();

    if (v == G) {
      if (c <= T) cout << c << '\n';
      else cout << "ANG\n";
      return;
    }

    if (v + 1 < MAX && !vis[v + 1]) {
      q.push({v + 1, c + 1});
      vis[v + 1] = true;
    }

    int nxt = 2 * v;
    if (nxt >= MAX) continue;
    else if (nxt >= 10'000) nxt -= 10'000;
    else if (nxt >= 1'000) nxt -= 1'000;
    else if (nxt >= 100) nxt -= 100;
    else if (nxt >= 10) nxt -= 10;
    else if (nxt >= 1) nxt -= 1;

    if (!vis[nxt]) {
      q.push({nxt, c + 1});
      vis[nxt] = true;
    }
  }

  cout << "ANG\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
