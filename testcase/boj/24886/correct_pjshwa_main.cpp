#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, p[3]; string s;
  cin >> n >> p[0] >> p[1] >> p[2] >> s;

  int p1 = -1, p2 = -1, p3 = -1, base = 0, s01 = 0, s02 = 0, s12 = 0, sc = 0, kc = 0, hc = 0;
  for (char c : s) {
    p1 = p2, p2 = p3;
    if (c == 'S') sc++, p3 = 0;
    if (c == 'K') kc++, p3 = 1;
    if (c == 'H') hc++, p3 = 2;

    if (p1 == 0 && p2 == 1 && p3 == 2) base++;
    else if (p2 == 0 && p3 == 1) s01++;
    else if (p2 == 0 && p3 == 2) s02++;
    else if (p2 == 1 && p3 == 2) s12++;
  }
  s01 -= base;
  sc -= (base + s01 + s02);
  kc -= (base + s01 + s12);
  hc -= (base + s02 + s12);

  int diff;
  diff = min(s01, p[2]), p[2] -= diff; base += diff;
  diff = min(s02, p[1]), p[1] -= diff, base += diff;
  diff = min(s12, p[0]), p[0] -= diff, base += diff;

  int ans = base;

  for (int i = 0; i <= sc; i++) {
    int rs = p[0], rk = p[1], rh = p[2];
    if (min(rk, rh) < i) break;

    int cur = i;
    rk -= i, rh -= i;

    int add1 = min({kc, rs, rh});
    cur += add1, rs -= add1, rh -= add1;

    int add2 = min({hc, rs, rk});
    cur += add2, rs -= add2, rk -= add2;

    ans = max(ans, base + cur + min({rs, rk, rh}));
  }

  for (int i = 0; i <= kc; i++) {
    int rs = p[0], rk = p[1], rh = p[2];
    if (min(rs, rh) < i) break;

    int cur = i;
    rs -= i, rh -= i;

    int add1 = min({sc, rk, rh});
    cur += add1, rk -= add1, rh -= add1;

    int add2 = min({hc, rs, rk});
    cur += add2, rs -= add2, rk -= add2;

    ans = max(ans, base + cur + min({rs, rk, rh}));
  }

  for (int i = 0; i <= hc; i++) {
    int rs = p[0], rk = p[1], rh = p[2];
    if (min(rs, rk) < i) break;

    int cur = i;
    rs -= i, rk -= i;

    int add1 = min({sc, rk, rh});
    cur += add1, rk -= add1, rh -= add1;

    int add2 = min({kc, rs, rh});
    cur += add2, rs -= add2, rh -= add2;

    ans = max(ans, base + cur + min({rs, rk, rh}));
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
