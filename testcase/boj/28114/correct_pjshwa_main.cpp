#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  vector<tuple<int, int, string>> A(3);
  for (int i = 0; i < 3; ++i) {
    int x, y; string s;
    cin >> x >> y >> s;
    A[i] = {-x, y, s};
  }
  sort(A.begin(), A.end());

  set<int> B;
  for (int i = 0; i < 3; i++) {
    auto& [x, y, s] = A[i];
    B.insert(y % 100);
  }

  for (int e : B) cout << e;
  cout << '\n';

  for (auto [x, y, s] : A) cout << s[0];
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
