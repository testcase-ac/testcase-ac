#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, W; cin >> N >> W;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  ll ans = W;
  for (int i = 1; i < N; i++) {
    if (A[i] < A[i - 1]) continue;

    ll q = ans / A[i - 1];
    ans = (ans % A[i - 1]) + (q * A[i]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
