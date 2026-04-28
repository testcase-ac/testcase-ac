#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, x; cin >> N;
  for (int i = 0; i < N - 1; ++i) cin >> x;

  vector<ll> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A.begin(), A.end(), greater<ll>());

  ll pre = 0;
  for (int i = 0; i < N; ++i) cout << pre + A[i] << "\n", pre += A[i];
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
