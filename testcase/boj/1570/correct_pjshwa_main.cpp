#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, sx, sy, mx, my; cin >> N >> sx >> sy >> mx >> my;
  if (mx < sx || my < sy) return cout << "-1\n", void();

  ll xdif = mx - sx, ydif = my - sy;
  if (xdif == 0) {
    for (int i = 0; i < min(N, ydif); ++i) cout << 'U';
    for (int i = 0; i < N - ydif; ++i) cout << 'R';
    cout << '\n';
    return;
  }
  if (ydif == 0) {
    for (int i = 0; i < N; ++i) cout << 'R';
    cout << '\n';
    return;
  }

  set<string> C;
  for (int rc = N - 1; rc >= 1; --rc) {
    int uc = N - rc;
    ll rrep = (xdif + rc - 1) / rc, urep = (ydif + uc - 1) / uc;
    ll mrep = min(rrep, urep);

    for (ll rep : {mrep - 1, mrep, mrep + 1}) {
      ll rrem = mx - (sx + rc * rep), urem = my - (sy + uc * rep);
      if (rrem < 0 || urem < 0) continue;
      if (rrem > rc || urem > uc) continue;

      string s = "";
      for (int i = 0; i < rrem; ++i) s += 'R';
      for (int i = 0; i < urem; ++i) s += 'U';
      for (int i = 0; i < rc - rrem; ++i) s += 'R';
      for (int i = 0; i < uc - urem; ++i) s += 'U';
      C.insert(s);
    }
  }

  if (C.empty()) cout << "-1\n";
  else cout << *C.begin() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
