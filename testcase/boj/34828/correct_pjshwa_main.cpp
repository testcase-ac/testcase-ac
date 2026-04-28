#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXK = 300, MAXN = 1e5, MOD = 998244353;
vector<vector<vector<int>>> F(MAXK + 1);

void solve() {

  int N, K; cin >> N >> K;
  if (K > MAXK) {
    ll v = 1;
    while (N > 0) {
      v = v * N % MOD;
      N -= K;
    }
    cout << v << '\n';
  } else {
    int q = N / K, r = N % K;
    if (r == 0) cout << F[K][K][q - 1] << '\n';
    else cout << F[K][r][q] << '\n';
  }
}

int main() {
  fast_io();

  for (int k = 1; k <= MAXK; ++k) {
    F[k].resize(k + 1);
    for (int m = 1; m <= k; ++m) {
      F[k][m].push_back(m);
      for (int i = 1;; ++i) {
        ll v = k * i + m;
        if (v > MAXN) break;
        F[k][m].push_back(F[k][m].back() * v % MOD);
      }
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
