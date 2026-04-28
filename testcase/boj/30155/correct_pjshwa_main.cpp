#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

void solve() {
  int A, B, N; cin >> A >> B >> N;

  int U[6];
  U[0] = (A + MOD) % MOD;
  U[1] = (B + MOD) % MOD;
  for (int i = 2; i < 6; ++i) U[i] = (U[i - 1] - U[i - 2] + MOD) % MOD;

  cout << U[(N - 1) % 6] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
