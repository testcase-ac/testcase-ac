#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, A, B, C, D, E, F;
  cin >> N >> A >> B >> C >> D >> E >> F;

  ll X = 0, S = 0;
  if (N > 5e6) S = N / F * F;
  for (ll i = S + 1; i <= N; i++) {
    if (i % A == 0) X += i;
    if (i % B == 0) X %= i;
    if (i % C == 0) X &= i;
    if (i % D == 0) X ^= i;
    if (i % E == 0) X |= i;
    if (i % F == 0) X >>= i;
  }

  cout << X << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
