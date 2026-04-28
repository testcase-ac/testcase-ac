#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> A(N);
  for (auto& x : A) cin >> x;
  sort(A.begin(), A.end());

  int i = 0, ans = 0;
  while (i < N) i += A[i], ans++;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
