#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, B, C, D, E; cin >> A >> B >> C >> D >> E;

  int ans = E, v;
  v = min(A, D); ans += v; A -= v; D -= v; ans += D;
  v = min(B, C); ans += v; B -= v; C -= v;

  while (C) {
    C--;
    A -= min(A, 2);
    ans++;
  }
  while (B >= 2) {
    B -= 2;
    if (A) A--;
    ans++;
  }
  if (B) {
    A -= min(A, 3);
    ans++;
  }
  ans += (A + 4) / 5;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
