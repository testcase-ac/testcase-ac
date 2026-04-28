#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

double area(int p0x, int p0y, int p1x, int p1y, int p2x, int p2y) {
  return abs((p1x - p0x) * (p2y - p0y) - (p2x - p0x) * (p1y - p0y)) / 2.0;
}

void solve() {
  int p0x, p0y, p1x, p1y, p2x, p2y, M;
  cin >> p0x >> p0y >> p1x >> p1y >> p2x >> p2y >> M;

  double ta = area(p0x, p0y, p1x, p1y, p2x, p2y);

  int ans = 0;
  while (M--) {
    int px, py;
    cin >> px >> py;

    double a1 = area(p0x, p0y, p1x, p1y, px, py);
    double a2 = area(p1x, p1y, p2x, p2y, px, py);
    double a3 = area(p2x, p2y, p0x, p0y, px, py);

    if (a1 + a2 + a3 == ta) ans++;
  }

  cout << fixed << setprecision(1) << ta << '\n';
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
