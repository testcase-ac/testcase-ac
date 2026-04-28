#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, X; cin >> N >> X;
  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  for (int i = 0; i < N; i++) cin >> B[i];

  ll dif = 0;
  for (int i = 0; i < N; i++) {
    dif += B[i];
    if (dif < A[i]) return cout << "-1\n", void();
  }
  cout << (dif - A[N - 1]) / X << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
