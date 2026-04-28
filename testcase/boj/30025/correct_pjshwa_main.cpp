#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

void solve() {
  int N, M, K; cin >> N >> M >> K;

  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  int d[M][K]; memset(d, 0, sizeof(d));
  for (int i = 0; i < N; ++i) {
    if (A[i] == 0) continue;
    d[0][A[i] % K] += 1;
  }

  for (int l = 1; l < M; ++l) {
    for (int m = 0; m < K; ++m) {
      for (int g : A) {
        int nm = (m * 10 + g) % K;
        d[l][nm] = (d[l][nm] + d[l - 1][m]) % MOD;
      }
    }
  }

  cout << d[M - 1][0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
