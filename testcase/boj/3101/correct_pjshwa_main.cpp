#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll N;
ll p2v(int x, int y) {
  if (x + y < N) {
    ll z = x + y + 1;
    ll s = z * (z + 1) / 2;

    if (z & 1) return s - x;
    else return s - y;
  }
  else {
    ll z = 2 * N - 1 - x - y;
    ll s = z * (z + 1) / 2;

    if (z & 1) return N * N - (s - (N - 1 - x)) + 1;
    else return N * N - (s - (N - 1 - y)) + 1;
  }
}

void solve() {
  int K;
  cin >> N >> K;

  int x = 0, y = 0;
  ll ans = 1;
  string ops;
  cin >> ops;
  for (char& op : ops) {
    if (op == 'U') x--;
    if (op == 'D') x++;
    if (op == 'L') y--;
    if (op == 'R') y++;
    ans += p2v(x, y);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
