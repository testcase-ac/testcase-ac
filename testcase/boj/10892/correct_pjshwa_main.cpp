#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<tuple<int, int, int>> A;
  for (int i = 1; i <= 3 * N; i++) {
    int x, y; cin >> x >> y;
    A.emplace_back(x, y, i);
  }
  sort(A.begin(), A.end());

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 3; j++) {
      cout << get<2>(A[3 * i + j]) << ' ';
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
