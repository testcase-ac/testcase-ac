#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int K, N; cin >> K >> N;
  cout << K << ' ';

  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    B[i] = A[i];
  }
  sort(B.begin(), B.end());

  int p = 0;
  for (int i = 0; i < N; i++) {
    if (B[p] == A[i]) p++;
  }
  cout << N - p << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
