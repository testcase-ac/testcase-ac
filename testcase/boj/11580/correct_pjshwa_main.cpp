#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int L; string S;
  cin >> L >> S;

  set<pii> u;
  u.insert({0, 0});
  int x = 0, y = 0;

  for (char c : S) {
    if (c == 'N') x--;
    if (c == 'S') x++;
    if (c == 'E') y++;
    if (c == 'W') y--;
    u.insert({x, y});
  }

  cout << u.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
