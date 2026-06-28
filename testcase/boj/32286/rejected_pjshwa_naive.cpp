#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

void solve() {
  ll k, p, q, r, s; cin >> k >> p >> q >> r >> s;
  ll N = (1LL << k) - 1;
  vector<ll> A(N + 1);
  cin >> A[1]; ll S = A[1];

  for (int i = 2; i <= N; ++i) {
    if (i & 1) A[i] = r * A[i / 2] + s;
    else A[i] = p * A[i / 2] + q;
    S += A[i];
  }
  cout << S << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
