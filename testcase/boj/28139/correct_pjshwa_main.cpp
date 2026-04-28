#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

double edist(pii a, pii b) {
  return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

void solve() {
  int N; cin >> N;
  vector<pii> A(N);
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;
    A[i] = {x, y};
  }

  double ans = 0;
  for (auto& p1 : A) for (auto& p2 : A) {
    double d = edist(p1, p2);
    ans += d / N;
  }
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
