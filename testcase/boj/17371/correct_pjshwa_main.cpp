#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

double dist(pii& a, pii& b) {
  return sqrt((a.first - b.first) * (a.first - b.first) +
              (a.second - b.second) * (a.second - b.second));
}

void solve() {
  int N;
  cin >> N;
  vector<pii> A(N);
  for (int i = 0; i < N; i++) cin >> A[i].first >> A[i].second;

  pii ans;
  double cdist = 1e18;

  for (int i = 0; i < N; i++) {
    double mdist = 0;
    for (int j = 0; j < N; j++) mdist = max(mdist, dist(A[i], A[j]));
    if (mdist < cdist) {
      cdist = mdist;
      ans = A[i];
    }
  }

  auto [x, y] = ans;
  cout << x << ' ' << y << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
