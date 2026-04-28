#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int cost(int px, int py, int cx, int cy) {
  int dx = cx - px, dy = cy - py;
  if (dx * dy > 0) return max(abs(dx), abs(dy));
  else return abs(dx) + abs(dy);
}

void solve() {
  int w, h, n;
  cin >> w >> h >> n;

  int px, py;
  cin >> px >> py;

  int ans = 0;
  while (--n) {
    int cx, cy;
    cin >> cx >> cy;
    ans += cost(px, py, cx, cy);
    px = cx, py = cy;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
