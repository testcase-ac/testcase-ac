#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A.begin(), A.end());

  int d = 0, ans = -1;
  for (int i = 1; i < N; i++) {
    int x = A[i - 1], y = A[i];
    if (y == x + 1) continue;

    int m = (x + y) / 2;
    int cd = min(m - x, y - m);
    if (cd > d) d = cd, ans = m;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
