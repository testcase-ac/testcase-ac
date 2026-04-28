#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<ll> A(N);
  for (auto& a : A) cin >> a;

  sort(A.begin(), A.end(), greater<ll>());
  ll ans = 2 * A[0] + accumulate(A.begin() + 1, A.end(), 0LL);

  if (ans & 1) cout << ans / 2 << ".5\n";
  else cout << ans / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
