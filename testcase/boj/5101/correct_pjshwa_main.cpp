#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int p[3];

void solve() {
  p[2] -= p[0];
  if (p[2] % p[1]) cout << "X\n";
  else {
    int ans = 1 + p[2] / p[1];
    if (ans <= 0) cout << "X\n";
    else cout << ans << '\n';
  }
}

int main() {
  fast_io();

  while (1) {
    cin >> p[0] >> p[1] >> p[2];
    if (p[0] == 0 && p[1] == 0 && p[2] == 0) break;
    solve();
  }
}
