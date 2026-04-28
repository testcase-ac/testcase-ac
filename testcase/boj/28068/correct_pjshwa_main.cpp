#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<pii> A, D;
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;
    if (x <= y) A.emplace_back(x, y);
    else D.emplace_back(x, y);
  }

  sort(A.begin(), A.end(), [&](pii& a, pii& b) {
    auto& [ax, ay] = a; auto& [bx, by] = b;
    if (ax == bx) return ay > by;
    return ax < bx;
  });
  sort(D.begin(), D.end(), [&](pii& a, pii& b) {
    auto& [ax, ay] = a; auto& [bx, by] = b;
    if (ay == by) return ax < bx;
    return ay > by;
  });

  ll acc = 0;
  for (auto& [x, y] : A) {
    acc -= x;
    if (acc < 0) return cout << "0\n", void();
    acc += y;
  }
  for (auto& [x, y] : D) {
    acc -= x;
    if (acc < 0) return cout << "0\n", void();
    acc += y;
  }
  cout << "1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
