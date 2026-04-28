#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll x, y, K, N;
bool f;
set<tuple<int, int, int, int>> vis;

void dfs(int a1, int a2, int b1, int b2) {
  if (vis.count({a1, a2, b1, b2})) return;
  vis.insert({a1, a2, b1, b2});

  ll xdiff = abs(x - K * a1 + N * a2), ydiff = abs(y - K * b1 + N * b2);
  ll g = __gcd(2 * K, 2 * N);

  if (xdiff % g == 0 && ydiff % g == 0) {
    f = true;
    return;
  }
  if (abs(a1) == 2 || abs(a2) == 2 || abs(b1) == 2 || abs(b2) == 2) return;

  dfs(a1 + 1, a2, b1, b2 + 1);
  dfs(a1 + 1, a2, b1, b2 - 1);
  dfs(a1 - 1, a2, b1, b2 + 1);
  dfs(a1 - 1, a2, b1, b2 - 1);
  dfs(a1, a2 + 1, b1 + 1, b2);
  dfs(a1, a2 + 1, b1 - 1, b2);
  dfs(a1, a2 - 1, b1 + 1, b2);
  dfs(a1, a2 - 1, b1 - 1, b2);
}

void solve() {
  ll x1, y1, x2, y2;
  cin >> K >> N >> x1 >> y1 >> x2 >> y2;

  x = abs(x1 - x2), y = abs(y1 - y2);
  if (K == 0 && N == 0) {
    if (x == 0 && y == 0) cout << "TAK\n";
    else cout << "NIE\n";
    return;
  }
  if (K == 0) {
    if (x % N == 0 && y % N == 0) cout << "TAK\n";
    else cout << "NIE\n";
    return;
  }
  if (N == 0) {
    if (x % K == 0 && y % K == 0) cout << "TAK\n";
    else cout << "NIE\n";
    return;
  }

  f = false; vis.clear();
  dfs(0, 0, 0, 0);

  if (f) cout << "TAK\n";
  else cout << "NIE\n";
}
 
int main() {
  fast_io();
 
  int t = 1;
  cin >> t;
  while (t--) solve();
}