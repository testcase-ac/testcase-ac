#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1e6, BIAS = 5e5;
int Hdt[MAXV + 1], Vdt[MAXV + 1];

void solve() {
  int n; cin >> n;

  vector<pii> A(n);
  for (auto& [x, y] : A) cin >> x >> y;

  for (int i = 1; i <= n; ++i) {
    auto [x1, y1] = A[i % n];
    auto [x2, y2] = A[i - 1];
    if (x1 == x2) {
      int miny = min(y1, y2), maxy = max(y1, y2);
      Vdt[miny + BIAS] += 1;
      Vdt[maxy + BIAS] -= 1;
    }
    else {
      int minx = min(x1, x2), maxx = max(x1, x2);
      Hdt[minx + BIAS] += 1;
      Hdt[maxx + BIAS] -= 1;
    }
  }

  int ans = 0;
  for (int i = 0; i <= MAXV; ++i) {
    if (i) {
      Hdt[i] += Hdt[i - 1];
      Vdt[i] += Vdt[i - 1];
    }
    ans = max(ans, Hdt[i]);
    ans = max(ans, Vdt[i]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
