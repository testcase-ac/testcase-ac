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

  ll K, ans = 0; cin >> K;
  for (int p : A) {
    ll c = p;
    while (c <= K) {
      ans += K / c;
      c *= p;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
