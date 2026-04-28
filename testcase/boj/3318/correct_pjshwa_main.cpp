#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6, MOD = 1e9 + 9;
ll A[MAX], d[MAX];

void solve() {
  int N, D; cin >> N >> D;
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A, A + N);

  d[0] = 1; int l = 0;
  for (int i = 1; i < N; i++) {
    while (l < i && A[i] - A[l] > D) l++;
    d[i] = (d[i - 1] * (i - l + 1)) % MOD;
  }
  cout << d[N - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
