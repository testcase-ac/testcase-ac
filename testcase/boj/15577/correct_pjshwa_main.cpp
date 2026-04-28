#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A.begin(), A.end());

  if (N == 1) return cout << A[0] << '\n', void();

  int sum = A[0] + A[1], p = 2;
  for (int i = 2; i < N; i++) {
    sum += p * A[i];
    p *= 2;
  }
  cout << fixed << setprecision(10) << (double)sum / p << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
