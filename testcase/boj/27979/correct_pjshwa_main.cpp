#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) cin >> A[i], B[i] = A[i];
  sort(B.begin(), B.end());

  int r = N - 1;
  for (int i = N - 1; i >= 0; i--) {
    if (A[i] == B[r]) r--;
  }
  cout << r + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
