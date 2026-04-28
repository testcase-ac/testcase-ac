#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  if (N == 1) return cout << "1\n", void();

  vector<int> A(N);
  for (int& x : A) cin >> x;
  sort(A.begin(), A.end(), greater<int>());

  int ans = N;
  for (int i = 2; i < N; ++i) {
    if (A[i] == A[i - 1] && A[i - 1] == A[i - 2]) --ans;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
