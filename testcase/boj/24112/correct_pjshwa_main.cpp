#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1234567;

void solve() {
  int N, P;
  cin >> N >> P;
  vector<int> A(N + 1, 0), D(N + 1, 0);
  for (int i = 1; i <= N; i++) {
    cin >> A[i];
    A[i] = A[i - 1] + A[i];
  }

  D[0] = 1;
  int l = 0;
  for (int i = 1; i <= N; i++) {
    while (A[i] - (l >= 1 ? A[l - 1] : 0) > P) l++;
    D[i] = (D[i - 1] + MOD - (l >= 2 ? D[l - 2] : 0)) % MOD;
    D[i] = (D[i] + D[i - 1]) % MOD;
  }

  cout << (D[N] - D[N - 1] + MOD) % MOD << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
