#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
ll A[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A, A + N);

  ll ans = 0;
  for (int i = 0; i < N; ++i) ans ^= (A[i] * A[i]);
  for (int i = 1; i < N; ++i) ans ^= (A[i] * A[i - 1]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
