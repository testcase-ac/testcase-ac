#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

map<string, bool> vis;

void solve() {
  string S = "12345678", T = "";
  for (int i = 0, x; i < 8; i++) cin >> x, T += x + '0';

  queue<pair<string, int>> q;
  q.push({S, 0});
  vis[S] = true;

  while (!q.empty()) {
    auto [v, c] = q.front();
    q.pop();

    if (v == T) {
      cout << c << '\n';
      return;
    }

    string N1 = v;
    reverse(N1.begin(), N1.end());
    string N2 = v.substr(3, 1) + v.substr(0, 3) + v.substr(5, 3) + v.substr(4, 1);
    string N3 = v.substr(0, 1) + v.substr(2, 1) + v.substr(5, 1) + v.substr(3, 2) +
                v.substr(6, 1) + v.substr(1, 1) + v.substr(7, 1);
    string N4 = v.substr(4, 1) + v.substr(1, 3) + v.substr(0, 1) + v.substr(5, 3);

    if (!vis[N1]) vis[N1] = true, q.push({N1, c + 1});
    if (!vis[N2]) vis[N2] = true, q.push({N2, c + 1});
    if (!vis[N3]) vis[N3] = true, q.push({N3, c + 1});
    if (!vis[N4]) vis[N4] = true, q.push({N4, c + 1});
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
