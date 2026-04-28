#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  vector<ll> A(N);
  ll val = 0;
  for (int i = 0; i < N; i++) cin >> A[i], val ^= A[i];
  A.push_back(val);
  N++;

  vector<ll> B(2 * N);
  for (int i = 0; i < 2 * N; i++) {
    B[i] = A[i % N];
    if (i) B[i] ^= B[i - 1];
  }

  int Q;
  cin >> Q;
  while (Q--) {
    ll L, R;
    cin >> L >> R;
    L--; R--;
    L %= N; R %= N;
    if (R < L) R += N;

    if (L) cout << (B[R] ^ B[L - 1]) << '\n';
    else cout << B[R] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
