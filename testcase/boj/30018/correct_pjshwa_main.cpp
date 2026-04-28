#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> A(N), B(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N; ++i) cin >> B[i];

  int ans = 0;
  for (int i = 0; i < N; ++i) ans += abs(A[i] - B[i]);
  cout << ans / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
