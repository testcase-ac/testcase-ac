#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool vis[20000];
void bfs(int n) {
  queue<pair<int, string>> q;
  q.push({1 % n, "1"});
  vis[1 % n] = true;

  while (1) {
    auto [r, s] = q.front();
    q.pop();

    if (r == 0) {
      cout << s << '\n';
      return;
    }

    int az = (r * 10 + 0) % n, ao = (r * 10 + 1) % n;
    if (!vis[az]) vis[az] = true, q.push({az, s + '0'});
    if (!vis[ao]) vis[ao] = true, q.push({ao, s + '1'});
  }
}

void solve() {
  int n;
  cin >> n;
  memset(vis, 0, sizeof(vis));
  bfs(n);
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
