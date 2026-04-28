#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<pair<string, string>> A(N);
  for (auto& [a, b] : A) cin >> a >> b;
  sort(A.begin(), A.end(), [&](auto& a, auto& b) {
    auto& [ax, ay] = a; auto& [bx, by] = b;
    if (ax == bx) return ay > by;
    return ax < bx;
  });
  for (auto [a, b] : A) cout << a << ' ' << b << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
