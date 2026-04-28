#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 300, MOD = 1e9;
int d[MAX][MAX];

void solve() {
  string S; cin >> S;
  int N = S.size();

  for (int l = N - 1; l >= 0; l--) {
    d[l][l] = 1;
    for (int r = l + 2; r < N; r += 2) {
      if (S[l] == S[r]) d[l][r] = d[l + 1][r - 1];
      for (int p = l + 2; p < r; p += 2) {
        if (S[l] == S[p] && S[p] == S[r]) {
          ll cur = d[p + 1][r - 1];
          cur = (cur * d[l][p]) % MOD;
          d[l][r] = (d[l][r] + cur) % MOD;
        }
      }
    }
  }
  cout << d[0][N - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
