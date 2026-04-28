#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4, MAXV = 5000, MOD = 1e9 + 7;
int A[MAX + 1], d[MAX + 1][MAXV + 1];

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> A[i];
    if (A[i] > MAXV) return cout << "0\n", void();
  }
  if (A[1] > 0) return cout << "0\n", void();

  d[1][0] = 1;
  for (int i = 2; i <= N; i++) {
    if (A[i] != -1) {
      d[i][A[i]] = (d[i][A[i]] + d[i - 1][A[i]]) % MOD; 
      if (A[i] - 1 >= 0) d[i][A[i]] = (d[i][A[i]] + d[i - 1][A[i] - 1]) % MOD; 
      if (A[i] + 1 <= MAXV) d[i][A[i]] = (d[i][A[i]] + d[i - 1][A[i] + 1]) % MOD;
      continue;
    }

    for (int v = 0; v <= MAXV; v++) {
      d[i][v] = (d[i][v] + d[i - 1][v]) % MOD; 
      if (v - 1 >= 0) d[i][v] = (d[i][v] + d[i - 1][v - 1]) % MOD; 
      if (v + 1 <= MAXV) d[i][v] = (d[i][v] + d[i - 1][v + 1]) % MOD;
    }
  }

  cout << d[N][0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
