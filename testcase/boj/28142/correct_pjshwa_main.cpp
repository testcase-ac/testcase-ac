#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

__int128_t lpow(__int128_t x, __int128_t y, __int128_t m) {
  __int128_t r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void solve_naive(ll N) {
  ll X = 0;
  for (int i = 1; i <= N; i++) {
    X -= i;
    if (X < 0) X = -X;

    if (i % 3 == 0) X = (X * i) % MOD;
    if (i % 15 == 0) X = (X & i);
    if (i % 63 == 0) X = (X ^ i);
    if (i % 255 == 0) X = (X | i);
    if (i % 1023 == 0) X = (X * lpow(2, i, MOD)) % MOD;
  }
  cout << X << '\n';
}

void solve() {
  ll N; cin >> N;
  if (N <= 255) return solve_naive(N);

  __int128_t S = N - (N % 255), X = S; assert(S % 255 == 0);
  if (S % 1023 == 0) X = (X * lpow(2, S, MOD)) % MOD;

  for (__int128_t i = S + 1; i <= N; i++) {
    X -= i;
    if (X < 0) X = -X;

    if (i % 3 == 0) X = (X * i) % MOD;
    if (i % 15 == 0) X = (X & i);
    if (i % 63 == 0) X = (X ^ i);
    if (i % 255 == 0) X = (X | i);
    if (i % 1023 == 0) X = (X * lpow(2, i, MOD)) % MOD;
  }
  cout << (ll)X << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
