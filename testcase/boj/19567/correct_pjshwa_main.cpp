#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
int X[MAXN][MAXN];

void solve() {
  int N; cin >> N;

  ll o = -1, minx, maxx, miny, maxy;
  vector<tuple<int, int, int>> A;
  for (int i = 0; i < N; ++i) {
    ll a, b, c; cin >> a >> b >> c;
    A.emplace_back(a, b, c);

    // rotate the coordinate 315 degrees
    b -= c;
    ll na = a + b;
    ll nb = b - a;

    // x range: [na, na + c]
    // y range: [nb, nb + c]

    if (o == -1) {
      o = 1;
      minx = na, maxx = na + 2 * c;
      miny = nb, maxy = nb + 2 * c;
    }
    else {
      minx = max(minx, na);
      maxx = min(maxx, na + 2 * c);
      miny = max(miny, nb);
      maxy = min(maxy, nb + 2 * c);
    }
  }

  if (minx > maxx || miny > maxy) cout << "NO\n";
  else {
    ll x = (minx - maxy) / 2, y = (minx + maxy) / 2;
    for (auto& [a, b, c] : A) {
      ll d = abs(a - x) + abs(b - y);
      if (d > c || (c - d) % 2) {
        cout << "NO\n";
        return;
      }
    }
    cout << x << " " << y << "\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
