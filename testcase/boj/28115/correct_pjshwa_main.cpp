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
  
  bool f = true;
  for (int i = 2; i < N; i++) {
    int d1 = A[i] - A[i - 1];
    int d2 = A[i - 1] - A[i - 2];
    if (d1 != d2) f = false;
  }
  if (!f) return cout << "NO\n", void();

  cout << "YES\n";
  for (int i = 0; i < N; i++) cout << A[i] << " \n"[i == N - 1];
  for (int i = 0; i < N; i++) cout << 0 << " \n"[i == N - 1];
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
