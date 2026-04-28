#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S, T; cin >> S >> T;

  int R = 0, G = 0, B = 0, Y = 0;
  for (char c : S) {
    if (c == 'R') R++;
    if (c == 'G') G++;
    if (c == 'B') B++;
    if (c == 'Y') Y++;
  }
  for (char c : T) {
    if (c == 'R') R--;
    if (c == 'G') G--;
    if (c == 'B') B--;
    if (c == 'Y') Y--;
  }

  int ans = abs(R) + abs(G) + abs(B) + abs(Y);
  cout << ans / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
