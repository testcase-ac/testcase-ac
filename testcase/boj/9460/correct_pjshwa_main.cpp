#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 2e9;

void solve() {
  int N, K; cin >> N >> K;

  vector<pii> A;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    A.emplace_back(x, y);
  }
  sort(A.begin(), A.end());

  double l = 0, r = MAXV;
  for (int it = 0; it < 100; ++it) {
    double m = (l + r) / 2;

    int cnt = 1, cmin = MAXV, cmax = -MAXV;
    for (int i = 0; i < N; ++i) {
      int y = A[i].second;
      int nmin = min(cmin, y), nmax = max(cmax, y);
      if (nmax - nmin > 2 * m) {
        ++cnt;
        cmin = y, cmax = y;
      }
      else {
        cmin = nmin, cmax = nmax;
      }
    }

    if (cnt <= K) r = m;
    else l = m;
  }

  cout << fixed << setprecision(1) << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
